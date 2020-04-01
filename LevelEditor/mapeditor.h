#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QPainter>
#include <QWidget>
#include <QScrollArea>
#include <QListWidget>
#include <QIcon>
#include <QMouseEvent>
#include <QScrollBar>
#include <vector>
#include "map.h"
#include "commandhistory.h"
#include "putobjectcommand.h"

class MapPencil;
class ImageHandler;

class MapEditor : public QWidget
{

public:

    MapEditor(QScrollArea * scrollArea, QListWidget * listWidget, CommandHistory *commandHistory, MapPack *mapPack, ImageHandler *imageHandler);

    /*
    void addObjectType(QString imagePath, QString name);

    void addObjectType(QPixmap pixmap, QString name);
    */

    void addPencil(MapPencil *pencil);

    void setMap(int mapId);

    void setShowGrid(bool showGrid) { _showGrid = showGrid; repaint(); }

    QSize sizeHint() const;

    QSize minimumSizeHint() const { return QSize(0, 0); }

    void setMapPack(MapPack *mapPack);

protected:

    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

private:

    void onMouseHitEvent(QMouseEvent *event);

    QScrollArea * _scrollArea;

    QListWidget * _listWidget;

    QPen pen;

    int _mapId;

    //std::vector<QPixmap> *objectTypesPixmaps;

    std::vector<MapPencil*> _pencils;

    bool _showGrid;

    CommandHistory *_commandHistory;

    MapPack *_mapPack;

    ImageHandler *_imageHandler;

};

#endif // MAPEDITOR_H
