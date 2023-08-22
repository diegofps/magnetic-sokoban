#include "buttonmenulevel.h"
#include <cstdio>
#include "sprite.h"
#include "graphics.h"

ButtonMenuLevel::ButtonMenuLevel(Engine *engine, Room *room, Sprite *normal, Sprite *hover, Sprite *press, ButtonListener *listener, Sprite *numbers, int l) :
    Object(engine), Button(engine, room, normal, hover, press, listener),
    _numbers(numbers), _star(NULL)
{
    level(l);
}

void ButtonMenuLevel::level(int level)
{
    if (level == ButtonMenuLevel::ARROW_LEFT) {
        _title[0] = 10;
        _title[1] = 0;
    } else if (level == ButtonMenuLevel::ARROW_RIGHT) {
        _title[0] = 11;
        _title[1] = 0;
    }
    else if (level >= 0) {
        sprintf(_title, "%d", level);
    } else {
        _title[0] = '\0';
    }
}

void ButtonMenuLevel::draw(const Viewport &viewport, Graphics * g)
{
    // Draws button
    Object::draw(viewport, g);

    // Draw number or arrow
    {
        int i;
        for (i=0; _title[i] != '\0'; ++i) ;

        int title_width = i * _numbers->width();
        int title_height = _numbers->height();

        int title_x = x() + (width() - title_width) / 2 - viewport.x();
        int title_y = y() + (height() - title_height) / 2 - viewport.y();

        for (i=0; _title[i] != '\0'; ++i) {
            if (_title[i] == 10 || _title[i] == 11) {
                _numbers->drawFrame(g, _title[i], title_x + i * _numbers->width(), title_y);
            }

            else if (_title[i] >= '0' && _title[i] <= '9') {
                _numbers->drawFrame(g, _title[i] - '0', title_x + i * _numbers->width(), title_y);
            }
        }
    }

    // Draws the star
    if (_star != NULL) {
        int star_x = x() - _star->width() / 2 + 10 - viewport.x();
        int star_y = y() - _star->height() / 2 + 10 - viewport.y();

        _star->draw(g, star_x, star_y);
    }

}

void ButtonMenuLevel::modalDraw(const Viewport &viewport, Graphics *g)
{
    draw(viewport, g);
}


void ButtonMenuLevel::star(Sprite *star)
{
    _star = star;
}
