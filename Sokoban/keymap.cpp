#include "keymap.h"

KeyMap::KeyMap()
{
    _map[Qt::Key_Left] = KeyListener::Left;
    _map[Qt::Key_Right] = KeyListener::Right;
    _map[Qt::Key_Up] = KeyListener::Up;
    _map[Qt::Key_Down] = KeyListener::Down;
    _map[Qt::Key_Escape] = KeyListener::Escape;
    _map[Qt::Key_W] = KeyListener::Key_w;
    _map[Qt::Key_F] = KeyListener::Key_f;
}

KeyListener::Key KeyMap::convert(int key)
{
    std::map<int, KeyListener::Key>::iterator it;
    it = _map.find(key);

    if (it == _map.end()) return KeyListener::Unknown;
    return (*it).second;
}
