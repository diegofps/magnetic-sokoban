#ifndef PUTOBJECTCOMMAND_H
#define PUTOBJECTCOMMAND_H

#include "command.h"
#include "mappack.h"
#include "mapobject.h"

class PutObjectCommand : public Command
{

public:

    PutObjectCommand(MapObject oldObject, MapObject newObject, int x, int y, int hSlider, int vSlider, int mapId, MapPack *mapPack);

    virtual ~PutObjectCommand() { }

    virtual void execute();

    virtual void unexecute();

    virtual void setCommandsListener(CommandsListener *listener);

private:

    MapObject _oldObject;

    MapObject _newObject;

    int _x;

    int _y;

    int _mapId;

    MapPack *_mapPack;

    CommandsListener *_listener;

    int _hSlider;

    int _vSlider;

};

#endif // PUTOBJECTCOMMAND_H
