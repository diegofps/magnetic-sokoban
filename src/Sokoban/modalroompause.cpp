#include "modalroompause.h"
#include "image.h"
#include "background.h"
#include "engine.h"
#include "graphics.h"
#include "motionbackground.h"
#include "gameroom.h"
#include "spriteshandler.h"
#include "objectimage.h"
#include "button.h"
#include "bigfoot.h"

ModalRoomPause::ModalRoomPause(Engine *engine, GameRoom *parent, SpritesHandler * spritesHandler) :
    Room(engine, parent),
    _spritesHandler(spritesHandler)
{
    Image * background = engine->graphics()->newImage(":imgs/pause_background.svg");
    Background *pauseBackground = engine->graphics()->newMotionBackground(background, 0, 0);
    addBackground(pauseBackground);
}

void ModalRoomPause::steps(const int robotSteps, const int stepsForGold, const int stepsForSilver, const int stepsForBronze)
{
    _robotSteps = robotSteps;
    _stepsForGold = stepsForGold;
    _stepsForSilver = stepsForSilver;
    _stepsForBronze = stepsForBronze;
}

void ModalRoomPause::onEnter()
{
    addKeyListener(this);

    Object *window = new ObjectImage(engine(), _spritesHandler->pauseWindow());

    _btMenu    = new Button(engine(), this, _spritesHandler->pauseBtMenuNormal()   , _spritesHandler->pauseBtMenuHover()   , _spritesHandler->pauseBtMenuPress()   , this);
    _btRestart = new Button(engine(), this, _spritesHandler->pauseBtRestartNormal(), _spritesHandler->pauseBtRestartHover(), _spritesHandler->pauseBtRestartPress(), this);
    _btResume  = new Button(engine(), this, _spritesHandler->pauseBtResumeNormal() , _spritesHandler->pauseBtResumeHover() , _spritesHandler->pauseBtResumePress() , this);

    window->x( (viewport().width() - window->width()) / 2 );
    window->y( (viewport().height() - window->height()) / 2 );

    int spaceBellow = 17;
    int spaceBetween = 11;

    int startY = window->y() + window->height() - _btMenu->height() - spaceBellow;
    int startX = window->x() + (window->width() - _btMenu->width() * 3 - spaceBetween * 2) / 2;

    _btMenu->x(startX);
    _btMenu->y(startY);

    _btRestart->x(startX + _btMenu->width() + spaceBetween);
    _btRestart->y(startY);

    _btResume->x(startX + _btMenu->width() * 2 + spaceBetween * 2);
    _btResume->y(startY);

    BigFoot *bigFoot = new BigFoot(engine(), window, _spritesHandler, _robotSteps, _stepsForGold, _stepsForSilver, _stepsForBronze);

    addObject(window);
    addObject(_btMenu);
    addObject(_btRestart);
    addObject(_btResume);
    addObject(bigFoot);
}

void ModalRoomPause::onKeyRelease(KeyListener::Key key)
{
    if (key == KeyListener::Escape)
        close(RESULT_MENU);
}

void ModalRoomPause::onClick(Button *button)
{
    if (button == _btMenu)
        close(RESULT_MENU);

    else if (button == _btRestart)
        close(RESULT_RESTART);

    else if (button == _btResume)
        close(RESULT_RESUME);
}
