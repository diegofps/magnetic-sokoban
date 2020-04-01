#ifndef BUTTONLISTENER_H
#define BUTTONLISTENER_H

class Button;

class ButtonListener
{

public:

    virtual void onClick(Button *button) = 0;

};

#endif // BUTTONLISTENER_H
