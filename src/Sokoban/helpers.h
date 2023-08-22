#ifndef HELPERS_H
#define HELPERS_H

namespace helpers {

    inline bool
    pointInsideBox(const int px, const int py, const int bx, const int by, const int bw, const int bh)
    {
        return (px >= bx && px <= bx + bw && py >= by && py <= by + bh);
    }

}

#endif // HELPERS_H
