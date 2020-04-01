#ifndef KEYMAP_H
#define KEYMAP_H

#include <QtCore>

#include "keylistener.h"

class KeyMap
{

public:

    KeyMap();

    KeyListener::Key convert(int key);

private:

    std::map<int, KeyListener::Key> _map;

};

#endif // KEYMAP_H
