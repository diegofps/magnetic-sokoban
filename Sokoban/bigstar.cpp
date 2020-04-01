#include "bigstar.h"
#include "numberdrawer.h"
#include "spriteshandler.h"

BigStar::BigStar(Engine *engine, SpritesHandler *spritesHandler, Object *window, const int robotSteps, const int stepsForGold, const int stepsForSilver, const int stepsForBronze) :
    Object(engine),
    _spritesHandler(spritesHandler), _window(window), _showSteps(0), _robotSteps(robotSteps),
    _stepsForGold(stepsForGold), _stepsForSilver(stepsForSilver), _stepsForBronze(stepsForBronze)
{

}

void BigStar::draw(const Viewport &, Graphics *g)
{
    Sprite *star;

    if (_showSteps != _robotSteps * DELAY)
        star = _spritesHandler->bigMissingStar();
    else if (_robotSteps <= _stepsForGold)
        star = _spritesHandler->bigGoldStar();
    else if (_robotSteps <= _stepsForSilver)
        star = _spritesHandler->bigSilverStar();
    else if (_robotSteps <= _stepsForBronze)
        star = _spritesHandler->bigBronzeStar();
    else
        star = _spritesHandler->bigMissingStar();

    int starX = _window->x() + ( _window->width() - star->width() ) / 2;
    int starY = _window->y() + 30;

    star->draw(g, starX, starY);

    NumberDrawer numberdrawer(_spritesHandler->smallNumbers());
    numberdrawer.number(_showSteps / DELAY);

    Sprite *smallFootprint = _spritesHandler->smallFootprint();

    int spaceBetween = 16;
    int startX = _window->x() + ( _window->width() -  smallFootprint->width() - spaceBetween - numberdrawer.width() ) / 2;
    int startY = _window->y() + 190;

    smallFootprint->draw(g, startX, startY);

    numberdrawer.draw(g,
                      startX + smallFootprint->width() + spaceBetween,
                      startY + (smallFootprint->height() - numberdrawer.height() ) / 2);

    if (_showSteps < _robotSteps * DELAY)
        ++_showSteps;
}
