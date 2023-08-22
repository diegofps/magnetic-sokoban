#include "spriteshandler.h"
#include "graphics.h"
#include "sprite.h"

SpritesHandler::SpritesHandler(Graphics * g)
{
    _robotNorth = new Sprite(g->newImage(":imgs/robotNorth.svg"),1,1,1,0);
    _robotSouth = new Sprite(g->newImage(":imgs/robotSouth.svg"),1,1,1,0);
    _robotEast = new Sprite(g->newImage(":imgs/robotEast.svg"),1,1,1,0);
    _robotWest = new Sprite(g->newImage(":imgs/robotWest.svg"),1,1,1,0);

    _robotMoveNorth = new Sprite(g->newImage(":imgs/robotMoveNorth.svg"),4,1,4,2);
    _robotMoveSouth = new Sprite(g->newImage(":imgs/robotMoveSouth.svg"),4,1,4,2);
    _robotMoveEast = new Sprite(g->newImage(":imgs/robotMoveEast.svg"),4,4,1,2);
    _robotMoveWest = new Sprite(g->newImage(":imgs/robotMoveWest.svg"),4,4,1,2);

    _plateMagneticNorthNorth = new Sprite(g->newImage(":imgs/magneticNorthNorth.svg"),1,1,1,0);
    _plateMagneticNorthSouth = new Sprite(g->newImage(":imgs/magneticNorthSouth.svg"),1,1,1,0);
    _plateMagneticNorthEast = new Sprite(g->newImage(":imgs/magneticNorthEast.svg"),1,1,1,0);
    _plateMagneticNorthWest = new Sprite(g->newImage(":imgs/magneticNorthWest.svg"),1,1,1,0);

    _plateMagneticSouthNorth = new Sprite(g->newImage(":imgs/magneticSouthNorth.svg"),1,1,1,0);
    _plateMagneticSouthSouth = new Sprite(g->newImage(":imgs/magneticSouthSouth.svg"),1,1,1,0);
    _plateMagneticSouthEast = new Sprite(g->newImage(":imgs/magneticSouthEast.svg"),1,1,1,1);
    _plateMagneticSouthWest = new Sprite(g->newImage(":imgs/magneticSouthWest.svg"),1,1,1,0);

    _plateMetalNorth = new Sprite(g->newImage(":imgs/metalNorth.svg"),1,1,1,0);
    _plateMetalSouth = new Sprite(g->newImage(":imgs/metalSouth.svg"),1,1,1,0);
    _plateMetalEast = new Sprite(g->newImage(":imgs/metalEast.svg"),1,1,1,0);
    _plateMetalWest = new Sprite(g->newImage(":imgs/metalWest.svg"),1,1,1,0);

    _movableWall = new Sprite(g->newImage(":imgs/movableWall.svg"),1,1,1,0);
    _rigidWall = new Sprite(g->newImage(":imgs/rigidWall.svg"),1,1,1,0);
    _atObjectiveWall = new Sprite(g->newImage(":imgs/atObjectiveWall.svg"),1,1,1,0);
    _bindedWall = new Sprite(g->newImage(":imgs/bindedWall.svg"),1,1,1,0);

    _floor = new Sprite(g->newImage(":imgs/floor.svg"),1,1,1,0);
    _floorObjective = new Sprite(g->newImage(":imgs/floorObjective.svg"),1,1,1,0);

    _pauseBtMenuNormal = new Sprite(g->newImage(":imgs/pauseBtMenuNormal.svg"),1,1,1,0);
    _pauseBtMenuHover = new Sprite(g->newImage(":imgs/pauseBtMenuHover.svg"),1,1,1,0);
    _pauseBtMenuPress = new Sprite(g->newImage(":imgs/pauseBtMenuPress.svg"),1,1,1,0);

    _pauseBtRestartNormal = new Sprite(g->newImage(":imgs/pauseBtRestartNormal.svg"),1,1,1,0);
    _pauseBtRestartHover = new Sprite(g->newImage(":imgs/pauseBtRestartHover.svg"),1,1,1,0);
    _pauseBtRestartPress = new Sprite(g->newImage(":imgs/pauseBtRestartPress.svg"),1,1,1,0);

    _pauseBtResumeNormal = new Sprite(g->newImage(":imgs/pauseBtResumeNormal.svg"),1,1,1,0);
    _pauseBtResumeHover = new Sprite(g->newImage(":imgs/pauseBtResumeHover.svg"),1,1,1,0);
    _pauseBtResumePress = new Sprite(g->newImage(":imgs/pauseBtResumePress.svg"),1,1,1,0);

    _pauseWindow = new Sprite(g->newImage(":imgs/pauseWindow.svg"),1,1,1,0);

    _bigMissingStar = new Sprite(g->newImage(":imgs/bigMissingStar.svg"),1,1,1,0);
    _bigGoldStar = new Sprite(g->newImage(":imgs/bigGoldStar.svg"),1,1,1,0);
    _bigSilverStar = new Sprite(g->newImage(":imgs/bigSilverStar.svg"),1,1,1,0);
    _bigBronzeStar = new Sprite(g->newImage(":imgs/bigBronzeStar.svg"),1,1,1,0);

    _finishLevelWindow = new Sprite(g->newImage(":imgs/finishLevelWindow.svg"),1,1,1,0);
    _smallFootprint = new Sprite(g->newImage(":imgs/smallFootprint.svg"),1,1,1,0);
    _bigFootprint = new Sprite(g->newImage(":imgs/bigFootprint.svg"),1,1,1,0);
    _pauseBtNextNormal = new Sprite(g->newImage(":imgs/pauseBtNextNormal.svg"),1,1,1,0);
    _pauseBtNextPress = new Sprite(g->newImage(":imgs/pauseBtNextPress.svg"),1,1,1,0);
    _pauseBtNextHover = new Sprite(g->newImage(":imgs/pauseBtNextHover.svg"),1,1,1,0);
    _smallNumbers = new Sprite(g->newImage(":imgs/smallNumbers.png"),12,12,1,0);
    _numbers = new Sprite(g->newImage(":imgs/numbers.png"),12,12,1,0);

}

