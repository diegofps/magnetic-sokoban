#include "qengine.h"
#include "ui_qengine.h"
#include "room.h"
#include "background.h"
#include "object.h"
#include "sprite.h"
#include "mouselistener.h"
#include "helpers.h"
#include "viewportrefresher.h"
#include "steplistener.h"

QEngine::QEngine(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::QEngine),
    _currentRoom(NULL), _currentRunningRoom(NULL), _goToRoom(NULL), _lastMouseX(-1), _lastMouseY(-1), _endGame(false), _closeCurrentRunningRoom(false)
{
    ui->setupUi(this);
    ui->gameWidget->setListener(this);

    _graphics = ui->gameWidget;

    setFixedSize(800, 600);
}

QEngine::~QEngine()
{
    delete ui;
}

void QEngine::start()
{
    show();

    //setWindowState(Qt::WindowFullScreen);
}

void QEngine::endGame()
{
    _endGame = true;
}

void QEngine::goTo(Room *room)
{
    _goToRoom = room;
}

void QEngine::closeCurrentModalRoom(int resultCode)
{
    _modalResultCode = resultCode;
    _closeCurrentRunningRoom = true;
}

Graphics * QEngine::graphics()
{
    return _graphics;
}

void QEngine::immediatelyGoToRoom(Room *room)
{
    while(_currentRunningRoom != NULL) {
        _currentRunningRoom->onLeave();
        _currentRunningRoom->clear();
        _currentRunningRoom = _currentRunningRoom->parent();
    }

    _currentRoom = room;
    _currentRunningRoom = _currentRoom;

    _goToRoom = NULL;

    _lastMouseX = -1;
    _lastMouseY = -1;

    if (_currentRoom == NULL) return;

    _currentRunningRoom->onEnter();
    while(_currentRunningRoom->modal() != NULL) {
        _currentRunningRoom = _currentRunningRoom->modal();
        _currentRunningRoom->onEnter();
    }
}

void QEngine::onStep()
{

    if (_endGame) {
        immediatelyGoToRoom(NULL);
        close();
        return;
    }

    if (_goToRoom != NULL) {
        immediatelyGoToRoom(_goToRoom);
    }

    if (_closeCurrentRunningRoom) {
        _closeCurrentRunningRoom = false;

        if (_currentRunningRoom->parent() != NULL) {
            Room *modal = _currentRunningRoom;
            _currentRunningRoom->onLeave();
            _currentRunningRoom = _currentRunningRoom->parent();
            _currentRunningRoom->modal(NULL);
            _currentRunningRoom->onModalRoomClose(modal, _modalResultCode);
        }
    }

     else {

        while (_currentRunningRoom->modal() != NULL) {
            _currentRunningRoom = _currentRunningRoom->modal();
            _currentRunningRoom->onEnter();
        }

        _currentRunningRoom->onStep();
        _currentRunningRoom->onViewportRefresher();

    }
}

void QEngine::onPaint()
{
    if (_currentRoom != NULL)
        _currentRoom->onDraw(graphics());
}

void QEngine::onMousePress(const MouseListener::Buttons buttons, const int x, const int y)
{
    if (_currentRunningRoom != NULL)
        _currentRunningRoom->onMousePress(buttons, x, y);
}

void QEngine::onMouseMove(const MouseListener::Buttons buttons, const int x, const int y)
{
    if (_currentRunningRoom != NULL)
        _currentRunningRoom->onMouseMove(buttons, x, y, _lastMouseX, _lastMouseY);

    _lastMouseX = x;
    _lastMouseY = y;
}

void QEngine::onMouseRelease(const MouseListener::Buttons buttons, const int x, const int y)
{
    if (_currentRunningRoom != NULL)
        _currentRunningRoom->onMouseRelease(buttons, x, y);
}

void QEngine::onKeyPress(KeyListener::Key key)
{
    if (_currentRunningRoom != NULL)
        _currentRunningRoom->onKeyPress(key);
}

void QEngine::onKeyRelease(KeyListener::Key key)
{
    if (_currentRunningRoom != NULL)
        _currentRunningRoom->onKeyRelease(key);
}
