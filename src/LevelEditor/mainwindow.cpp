#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include "floorpencil.h"
#include "robotpencil.h"
#include "wallpencil.h"
#include "rigidpencil.h"
#include "platepencil.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Initialize GUI
    ui->setupUi(this);

    // Initialize CommandHistory
    commandHistory = new CommandHistory(this);

    // Initialize empty mapPack
    currentMapPack = new MapPack();

    // Initialize mapEditor and objects buttons
    mapEditor = new MapEditor(ui->scrollAreaMap, ui->listObjects, commandHistory, currentMapPack, &imageHandler);

    // Add pencils to mapEditor
    createPencils();

    // Add walls, robots and floor types
    //populateListObjects();

    // Initialize listLevels control buttons
    updateLevelButtonsAccess();
    updateHistoryDependantButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btAddLevel_clicked()
{

    MapDialog mapDialog(currentMapPack, commandHistory);
    mapDialog.setModal(true);
    mapDialog.exec();

    /*
    if (mapDialog.exec() == QDialog::Accepted) {
        if (ui->listMaps->count() == 0) {
            updateListMap();
            ui->listMaps->setCurrentRow(0);
        } else {
            int index = ui->listMaps->currentRow();
            updateListMap();
            ui->listMaps->setCurrentRow(index);
        }

        updateLevelButtonsAccess();
    }
    */
}

void MainWindow::updateListMap()
{
    ui->listMaps->clear();

    for (std::vector<Map*>::iterator it = currentMapPack->all()->begin(); it != currentMapPack->all()->end(); ++it)
        ui->listMaps->addItem(QString((*it)->name().c_str()));
}

void MainWindow::on_listMaps_doubleClicked(const QModelIndex &index)
{
    MapDialog mapDialog(currentMapPack, commandHistory, index.row());
    mapDialog.setModal(true);
    mapDialog.exec();
    /*
    if (mapDialog.exec() == QDialog::Accepted) {
        int index = ui->listMaps->currentRow();
        updateListMap();
        ui->listMaps->setCurrentRow(index);
    }
    */
}

void MainWindow::on_btRemoveLevel_clicked()
{
    int index = ui->listMaps->currentRow();
    commandHistory->add(new RemoveMapCommand(currentMapPack, index));
/*
    currentMapPack->removeAt(index);
    delete ui->listMaps->item(index);
    updateLevelButtonsAccess();
    */
}

void MainWindow::updateLevelButtonsAccess()
{
    if (ui->listMaps->count() == 0) {
        ui->btRemoveLevel->setEnabled(false);
        ui->btMoveLevelDown->setEnabled(false);
        ui->btMoveLevelUp->setEnabled(false);
        return;
    } else {
        ui->btRemoveLevel->setEnabled(true);
    }

    int currentRow = ui->listMaps->currentRow();

    if (currentRow == 0) {
        ui->btMoveLevelUp->setEnabled(false);
    } else {
        ui->btMoveLevelUp->setEnabled(true);
    }

    if (currentRow == ui->listMaps->count() - 1) {
        ui->btMoveLevelDown->setEnabled(false);
    } else {
        ui->btMoveLevelDown->setEnabled(true);
    }
}

void MainWindow::on_listMaps_currentRowChanged(int currentRow)
{
    updateLevelButtonsAccess();
    mapEditor->setMap(currentRow);
    mapEditor->updateGeometry();
    mapEditor->repaint();
}

void MainWindow::on_btMoveLevelUp_clicked()
{
    int index = ui->listMaps->currentRow();
    commandHistory->add(new MoveMapUpCommand(index, currentMapPack));
    /*
    currentMapPack->moveUp(index);
    updateListMap();
    ui->listMaps->setCurrentRow(index - 1);
    */
}

void MainWindow::on_btMoveLevelDown_clicked()
{
    int index = ui->listMaps->currentRow();
    commandHistory->add(new MoveMapDownCommand(index, currentMapPack));
    /*
    int index = ui->listMaps->currentRow();
    currentMapPack->moveDown(index);

    updateListMap();
    ui->listMaps->setCurrentRow(index + 1);
    */
}

