#ifndef BUTTONQUIT_H
#define BUTTONQUIT_H

#include "button.h"

class Engine;

class ButtonQuit : public Button
{

public:

    ButtonQuit(Engine *engine);

    void onClick(int buttons);

};

#endif // BUTTONQUIT_H
