#include "menuroom.h"
#include "image.h"
#include "engine.h"
#include "levelselectroom.h"
#include "sprite.h"
#include "objectimage.h"
#include "graphics.h"
#include "button.h"
#include "motionbackground.h"

MenuRoom::MenuRoom(Engine *engine) :
    Room(engine)
{
    Image *imgBackground = engine->graphics()->newImage(":imgs/menu_background.svg");
    Background *background = engine->graphics()->newMotionBackground(imgBackground, 0, 0);
    addBackground(background);

    _levelSelectRoom = new LevelSelectRoom(engine, background, this);

    _spriteButtonPlayNormal = new Sprite(engine->graphics()->newImage(":imgs/button_play_normal.svg"),1,1,1,0);
    _spriteButtonPlayHover = new Sprite(engine->graphics()->newImage(":imgs/button_play_hover.svg" ),1,1,1,0);
    _spriteButtonPlayPress = new Sprite(engine->graphics()->newImage(":imgs/button_play_press.svg" ),1,1,1,0);

    _spriteButtonQuitNormal = new Sprite(engine->graphics()->newImage(":imgs/button_quit_normal.svg"),1,1,1,0);
    _spriteButtonQuitHover = new Sprite(engine->graphics()->newImage(":imgs/button_quit_hover.svg" ),1,1,1,0);
    _spriteButtonQuitPress = new Sprite(engine->graphics()->newImage(":imgs/button_quit_press.svg" ),1,1,1,0);
}

MenuRoom::~MenuRoom()
{
    delete _levelSelectRoom;
}

void
MenuRoom::onEnter()
{
    addKeyListener(this);

    int vWidth = viewport().width();
    int vHeight = viewport().height();

    _buttonPlay = new Button(engine(), this, _spriteButtonPlayNormal, _spriteButtonPlayHover, _spriteButtonPlayPress, this);
    _buttonQuit = new Button(engine(), this, _spriteButtonQuitNormal, _spriteButtonQuitHover, _spriteButtonQuitPress, this);

    _title = new ObjectImage(engine(), ":imgs/title.svg");

    _buttonPlay->x( (vWidth - _buttonPlay->width()) / 2 );
    _buttonPlay->y( vHeight - _buttonPlay->height() * 4 );

    _buttonQuit->x( (vWidth - _buttonQuit->width()) / 2 );
    _buttonQuit->y( vHeight - _buttonQuit->height() * 2 );

    _title->x( (vWidth - _title->width()) / 2 );
    _title->y( 50 );

    addObject(_title);
    addObject(_buttonPlay);
    addObject(_buttonQuit);
}

void MenuRoom::onLeave()
{

}

void MenuRoom::onClick(Button *button)
{
    if (button == _buttonPlay)
        engine()->goTo(_levelSelectRoom);

    else if (button ==_buttonQuit)
        engine()->endGame();
}

void MenuRoom::onKeyPress(KeyListener::Key key)
{
    if (key == KeyListener::Escape)
        engine()->endGame();
}