void MainWindow::on_actionGrid_triggered(bool checked)
{
    mapEditor->setShowGrid(checked);
}

void MainWindow::on_actionSave_as_triggered()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save as"), currentFileName,
                                                    tr("Map Packs (*.mpk);;All Files (*)"),
                                                    &selectedFilter, options);

    if (!fileName.isEmpty()) {
        if (!fileName.endsWith(".mpk")) fileName.append(".mpk");
        saveToFile(fileName);
    }

}

void MainWindow::on_actionSave_triggered()
{
    if (currentFileName.isEmpty()) on_actionSave_as_triggered();
    else saveToFile(currentFileName);
}

void MainWindow::on_actionOpen_triggered()
{
    if (commandHistory->atSavePoint()) {
        QFileDialog::Options options;
        QString selectedFilter;
        QString fileName = QFileDialog::getOpenFileName(this,
                                    tr("Open"),
                                    currentFileName,
                                    tr("Map Packs (*.mpk);;All Files (*)"),
                                    &selectedFilter,
                                    options);

        if (!fileName.isEmpty()) openFromFile(fileName);
    } else {
        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, tr("Save current work"),
                              tr("You have unsaved changes. Would you like to save them first?"),
                              QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            on_actionSave_triggered();
            if (commandHistory->atSavePoint()) {
                QFileDialog::Options options;
                QString selectedFilter;
                QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open"),
                                            currentFileName,
                                            tr("Map Packs (*.mpk);;All Files (*)"),
                                            &selectedFilter,
                                            options);

                if (!fileName.isEmpty()) openFromFile(fileName);
            }
        } else {
            QFileDialog::Options options;
            QString selectedFilter;
            QString fileName = QFileDialog::getOpenFileName(this,
                                        tr("Open"),
                                        currentFileName,
                                        tr("Map Packs (*.mpk);;All Files (*)"),
                                        &selectedFilter,
                                        options);

            if (!fileName.isEmpty()) openFromFile(fileName);
        }
    }
}

void MainWindow::saveToFile(QString fileName)
{
    const char * path = fileName.toLocal8Bit().constData();

    if (!currentMapPack->exportTo(path)) {
        showError("Could not save the file, check if you have write permissions on this file or folder");
    } else {
        commandHistory->setSavePoint();
        currentFileName = fileName;
    }
}

void MainWindow::openFromFile(QString fileName)
{
    MapPack *newPack = new MapPack();
    const char * path = fileName.toLocal8Bit().constData();

    if (newPack->importFrom(path)) {
        delete currentMapPack;
        currentFileName = fileName;
        currentMapPack = newPack;
        mapEditor->setMapPack(currentMapPack);
        updateListMap();
        updateLevelButtonsAccess();
        commandHistory->clear();
        if (ui->listMaps->count() != 0)
            ui->listMaps->setCurrentRow(0);
    }
    else {
        showError("This file is corrupted or is not a valid map file");
        delete newPack;
    };
}

void MainWindow::showError(QString msg)
{
    QMessageBox msgBox(QMessageBox::Critical, tr("Error"), msg, QMessageBox::Ok, this);
    msgBox.addButton(tr("&Ok"), QMessageBox::AcceptRole);
    msgBox.exec();
}

void MainWindow::on_actionQuit_triggered()
{
    if (commandHistory->atSavePoint()) {
        this->close();
    } else {
        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, tr("Save current work"),
                              tr("You have unsaved changes. Would you like to save them first?"),
                              QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            on_actionSave_triggered();
            if (commandHistory->atSavePoint()) {
                this->close();
            }
        } else {
            this->close();
        }
    }
}

