#ifndef QGAMEWIDGET_H
#define QGAMEWIDGET_H

#include <vector>
#include <QTimer>
#include <QGLWidget>
#include <QPainter>

#include "graphics.h"
#include "mouselistener.h"
#include "keymap.h"

class Image;
class MotionBackground;
class QGameWidgetListener;
class QMouseEvent;

class QGameWidget : public QGLWidget, public Graphics
{

public:

    QGameWidget(QWidget *parent);


    void paintGL();

    bool eventFilter(QObject *, QEvent *);

    void mousePressEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

    Image * newImage(const char *filePath);

    MotionBackground * newMotionBackground(Image * image, const float xSpeed, const float ySpeed);

    void drawImage(Image *image, int x, int y);

    void drawSubImage(Image * image, int x, int y, int imX, int imY, int imW, int imH);

    void setListener(QGameWidgetListener *listener);

    void focusOutEvent(QFocusEvent *);

private:

    MouseListener::Buttons
    qtMouseButtons2MouseListenerButtons(Qt::MouseButtons);

private:

    QTimer timer;

    QGameWidgetListener *_listener;

    QPainter *_painter;

    KeyMap _keyMap;

};

#endif // QGAMEWIDGET_H
