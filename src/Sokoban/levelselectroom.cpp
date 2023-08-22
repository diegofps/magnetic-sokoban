#include "levelselectroom.h"
#include <QFile>
#include <iostream>
#include <sstream>
#include <fstream>
#include "mappack.h"
#include "sprite.h"
#include "buttonmenulevel.h"
#include "engine.h"
#include "menuroom.h"
#include "graphics.h"
#include "gameroom.h"

LevelSelectRoom::LevelSelectRoom(Engine *engine, Background *background, MenuRoom *menuRoom) :
    Room(engine),
    _mapPack(new MapPack()), _menuRoom(menuRoom), _currentPage(0)
{
    addBackground(background);

    importMapPack();

    // Forces allocation if not
    if (_mapPack->all()->size() > 0)
        _gameProgress.star(_mapPack->all()->size()-1);

    _gameRoom = new GameRoom(engine, _mapPack, this, &_gameProgress);
    _spriteNumbers = new Sprite(engine->graphics()->newImage(":imgs/numbers.png"),12,12,1,0);

    _spriteButtonLevelNormal = new Sprite(engine->graphics()->newImage(":imgs/button_level_normal.svg"),1,1,1,0);
    _spriteButtonLevelHover = new Sprite(engine->graphics()->newImage(":imgs/button_level_hover.svg"),1,1,1,0);
    _spriteButtonLevelPress = new Sprite(engine->graphics()->newImage(":imgs/button_level_press.svg"),1,1,1,0);

    _spriteButtonLevelLocked = new Sprite(engine->graphics()->newImage(":imgs/button_level_locked.svg"),1,1,1,0);

    _spriteButtonBackNormal = new Sprite(engine->graphics()->newImage(":imgs/button_back_normal.svg"),1,1,1,0);
    _spriteButtonBackHover = new Sprite(engine->graphics()->newImage(":imgs/button_back_hover.svg"),1,1,1,0);
    _spriteButtonBackPress = new Sprite(engine->graphics()->newImage(":imgs/button_back_press.svg"),1,1,1,0);

    _spriteGoldStar = new Sprite(engine->graphics()->newImage(":imgs/star_gold.svg"),1,1,1,0);
    _spriteSilverStar = new Sprite(engine->graphics()->newImage(":imgs/star_silver.svg"),1,1,1,0);
    _spriteBronzeStar = new Sprite(engine->graphics()->newImage(":imgs/star_bronze.svg"),1,1,1,0);
}

void LevelSelectRoom::onEnter()
{
    addKeyListener(this);
    createButtons();
    repositionButtons();
    showCurrentPage();
}

void LevelSelectRoom::onLeave()
{

}

void LevelSelectRoom::importMapPack()
{
    QFile file(":/imgs/mapPack1.mpk");

    if (!file.open(QIODevice::ReadOnly)) {
        std::cout << "Could not open MapPack file" << std::endl;
        return;
    }

    QByteArray byteArray = file.readAll();
    file.close();

    std::string str(byteArray.constData(), byteArray.length());
    std::istringstream iss(str, std::istringstream::in | std::istringstream::binary);

    if (!_mapPack->importFrom(&iss)) {
        std::cout << "Could not import MapPack" << std::endl;
    }
}

void LevelSelectRoom::createButtons()
{
    _btArrowLeft = new ButtonMenuLevel(engine(), this,
                                       _spriteButtonLevelNormal, _spriteButtonLevelHover, _spriteButtonLevelPress,
                                       this, _spriteNumbers, ButtonMenuLevel::ARROW_LEFT);

    _btArrowRight = new ButtonMenuLevel(engine(), this,
                                        _spriteButtonLevelNormal, _spriteButtonLevelHover, _spriteButtonLevelPress,
                                       this, _spriteNumbers, ButtonMenuLevel::ARROW_RIGHT);

    _btBack = new Button(engine(), this, _spriteButtonBackNormal, _spriteButtonBackHover, _spriteButtonBackPress, this);

    addObject(_btArrowLeft);
    addObject(_btArrowRight);
    addObject(_btBack);

    for (int x=0;x<COLUMNS;++x) {
        for (int y=0;y<ROWS;++y) {
            _btLevels[x][y] = new ButtonMenuLevel(engine(), this,
                                                  _spriteButtonLevelNormal, _spriteButtonLevelHover, _spriteButtonLevelPress,
                                                  this, _spriteNumbers, ButtonMenuLevel::NOTHING);
            addObject(_btLevels[x][y]);
        }
    }
}

