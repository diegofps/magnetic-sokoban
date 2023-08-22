#include "putobjectcommand.h"

PutObjectCommand::PutObjectCommand(MapObject oldObject, MapObject newObject, int x, int y, int hSlider, int vSlider, int mapId, MapPack *mapPack) :
    _oldObject(oldObject), _newObject(newObject), _x(x), _y(y), _mapId(mapId), _mapPack(mapPack), _hSlider(hSlider), _vSlider(vSlider)
{

}

void PutObjectCommand::execute()
{
    _mapPack->at(_mapId)->put(_newObject, _x, _y);

    if (_listener != NULL)
        _listener->onChangeMap(_mapId, _hSlider, _vSlider);
}

void PutObjectCommand::unexecute()
{
    _mapPack->at(_mapId)->put(_oldObject, _x, _y);

    if (_listener != NULL)
        _listener->onChangeMap(_mapId, _hSlider, _vSlider);
}

void PutObjectCommand::setCommandsListener(CommandsListener *listener)
{
    _listener = listener;
}
