#include <QtWidgets/QApplication>
#include "qengine.h"
#include "menuroom.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QEngine engine;

    MenuRoom menuRoom(&engine);

    engine.goTo(&menuRoom);
    engine.start();

    return a.exec();
}
