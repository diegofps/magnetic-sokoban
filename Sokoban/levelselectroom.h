#ifndef LEVELSELECTROOM_H
#define LEVELSELECTROOM_H

#include "room.h"
#include "buttonlistener.h"
#include "gameprogress.h"

class Engine;
class Background;
class MapPack;
class Sprite;
class MenuRoom;
class Object;
class GameRoom;
class ButtonMenuLevel;

class LevelSelectRoom : public Room, public ButtonListener, public KeyListener
{

private:

    static const int COLUMNS = 4;

    static const int ROWS = 3;

public:

    LevelSelectRoom(Engine *engine, Background *background, MenuRoom *menuRoom);

    void onEnter();

    void onLeave();

    void onClick(Button *button);

    void onKeyRelease(Key key);

private:

    void importMapPack();

    void createButtons();

    void repositionButtons();

    void showNextPage();

    void showPreviousPage();

    void showCurrentPage();

private:

    MapPack *_mapPack;

    MenuRoom *_menuRoom;

    Sprite *_spriteNumbers;

    Sprite *_spriteButtonLevelNormal;

    Sprite *_spriteButtonLevelHover;

    Sprite *_spriteButtonLevelPress;

    Sprite *_spriteButtonLevelLocked;

    Sprite *_spriteButtonBackNormal;

    Sprite *_spriteButtonBackHover;

    Sprite *_spriteButtonBackPress;

    Sprite *_spriteGoldStar;

    Sprite *_spriteSilverStar;

    Sprite *_spriteBronzeStar;

    Object *_btBack;

    Object *_btArrowLeft;

    Object *_btArrowRight;

    ButtonMenuLevel *_btLevels[COLUMNS][ROWS];

    GameProgress _gameProgress;

    GameRoom *_gameRoom;

    int _currentPage;

};

#endif // LEVELSELECTROOM_H
