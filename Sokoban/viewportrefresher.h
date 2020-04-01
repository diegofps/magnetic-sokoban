#ifndef VIEWPORTREFRESHER_H
#define VIEWPORTREFRESHER_H

class Viewport;

class ViewportRefresher
{

public:

    virtual void refresh(Viewport & viewport) = 0;

};

#endif // VIEWPORTREFRESHER_H