Sprite * SpritesHandler::robotNorth()
{
    return _robotNorth;
}

Sprite * SpritesHandler::robotSouth()
{
    return _robotSouth;
}

Sprite * SpritesHandler::robotEast()
{
    return _robotEast;
}

Sprite * SpritesHandler::robotWest()
{
    return _robotWest;
}

Sprite * SpritesHandler::robotMoveNorth()
{
    return _robotMoveNorth;
}

Sprite * SpritesHandler::robotMoveSouth()
{
    return _robotMoveSouth;
}

Sprite * SpritesHandler::robotMoveEast()
{
    return _robotMoveEast;
}

Sprite * SpritesHandler::robotMoveWest()
{
    return _robotMoveWest;
}

Sprite * SpritesHandler::plateMagneticNorthNorth()
{
    return _plateMagneticNorthNorth;
}

Sprite * SpritesHandler::plateMagneticNorthSouth()
{
    return _plateMagneticNorthSouth;
}

Sprite * SpritesHandler::plateMagneticNorthEast()
{
    return _plateMagneticNorthEast;
}

Sprite * SpritesHandler::plateMagneticNorthWest()
{
    return _plateMagneticNorthWest;
}

Sprite * SpritesHandler::plateMagneticSouthNorth()
{
    return _plateMagneticSouthNorth;
}

Sprite * SpritesHandler::plateMagneticSouthSouth()
{
    return _plateMagneticSouthSouth;
}

Sprite * SpritesHandler::plateMagneticSouthEast()
{
    return _plateMagneticSouthEast;
}

Sprite * SpritesHandler::plateMagneticSouthWest()
{
    return _plateMagneticSouthWest;
}

Sprite * SpritesHandler::plateMetalNorth()
{
    return _plateMetalNorth;
}

Sprite * SpritesHandler::plateMetalSouth()
{
    return _plateMetalSouth;
}

Sprite * SpritesHandler::plateMetalEast()
{
    return _plateMetalEast;
}

Sprite * SpritesHandler::plateMetalWest()
{
    return _plateMetalWest;
}

Sprite * SpritesHandler::movableWall()
{
    return _movableWall;
}

Sprite * SpritesHandler::rigidWall()
{
    return _rigidWall;
}

Sprite * SpritesHandler::atObjectiveWall()
{
    return _atObjectiveWall;
}

Sprite * SpritesHandler::bindedWall()
{
    return _bindedWall;
}

Sprite * SpritesHandler::floor()
{
    return _floor;
}

Sprite * SpritesHandler::floorObjective()
{
    return _floorObjective;
}

Sprite * SpritesHandler::pauseBtMenuNormal()
{
    return _pauseBtMenuNormal;
}

Sprite * SpritesHandler::pauseBtMenuHover()
{
    return _pauseBtMenuHover;
}

Sprite * SpritesHandler::pauseBtMenuPress()
{
    return _pauseBtMenuPress;
}

Sprite * SpritesHandler::pauseBtRestartNormal()
{
    return _pauseBtRestartNormal;
}

Sprite * SpritesHandler::pauseBtRestartHover()
{
    return _pauseBtRestartHover;
}

Sprite * SpritesHandler::pauseBtRestartPress()
{
    return _pauseBtRestartPress;
}

Sprite * SpritesHandler::pauseBtResumeNormal()
{
    return _pauseBtResumeNormal;
}

Sprite * SpritesHandler::pauseBtResumeHover()
{
    return _pauseBtResumeHover;
}

Sprite * SpritesHandler::pauseBtResumePress()
{
    return _pauseBtResumePress;
}

Sprite * SpritesHandler::pauseWindow()
{
    return _pauseWindow;
}

Sprite * SpritesHandler::bigMissingStar()
{
    return _bigMissingStar;
}

Sprite * SpritesHandler::bigGoldStar()
{
    return _bigGoldStar;
}

Sprite * SpritesHandler::bigSilverStar()
{
    return _bigSilverStar;
}

Sprite * SpritesHandler::bigBronzeStar()
{
    return _bigBronzeStar;
}

Sprite * SpritesHandler::finishLevelWindow()
{
    return _finishLevelWindow;
}

Sprite * SpritesHandler::smallFootprint()
{
    return _smallFootprint;
}

Sprite * SpritesHandler::bigFootprint()
{
    return _bigFootprint;
}

Sprite * SpritesHandler::pauseBtNextNormal()
{
    return _pauseBtNextNormal;
}

Sprite * SpritesHandler::pauseBtNextPress()
{
    return _pauseBtNextPress;
}

Sprite * SpritesHandler::pauseBtNextHover()
{
    return _pauseBtNextHover;
}

Sprite * SpritesHandler::smallNumbers()
{
    return _smallNumbers;
}

Sprite * SpritesHandler::numbers()
{
    return _numbers;
}
