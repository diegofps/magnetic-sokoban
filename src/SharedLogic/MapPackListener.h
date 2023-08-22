#ifndef MAPPACKLISTENER_H
#define MAPPACKLISTENER_H

class MapPackListener
{

public:

    virtual void onAddMap(int index) = 0;

    virtual void onRemoveMap(int oldIndex) = 0;

    virtual void onChangeMap(int index) = 0;

    virtual void onMoveMap(int newIndex, int oldIndex) = 0;

};

#endif // MAPPACKLISTENER_H
