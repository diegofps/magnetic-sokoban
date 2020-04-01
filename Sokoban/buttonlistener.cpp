#include "buttonlistener.h"

#include "object.h"

ButtonListener::ButtonListener() : virtual public Object
{

public:

    void onClick() = 0;

}
