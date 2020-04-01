#include "bigfoot.h"
#include "spriteshandler.h"
#include "numberdrawer.h"

BigFoot::BigFoot(Engine *engine, Object *window, SpritesHandler *spritesHandler, const int robotSteps, const int stepsForGold, const int stepsForSilver, const int stepsForBronze) :
    Object(engine),
    _window(window), _spritesHandler(spritesHandler), _robotSteps(robotSteps),
    _stepsForGold(stepsForGold), _stepsForSilver(stepsForSilver), _stepsForBronze(stepsForBronze)
{

}

void BigFoot::draw(const Viewport &, Graphics *g)
{
    NumberDrawer smallNumberDrawer(_spritesHandler->smallNumbers());

    int startX = _window->x() + 110;

    smallNumberDrawer.number(_stepsForGold);
    smallNumberDrawer.draw(g, startX - smallNumberDrawer.width() / 2, _window->y() + 40);

    smallNumberDrawer.number(_stepsForSilver);
    smallNumberDrawer.draw(g, startX - smallNumberDrawer.width() / 2, _window->y() + 112);

    smallNumberDrawer.number(_stepsForBronze);
    smallNumberDrawer.draw(g, startX - smallNumberDrawer.width() / 2, _window->y() + 184);

    NumberDrawer numberDrawer(_spritesHandler->numbers());

    numberDrawer.number(_robotSteps);
    numberDrawer.draw(g, _window->x() + 222 - numberDrawer.width() / 2, _window->y() + 160);
}
