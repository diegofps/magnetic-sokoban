#ifndef SPRITESHANDLER_H
#define SPRITESHANDLER_H

class Graphics;
class Sprite;

class SpritesHandler
{

public:

    SpritesHandler(Graphics *g);

    Sprite * robotNorth();

    Sprite * robotSouth();

    Sprite * robotEast();

    Sprite * robotWest();

    Sprite * robotMoveNorth();

    Sprite * robotMoveSouth();

    Sprite * robotMoveEast();

    Sprite * robotMoveWest();

    Sprite * plateMagneticNorthNorth();

    Sprite * plateMagneticNorthSouth();

    Sprite * plateMagneticNorthEast();

    Sprite * plateMagneticNorthWest();

    Sprite * plateMagneticSouthNorth();

    Sprite * plateMagneticSouthSouth();

    Sprite * plateMagneticSouthEast();

    Sprite * plateMagneticSouthWest();

    Sprite * plateMetalNorth();

    Sprite * plateMetalSouth();

    Sprite * plateMetalEast();

    Sprite * plateMetalWest();

    Sprite * movableWall();

    Sprite * rigidWall();

    Sprite * atObjectiveWall();

    Sprite * bindedWall();

    Sprite * floor();

    Sprite * floorObjective();

    Sprite * pauseBtMenuNormal();

    Sprite * pauseBtMenuHover();

    Sprite * pauseBtMenuPress();

    Sprite * pauseBtRestartNormal();

    Sprite * pauseBtRestartHover();

    Sprite * pauseBtRestartPress();

    Sprite * pauseBtResumeNormal();

    Sprite * pauseBtResumeHover();

    Sprite * pauseBtResumePress();

    Sprite * pauseWindow();

    Sprite * bigMissingStar();

    Sprite * bigGoldStar();

    Sprite * bigSilverStar();

    Sprite * bigBronzeStar();

    Sprite * finishLevelWindow();

    Sprite * smallFootprint();

    Sprite * bigFootprint();

    Sprite * pauseBtNextNormal();

    Sprite * pauseBtNextPress();

    Sprite * pauseBtNextHover();

    Sprite * smallNumbers();

    Sprite * numbers();

private:

    Sprite *_robotNorth;

    Sprite *_robotSouth;

    Sprite *_robotEast;

    Sprite *_robotWest;

    Sprite *_robotMoveNorth;

    Sprite *_robotMoveSouth;

    Sprite *_robotMoveEast;

    Sprite *_robotMoveWest;

    Sprite *_plateMagneticNorthNorth;

    Sprite *_plateMagneticNorthSouth;

    Sprite *_plateMagneticNorthEast;

    Sprite *_plateMagneticNorthWest;

    Sprite *_plateMagneticSouthNorth;

    Sprite *_plateMagneticSouthSouth;

    Sprite *_plateMagneticSouthEast;

    Sprite *_plateMagneticSouthWest;

    Sprite *_plateMetalNorth;

    Sprite *_plateMetalSouth;

    Sprite *_plateMetalEast;

    Sprite *_plateMetalWest;

    Sprite *_movableWall;

    Sprite *_rigidWall;

    Sprite *_atObjectiveWall;

    Sprite *_bindedWall;

    Sprite *_floor;

    Sprite *_floorObjective;

    Sprite *_pauseBtMenuNormal;

    Sprite *_pauseBtMenuHover;

    Sprite *_pauseBtMenuPress;

    Sprite *_pauseBtRestartNormal;

    Sprite *_pauseBtRestartHover;

    Sprite *_pauseBtRestartPress;

    Sprite *_pauseBtResumeNormal;

    Sprite *_pauseBtResumeHover;

    Sprite *_pauseBtResumePress;

    Sprite *_pauseWindow;

    Sprite *_bigMissingStar;

    Sprite *_bigGoldStar;

    Sprite *_bigSilverStar;

    Sprite *_bigBronzeStar;

    Sprite *_finishLevelWindow;

    Sprite *_smallFootprint;

    Sprite *_bigFootprint;

    Sprite *_pauseBtNextNormal;

    Sprite *_pauseBtNextPress;

    Sprite *_pauseBtNextHover;

    Sprite *_smallNumbers;

    Sprite *_numbers;

};

#endif // SPRITESHANDLER_H
