#ifndef KEYLISTENER_H
#define KEYLISTENER_H

class KeyListener
{

public:

    enum Key {
        Left,
        Right,
        Up,
        Down,
        Escape,
        Key_w,
        Key_f,
        Unknown
    };

    virtual void onKeyPress(Key key);

    virtual void onKeyRelease(Key key);

};

#endif // KEYLISTENER_H
