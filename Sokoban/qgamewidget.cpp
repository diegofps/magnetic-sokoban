#include "qgamewidget.h"
#include "qgameimage.h"
#include "qgamewidgetlistener.h"
#include "mouselistener.h"
#include <QMouseEvent>
#include <iostream>
#include "motionbackground.h"

QGameWidget::QGameWidget(QWidget *parent) :
    QGLWidget(parent), _listener(NULL)
{
    setFocus();
    setMouseTracking(true);
    setAutoBufferSwap(false);
    installEventFilter(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(20);
}

void
QGameWidget::setListener(QGameWidgetListener *listener)
{
    _listener = listener;
}

void QGameWidget::focusOutEvent(QFocusEvent *)
{
    setFocus();
}

Image *
QGameWidget::newImage(const char *filePath)
{
    QPixmap pixmap;

    if (pixmap.load(filePath)) {
        return new QGameImage(pixmap);
    } else {
        std::cout << "Warning! Could not load image \"" << filePath << "\"" << std::endl;
        return NULL;
    }
}

MotionBackground *
QGameWidget::newMotionBackground(Image * image, const float xSpeed, const float ySpeed)
{
    return new MotionBackground(image, xSpeed, ySpeed);
}

void
QGameWidget::drawImage(Image *image, int x, int y)
{
    if (image == NULL)
        return;

    QGameImage *qImage = static_cast<QGameImage*>(image);
    _painter->drawPixmap(x, y, qImage->pixmap());
}

void
QGameWidget::drawSubImage(Image * image, int x, int y, int imX, int imY, int imW, int imH)
{
    if (image == NULL)
        return;

    QGameImage *qImage = static_cast<QGameImage*>(image);
    _painter->drawPixmap(x, y, qImage->pixmap(), imX, imY, imW, imH);
}

void
QGameWidget::paintGL()
{
    if (_listener == NULL)
        return;

    _listener->onStep();

    QPainter painter(this);
    painter.scale(width()/800.0,height()/600.0);
    _painter = &painter;
    _listener->onPaint();
    painter.end();
    swapBuffers();
}

void QGameWidget::mousePressEvent(QMouseEvent *event)
{
    if (_listener != NULL)
        _listener->onMousePress(
                    qtMouseButtons2MouseListenerButtons(event->buttons()),
                    event->x()*800.0/width(), event->y()*600.0/height());
}

void QGameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (_listener != NULL)
        _listener->onMouseRelease(
                    qtMouseButtons2MouseListenerButtons(event->buttons()),
                    event->x()*800.0/width(), event->y()*600.0/height());
}

MouseListener::Buttons
QGameWidget::qtMouseButtons2MouseListenerButtons(Qt::MouseButtons qtButtons)
{
    MouseListener::Buttons buttons = MouseListener::NONE;

    buttons |= qtButtons | Qt::LeftButton ? MouseListener::BUTTON_LEFT : MouseListener::NONE;
    buttons |= qtButtons | Qt::RightButton ? MouseListener::BUTTON_RIGHT : MouseListener::NONE;
    buttons |= qtButtons | Qt::MiddleButton ? MouseListener::BUTTON_MIDDLE : MouseListener::NONE;

    return buttons;
}

bool QGameWidget::eventFilter(QObject *, QEvent *event)
{

    if (event->type() == QEvent::MouseMove) {
        if (_listener != NULL) {
            QMouseEvent *event2 = static_cast<QMouseEvent*>(event);
            _listener->onMouseMove(
                        qtMouseButtons2MouseListenerButtons(event2->buttons()),
                        event2->x()*800.0/width(), event2->y()*600.0/height());
        }
        return true;
    }

    else if (event->type() == QEvent::KeyPress) {
        QKeyEvent *event2 = static_cast<QKeyEvent*>(event);
        if (_listener != NULL)
            _listener->onKeyPress(_keyMap.convert(event2->key()));
        return true;
    }

    else if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *event2 = static_cast<QKeyEvent*>(event);
        if (_listener != NULL)
            _listener->onKeyRelease(_keyMap.convert(event2->key()));
        return true;
    }

    else {
        return false;
    }
}
