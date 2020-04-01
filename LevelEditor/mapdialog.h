#ifndef MAPDIALOG_H
#define MAPDIALOG_H

#include <QDialog>
#include <iostream>
#include "mappack.h"
#include "commandhistory.h"
#include "editmapcommand.h"
#include "addmapcommand.h"

namespace Ui {
    class MapDialog;
}

class MapDialog : public QDialog
{
    Q_OBJECT

public:

    explicit MapDialog(MapPack *mapPack, CommandHistory *commandHistory, QWidget *parent = 0);

    explicit MapDialog(MapPack *mapPack, CommandHistory *commandHistory, int mapId, QWidget *parent = 0);

    ~MapDialog();

private slots:

    void on_buttonBox_accepted();

private:

    Ui::MapDialog *ui;

    MapPack *_mapPack;

    int _mapId;

    CommandHistory *_commandHistory;

};

#endif // MAPDIALOG_H
