#include "modalroomfinishlevel.h"
#include "spriteshandler.h"
#include "objectimage.h"
#include "button.h"
#include "bigstar.h"
#include "image.h"
#include "engine.h"
#include "graphics.h"
#include "motionbackground.h"

ModalRoomFinishLevel::ModalRoomFinishLevel(Engine *engine, Room *parent, SpritesHandler *spritesHandler) :
    Room(engine, parent),
    _spritesHandler(spritesHandler), _star(NULL)
{
    Image * background = engine->graphics()->newImage(":imgs/pause_background.svg");
    Background *pauseBackground = engine->graphics()->newMotionBackground(background, 0, 0);
    addBackground(pauseBackground);
}

void ModalRoomFinishLevel::steps(const int robotSteps, const int stepsForGold, const int stepsForSilver, const int stepsForBronze)
{
    _robotSteps = robotSteps;
    _stepsForGold = stepsForGold;
    _stepsForSilver = stepsForSilver;
    _stepsForBronze = stepsForBronze;
}

void ModalRoomFinishLevel::onEnter()
{
    addKeyListener(this);

    Object *window = new ObjectImage(engine(), _spritesHandler->finishLevelWindow());

    window->x( (viewport().width() - window->width()) / 2 );
    window->y( (viewport().height() - window->height()) / 2 );

    _btMenu    = new Button(engine(), this, _spritesHandler->pauseBtMenuNormal()   , _spritesHandler->pauseBtMenuHover()   , _spritesHandler->pauseBtMenuPress()   , this);
    _btRestart = new Button(engine(), this, _spritesHandler->pauseBtRestartNormal(), _spritesHandler->pauseBtRestartHover(), _spritesHandler->pauseBtRestartPress(), this);
    _btNext    = new Button(engine(), this, _spritesHandler->pauseBtNextNormal()   , _spritesHandler->pauseBtNextHover()   , _spritesHandler->pauseBtNextPress()   , this);

    int spaceBellow = 17;
    int spaceBetween = 11;

    int startY = window->y() + window->height() - _btMenu->height() - spaceBellow;
    int startX = window->x() + (window->width() - _btMenu->width() * 3 - spaceBetween * 2) / 2;

    _btMenu->x(startX);
    _btMenu->y(startY);

    _btRestart->x(startX + _btMenu->width() + spaceBetween);
    _btRestart->y(startY);

    _btNext->x(startX + _btMenu->width() * 2 + spaceBetween * 2);
    _btNext->y(startY);

    Object *bigStar = new BigStar(engine(), _spritesHandler, window, _robotSteps, _stepsForGold, _stepsForSilver, _stepsForBronze);

    addObject(window);
    addObject(_btMenu);
    addObject(_btRestart);
    addObject(_btNext);
    addObject(bigStar);
}

void ModalRoomFinishLevel::onClick(Button *button)
{
    if (button == _btMenu)
        close(RESULT_MENU);

    else if (button == _btRestart)
        close(RESULT_RESTART);

    else if (button == _btNext)
        close(RESULT_NEXT);
}

void ModalRoomFinishLevel::onKeyRelease(KeyListener::Key key)
{
    if (key == KeyListener::Escape)
        close(RESULT_MENU);
}