void LevelSelectRoom::repositionButtons()
{
    int hSpace = (viewport().width() - (COLUMNS + 2) * _spriteButtonLevelNormal->width()) / (COLUMNS + 3);
    int vSpace = (viewport().height() - (ROWS + 1) * _spriteButtonLevelNormal->height()) / (ROWS + 2);

    int centerX = viewport().width() / 2;
    int centerY = viewport().height() / 2;

    _btArrowLeft->x( hSpace );
    _btArrowLeft->y( centerY - _btArrowLeft->height() / 2 );

    _btArrowRight->x( viewport().width() - hSpace - _btArrowRight->width() );
    _btArrowRight->y( centerY - _btArrowRight->height() / 2 );

    _btBack->x( centerX - _btBack->width() / 2 );
    _btBack->y( viewport().height() - vSpace - _btBack->height() );

    for (int x = 0; x < COLUMNS; ++x) {
        for (int y = 0; y < ROWS; ++y) {
            _btLevels[x][y]->x( 2 * hSpace + _btArrowLeft->width() + x * (_btLevels[0][0]->width() + hSpace) );
            _btLevels[x][y]->y( vSpace + y * (_btLevels[0][0]->height() + vSpace) );
        }
    }
}

void LevelSelectRoom::onClick(Button *button)
{
    if (button == _btBack) {
        engine()->goTo(_menuRoom);
        return;
    }

    if (button == _btArrowLeft) {
        showPreviousPage();
        return;
    }

    if (button == _btArrowRight) {
        showNextPage();
        return;
    }

    int x, y;
    for (int i = 0; i < COLUMNS * ROWS; ++i) {
        x = i % COLUMNS;
        y = i / COLUMNS;

        if (_btLevels[x][y] == button) {
            _gameRoom->setLevel( COLUMNS * ROWS * _currentPage + i );
            engine()->goTo(_gameRoom);
            break;
        }

    }

}

void LevelSelectRoom::showPreviousPage()
{
    --_currentPage;
    showCurrentPage();
}

void LevelSelectRoom::showNextPage()
{
    ++_currentPage;
    showCurrentPage();
}

void LevelSelectRoom::showCurrentPage()
{
    int levels = _mapPack->all()->size();
    int levelsPerPage = COLUMNS * ROWS;
    int lastPage = (_mapPack->all()->size() - 1) / levelsPerPage;

    _btArrowLeft->visible(_currentPage != 0);
    _btArrowRight->visible(_currentPage != lastPage);

    int x, y;
    Sprite *star;
    int currentLevel;

    for(int i=0; i<levelsPerPage; ++i) {
        y = i / COLUMNS;
        x = i % COLUMNS;
        currentLevel = _currentPage * levelsPerPage + i;

        if (currentLevel < levels) {
            _btLevels[x][y]->visible(true);

            if (_gameProgress.isLocked(currentLevel)) {
                _btLevels[x][y]->level(ButtonMenuLevel::NOTHING);

                _btLevels[x][y]->spriteNormal(_spriteButtonLevelLocked);
                _btLevels[x][y]->spriteHover(_spriteButtonLevelLocked);
                _btLevels[x][y]->spritePress(_spriteButtonLevelLocked);

                _btLevels[x][y]->listener(NULL);
                _btLevels[x][y]->star(NULL);
            }
            else {
                _btLevels[x][y]->level(currentLevel+1);

                _btLevels[x][y]->spriteNormal(_spriteButtonLevelNormal);
                _btLevels[x][y]->spriteHover(_spriteButtonLevelHover);
                _btLevels[x][y]->spritePress(_spriteButtonLevelPress);

                switch(_gameProgress.star(currentLevel)) {
                    case GameProgress::GOLD: star = _spriteGoldStar; break;
                    case GameProgress::SILVER: star = _spriteSilverStar; break;
                    case GameProgress::BRONZE: star = _spriteBronzeStar; break;
                    default: star = NULL;
                }

                _btLevels[x][y]->star(star);
                _btLevels[x][y]->listener(this);
            }
        }
        else {
            _btLevels[x][y]->visible(false);
        }

    }

}

void LevelSelectRoom::onKeyRelease(KeyListener::Key key)
{
    if (key == KeyListener::Escape)
        engine()->goTo(_menuRoom);
}
