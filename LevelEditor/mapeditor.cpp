#include "mapeditor.h"
#include "mapobject.h"
#include "imagehandler.h"
#include "mappencil.h"

MapEditor::MapEditor(QScrollArea * scrollArea, QListWidget * listWidget, CommandHistory *commandHistory, MapPack *mapPack, ImageHandler *imageHandler):
    _scrollArea(scrollArea), _listWidget(listWidget), _mapId(-1), _showGrid(true),
    _commandHistory(commandHistory), _mapPack(mapPack), _imageHandler(imageHandler)
{
    QSizePolicy policy;
    policy.setHorizontalPolicy(QSizePolicy::Fixed);
    policy.setVerticalPolicy(QSizePolicy::Fixed);
    policy.setHorizontalStretch(0);
    policy.setVerticalStretch(0);
    setSizePolicy(policy);

    pen.setWidth(1);
    pen.setColor(QColor(100, 100, 100, 50));

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    _listWidget->setEnabled(false);
    _scrollArea->setWidget(this);
}

/*
void MapEditor::addObjectType(QString imagePath, QString name)
{
    QPixmap pixmap; pixmap.load(imagePath);
    addObjectType(pixmap, name);
}

void MapEditor::addObjectType(QPixmap pixmap, QString name)
{
    objectTypesPixmaps->push_back(pixmap);
    QListWidgetItem *item = new QListWidgetItem(QIcon(pixmap), name);

    _listWidget->addItem(item);

    if (objectTypesPixmaps->size() == 1)
        _listWidget->setCurrentRow(0);
}
*/

void MapEditor::addPencil(MapPencil *pencil)
{
    _pencils.push_back(pencil);
    _listWidget->addItem(new QListWidgetItem(QIcon(pencil->pixmap()), pencil->name()));

    if (_pencils.size() == 1)
        _listWidget->setCurrentRow(0);
}

void MapEditor::paintEvent(QPaintEvent *)
{
    Map *map = _mapPack->at(_mapId);

    if (map == NULL)
        return;

    QPainter painter(this);
    painter.setPen(pen);

    const QPixmap *pixmap;
    for (int y=0;y<map->height();++y)
    {
        for (int x=0;x<map->width();++x)
        {
            pixmap = _imageHandler->imageFor(map->at(x, y));
            if (pixmap != NULL) painter.drawPixmap(x*48, y*48, *pixmap);
        }
    }

    if (!_showGrid)
        return;

    for(int i=0;i<map->width();++i)
    {
        painter.drawLine(i * 48, 0, i * 48, map->height() * 48);
    }

    for(int i=0;i<map->height();++i)
    {
        painter.drawLine(0, i * 48, map->width() * 48, i * 48);
    }

}

QSize MapEditor::sizeHint() const
{
    Map *map = _mapPack->at(_mapId);

    if (map == NULL)
        return QSize(0, 0);
    else
        return QSize(map->width() * 48, map->height() * 48);
}

void MapEditor::mouseMoveEvent(QMouseEvent *event)
{
    onMouseHitEvent(event);
}

void MapEditor::mousePressEvent(QMouseEvent *event)
{
    onMouseHitEvent(event);
}

void MapEditor::onMouseHitEvent(QMouseEvent *event)
{
    if (_mapId == -1)
        return;

    Map *map = _mapPack->at(_mapId);

    if (event->buttons() & Qt::LeftButton)
    {
        int currentRow = _listWidget->currentRow();

        if (currentRow < 0 || currentRow >= (int)_pencils.size())
            return;

        int x = event->x() / 48;
        int y = event->y() / 48;

        MapPencil *pencil = _pencils.at(currentRow);
        MapObject obj1 = map->at(x, y);
        MapObject obj2 = pencil->paint(obj1);

        if (obj1 != obj2)
        {
            int vSlider = _scrollArea->verticalScrollBar()->value();
            int hSlider = _scrollArea->horizontalScrollBar()->value();

            _commandHistory->add(new PutObjectCommand(obj1, obj2, x, y, hSlider, vSlider, _mapId, _mapPack));
        }
    }

    else if (event->buttons() & Qt::RightButton)
    {
        int x = event->x() / 48;
        int y = event->y() / 48;

        MapObject obj1 = map->at(x, y);
        MapObject obj2 = obj1;

        obj2.type(MapObject::None);

        if (obj1 != obj2)
        {
            int vSlider = _scrollArea->verticalScrollBar()->value();
            int hSlider = _scrollArea->horizontalScrollBar()->value();

            _commandHistory->add(new PutObjectCommand(obj1, obj2, x, y, hSlider, vSlider, _mapId, _mapPack));
        }
    }

}

void MapEditor::setMap(int mapId)
{
    Map *map = _mapPack->at(mapId);

    if (map == NULL)
        _listWidget->setEnabled(false);
    else
        _listWidget->setEnabled(true);

    _mapId = mapId;
}

void MapEditor::setMapPack(MapPack *mapPack)
{
    _mapPack = mapPack;
}