void MainWindow::on_actionNew_triggered()
{
    if (commandHistory->atSavePoint()) {
        delete currentMapPack;
        currentMapPack = new MapPack();
        currentFileName = "";
        updateListMap();
        commandHistory->clear();
        updateLevelButtonsAccess();
    } else {
        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, tr("Save current work"),
                              tr("You have unsaved changes. Would you like to save them first?"),
                              QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            on_actionSave_triggered();
            if (commandHistory->atSavePoint()) {
                delete currentMapPack;
                currentMapPack = new MapPack();
                currentFileName = "";
                updateListMap();
                commandHistory->clear();
                updateLevelButtonsAccess();
            }
        } else {
            delete currentMapPack;
            currentMapPack = new MapPack();
            currentFileName = "";
            updateListMap();
            commandHistory->clear();
            updateLevelButtonsAccess();
        }
    }
}

void MainWindow::updateHistoryDependantButtons()
{
    if (commandHistory->atSavePoint()) {
        ui->actionSave->setEnabled(false);
    } else {
        ui->actionSave->setEnabled(true);
    }

    if (commandHistory->hasNext()) {
        ui->actionRedo->setEnabled(true);
    } else {
        ui->actionRedo->setEnabled(false);
    }

    if (commandHistory->hasPrevious()) {
        ui->actionUndo->setEnabled(true);
    } else {
        ui->actionUndo->setEnabled(false);
    }
}

void MainWindow::onAddMap(int index)
{
    updateListMap();
    ui->listMaps->setCurrentRow(index);
}

void MainWindow::onRemoveMap(int)
{
    int index = ui->listMaps->currentRow();
    updateListMap();
    updateLevelButtonsAccess();

    if (ui->listMaps->count() == 0)
        return;

    if (index == ui->listMaps->count())
        ui->listMaps->setCurrentRow(index - 1);
    else
        ui->listMaps->setCurrentRow(index);
}

void MainWindow::onEditMap(int index)
{
    updateListMap();
    ui->listMaps->setCurrentRow(index);
    mapEditor->updateGeometry();
}

void MainWindow::onChangeMap(int index, int hSlider, int vSlider)
{
    ui->listMaps->setCurrentRow(index);
    ui->scrollAreaMap->horizontalScrollBar()->setValue(hSlider);
    ui->scrollAreaMap->verticalScrollBar()->setValue(vSlider);
    mapEditor->repaint();
}

void MainWindow::onMoveMap(int newIndex, int)
{
    updateListMap();
    ui->listMaps->setCurrentRow(newIndex);
}

void MainWindow::on_actionUndo_triggered()
{
    commandHistory->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    commandHistory->redo();
}

void MainWindow::onChangeHistory()
{
    updateHistoryDependantButtons();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}

