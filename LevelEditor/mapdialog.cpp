#include "mapdialog.h"
#include "ui_mapdialog.h"

MapDialog::MapDialog(MapPack *mapPack, CommandHistory *commandHistory, QWidget *parent) :
    QDialog(parent), ui(new Ui::MapDialog),
    _mapPack(mapPack), _mapId(-1), _commandHistory(commandHistory)
{
    ui->setupUi(this);
}

MapDialog::MapDialog(MapPack *mapPack, CommandHistory *commandHistory, int mapId, QWidget *parent) :
    QDialog(parent), ui(new Ui::MapDialog),
    _mapPack(mapPack), _mapId(mapId), _commandHistory(commandHistory)
{
    ui->setupUi(this);

    Map *map = mapPack->at(mapId);

    ui->labelTitle->setText("Edit Level");
    ui->lineEditName->setText(map->name().c_str());
    ui->spinBoxSizeX->setValue(map->width());
    ui->spinBoxSizeY->setValue(map->height());
    ui->spinBoxStepsForGold->setValue(map->stepsForGold());
    ui->spinBoxStepsForSilver->setValue(map->stepsForSilver());
    ui->spinBoxStepsForBronze->setValue(map->stepsForBronze());
}

MapDialog::~MapDialog()
{
    delete ui;
}

void MapDialog::on_buttonBox_accepted()
{
    const char *name = ui->lineEditName->text().toLocal8Bit().constData();
    int width = ui->spinBoxSizeX->value();
    int height = ui->spinBoxSizeY->value();
    int stepsForGold = ui->spinBoxStepsForGold->value();
    int stepsForSilver = ui->spinBoxStepsForSilver->value();
    int stepsForBronze = ui->spinBoxStepsForBronze->value();

    if (_mapId == -1) {
        _commandHistory->add(new AddMapCommand(
                                 name, width, height,
                                 stepsForGold, stepsForSilver, stepsForBronze,
                                 _mapPack));
    }

    else {
        _commandHistory->add(new EditMapCommand(
                                 name, width, height,
                                 stepsForGold, stepsForSilver, stepsForBronze,
                                 _mapPack, _mapId));
    }
}
