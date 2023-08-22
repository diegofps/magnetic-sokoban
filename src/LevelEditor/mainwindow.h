#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mapeditor.h"
#include "mappack.h"
#include "mapdialog.h"
#include "removemapcommand.h"
#include "movemapdowncommand.h"
#include "movemapupcommand.h"
#include "aboutdialog.h"
#include <QMainWindow>
#include <QStringListModel>
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <commandhistory.h>
#include "imagehandler.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, public CommandsListener
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void onAddMap(int index);

    void onRemoveMap(int oldIndex);

    void onEditMap(int index);

    void onChangeMap(int index, int hSlider, int vSlider);

    void onMoveMap(int newIndex, int oldIndex);

    void onChangeHistory();

private:

    void updateListMap();

    void updateLevelButtonsAccess();

    void showError(QString msg);

    void saveToFile(QString fileName);

    void openFromFile(QString fileName);

    void updateHistoryDependantButtons();

    //void populateListObjects();

    void createPencils();

private slots:

    void on_btAddLevel_clicked();

    void on_listMaps_doubleClicked(const QModelIndex &index);

    void on_btRemoveLevel_clicked();

    void on_listMaps_currentRowChanged(int currentRow);

    void on_btMoveLevelUp_clicked();

    void on_btMoveLevelDown_clicked();

    void on_actionGrid_triggered(bool checked);

    void on_actionSave_as_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_actionNew_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionAbout_triggered();

private:

    Ui::MainWindow *ui;

    MapPack *currentMapPack;

    MapEditor *mapEditor;

    QString currentFileName;

    CommandHistory *commandHistory;

    ImageHandler imageHandler;

};

#endif // MAINWINDOW_H