/*
void MainWindow::populateListObjects()
{
    QPixmap robotNorth; robotNorth.load(":/icons/robotNorth.svg");
    QPixmap robotSouth; robotSouth.load(":/icons/robotSouth.svg");
    QPixmap robotEast; robotEast.load(":/icons/robotEast.svg");
    QPixmap robotWest; robotWest.load(":/icons/robotWest.svg");

    QPixmap floor; floor.load(":/icons/floor.svg");
    QPixmap floorObjective; floorObjective.load(":/icons/floorObjective.svg");

    QPixmap rigidWall;  std::cout << rigidWall.load(":/icons/rigidWall.svg");
    QPixmap moveblaWall;  std::cout << moveblaWall.load(":/icons/moveblaWall.svg");

    QPixmap magneticNorthNorth; magneticNorthNorth.load(":/icons/magneticNorthNorth.svg");
    QPixmap magneticNorthSouth; magneticNorthSouth.load(":/icons/magneticNorthSouth.svg");
    QPixmap magneticNorthEast; magneticNorthEast.load(":/icons/magneticNorthEast.svg");
    QPixmap magneticNorthWest; magneticNorthWest.load(":/icons/magneticNorthWest.svg");

    QPixmap magneticSouthNorth; magneticSouthNorth.load(":/icons/magneticSouthNorth.svg");
    QPixmap magneticSouthSouth; magneticSouthSouth.load(":/icons/magneticSouthSouth.svg");
    QPixmap magneticSouthEast; magneticSouthEast.load(":/icons/magneticSouthEast.svg");
    QPixmap magneticSouthWest; magneticSouthWest.load(":/icons/magneticSouthWest.svg");

    QPixmap metalNorth; metalNorth.load(":/icons/metalNorth.svg");
    QPixmap metalSouth; metalSouth.load(":/icons/metalSouth.svg");
    QPixmap metalEast; metalEast.load(":/icons/metalEast.svg");
    QPixmap metalWest; metalWest.load(":/icons/metalWest.svg");

    { // Add Robots
        {
            QPixmap pixmap(48, 48);
            QPainter painter(&pixmap);
            painter.drawPixmap(0,0,floor);
            painter.drawPixmap(0,0,robotNorth);
            mapEditor->addObjectType(pixmap, "Robot N");
        }

        {
            QPixmap pixmap(48, 48);
            QPainter painter(&pixmap);
            painter.drawPixmap(0,0,floor);
            painter.drawPixmap(0,0,robotSouth);
            mapEditor->addObjectType(pixmap, "Robot S");
        }

        {
            QPixmap pixmap(48, 48);
            QPainter painter(&pixmap);
            painter.drawPixmap(0,0,floor);
            painter.drawPixmap(0,0,robotEast);
            mapEditor->addObjectType(pixmap, "Robot E");
        }

        {
            QPixmap pixmap(48, 48);
            QPainter painter(&pixmap);
            painter.drawPixmap(0,0,floor);
            painter.drawPixmap(0,0,robotWest);
            mapEditor->addObjectType(pixmap, "Robot W");
        }
    }

    { // Add Floors
        {
            mapEditor->addObjectType(floor, "Floor");
        }

        {
            QPixmap pixmap(48, 48);
            QPainter painter(&pixmap);
            painter.drawPixmap(0,0,floor);
            painter.drawPixmap(0,0,floorObjective);
            mapEditor->addObjectType(pixmap, "Floor Objective");
        }
    }

    { // Add Mobile Walls and then Rigid Walls
        char title[5]; title[4] = '\0';
        int w, i,j,k,l;
        for (w=0;w<2;++w) {
            for (i=0;i<4;++i) {
                for (j=0;j<4;++j) {
                    for (k=0;k<4;++k) {
                        for (l=0;l<4;++l) {
                            QPixmap pixmap(48, 48);
                            QPainter painter(&pixmap);
                            painter.drawPixmap(0,0,floor);

                            if (w == 0) painter.drawPixmap(0,0,moveblaWall);
                            else painter.drawPixmap(0,0,rigidWall);


                            switch(i) {
                                case 0: painter.drawPixmap(0,0,magneticNorthEast); title[0] = 'N'; break;
                                case 1: painter.drawPixmap(0,0,magneticSouthEast); title[0] = 'S'; break;
                                case 2: painter.drawPixmap(0,0,metalEast); title[0] = 'M'; break;
                                case 3: title[0] = 'E'; break;
                            }

                            switch(j) {
                                case 0: painter.drawPixmap(0,0,magneticNorthNorth); title[1] = 'N'; break;
                                case 1: painter.drawPixmap(0,0,magneticSouthNorth); title[1] = 'S'; break;
                                case 2: painter.drawPixmap(0,0,metalNorth); title[1] = 'M'; break;
                                case 3: title[1] = 'E'; break;
                            }

                            switch(k) {
                                case 0: painter.drawPixmap(0,0,magneticNorthWest); title[2] = 'N'; break;
                                case 1: painter.drawPixmap(0,0,magneticSouthWest); title[2] = 'S'; break;
                                case 2: painter.drawPixmap(0,0,metalWest); title[2] = 'M'; break;
                                case 3: title[2] = 'E'; break;
                            }

                            switch(l) {
                                case 0: painter.drawPixmap(0,0,magneticNorthSouth); title[3] = 'N'; break;
                                case 1: painter.drawPixmap(0,0,magneticSouthSouth); title[3] = 'S'; break;
                                case 2: painter.drawPixmap(0,0,metalSouth); title[3] = 'M'; break;
                                case 3: title[3] = 'E'; break;
                            }

                            mapEditor->addObjectType(pixmap, QString(title));
                        }
                    }
                }
            }
        }
    }

}
*/
void MainWindow::createPencils()
{
    mapEditor->addPencil(new FloorPencil(imageHandler.floor(), false));
    mapEditor->addPencil(new FloorPencil(imageHandler.floorObjective(), true));

    mapEditor->addPencil(new RobotPencil(imageHandler.robotNorth(), MapObject::North));
    mapEditor->addPencil(new RobotPencil(imageHandler.robotSouth(), MapObject::South));
    mapEditor->addPencil(new RobotPencil(imageHandler.robotEast(), MapObject::East));
    mapEditor->addPencil(new RobotPencil(imageHandler.robotWest(), MapObject::West));

    mapEditor->addPencil(new WallPencil(imageHandler.wallRigidMagneticNorth(), MapObject::MagneticNorth, true));
    mapEditor->addPencil(new WallPencil(imageHandler.wallRigidMagneticSouth(), MapObject::MagneticSouth, true));
    mapEditor->addPencil(new WallPencil(imageHandler.wallRigidMetal(), MapObject::Metal, true));
    mapEditor->addPencil(new WallPencil(imageHandler.wallRigidNeutral(), MapObject::Neutral, true));

    mapEditor->addPencil(new WallPencil(imageHandler.wallMoveblaMagneticNorth(), MapObject::MagneticNorth, false));
    mapEditor->addPencil(new WallPencil(imageHandler.wallMoveblaMagneticSouth(), MapObject::MagneticSouth, false));
    mapEditor->addPencil(new WallPencil(imageHandler.wallMoveblaMetal(), MapObject::Metal, false));
    mapEditor->addPencil(new WallPencil(imageHandler.wallMoveblaNeutral(), MapObject::Neutral, false));

    mapEditor->addPencil(new RigidPencil(imageHandler.wallRigid(), true));
    mapEditor->addPencil(new RigidPencil(imageHandler.wallMovebla(), false));

    mapEditor->addPencil(new PlatePencil(imageHandler.magneticNorthNorth(), MapObject::MagneticNorth, MapObject::North));
    mapEditor->addPencil(new PlatePencil(imageHandler.magneticNorthSouth(), MapObject::MagneticNorth, MapObject::South));
    mapEditor->addPencil(new PlatePencil(imageHandler.magneticNorthEast(), MapObject::MagneticNorth, MapObject::East));
    mapEditor->addPencil(new PlatePencil(imageHandler.magneticNorthWest(), MapObject::MagneticNorth, MapObject::West));

    mapEditor->addPencil(new PlatePencil(imageHandler.magneticSouthNorth(), MapObject::MagneticSouth, MapObject::North));
    mapEditor->addPencil(new PlatePencil(imageHandler.magneticSouthSouth(), MapObject::MagneticSouth, MapObject::South));
    mapEditor->addPencil(new PlatePencil(imageHandler.magneticSouthEast(), MapObject::MagneticSouth, MapObject::East));
    mapEditor->addPencil(new PlatePencil(imageHandler.magneticSouthWest(), MapObject::MagneticSouth, MapObject::West));

    mapEditor->addPencil(new PlatePencil(imageHandler.metalNorth(), MapObject::Metal, MapObject::North));
    mapEditor->addPencil(new PlatePencil(imageHandler.metalSouth(), MapObject::Metal, MapObject::South));
    mapEditor->addPencil(new PlatePencil(imageHandler.metalEast(), MapObject::Metal, MapObject::East));
    mapEditor->addPencil(new PlatePencil(imageHandler.metalWest(), MapObject::Metal, MapObject::West));

    mapEditor->addPencil(new PlatePencil(imageHandler.neutralNorth(), MapObject::Neutral, MapObject::North));
    mapEditor->addPencil(new PlatePencil(imageHandler.neutralSouth(), MapObject::Neutral, MapObject::South));
    mapEditor->addPencil(new PlatePencil(imageHandler.neutralEast(), MapObject::Neutral, MapObject::East));
    mapEditor->addPencil(new PlatePencil(imageHandler.neutralWest(), MapObject::Neutral, MapObject::West));
}
