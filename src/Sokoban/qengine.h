#ifndef QENGINE_H
#define QENGINE_H

#include <map>
#include <vector>
#include <QMainWindow>

#include "engine.h"
#include "qgamewidgetlistener.h"

class Graphics;
class ModalRoom;

namespace Ui {
    class QEngine;
}

class QEngine : public QMainWindow, public Engine, public QGameWidgetListener
{
    Q_OBJECT

public:

    explicit QEngine(QWidget *parent = 0);

    ~QEngine();

    void start();

    void endGame();

    void goTo(Room *room);

    void closeCurrentModalRoom(int resultCode);

    Graphics * graphics();


    void onStep();

    void onPaint();

    void onMousePress(const MouseListener::Buttons buttons, const int x, const int y);

    void onMouseMove(const MouseListener::Buttons buttons, const int x, const int y);

    void onMouseRelease(const MouseListener::Buttons buttons, const int x, const int y);

    void onKeyPress(KeyListener::Key key);

    void onKeyRelease(KeyListener::Key key);


private:

    void immediatelyGoToRoom(Room *room);

private:

    Ui::QEngine *ui;

    Room *_currentRoom;

    Room *_currentRunningRoom;

    Room *_goToRoom;

    Graphics *_graphics;

    int _lastMouseX;

    int _lastMouseY;

    bool _endGame;

    bool _closeCurrentRunningRoom;

    int _modalResultCode;

 };

#endif // QENGINE_H
