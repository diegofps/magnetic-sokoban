#-------------------------------------------------
#
# Project created by QtCreator 2012-06-06T18:56:57
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

TARGET = Sokoban
TEMPLATE = app


SOURCES += main.cpp\
    qengine.cpp \
    qgamewidget.cpp \
    menuroom.cpp \
    qgameimage.cpp \
    room.cpp \
    background.cpp \
    motionbackground.cpp \
    viewport.cpp \
    button.cpp \
    sprite.cpp \
    object.cpp \
    levelselectroom.cpp \
    objectimage.cpp \
    buttonmenulevel.cpp \
    gameprogress.cpp \
    gameroom.cpp \
    levelobject.cpp \
    wall.cpp \
    robot.cpp \
    floor.cpp \
    spriteshandler.cpp \
    keylistener.cpp \
    keymap.cpp \
    viewportrefresher.cpp \
    steplistener.cpp \
    modalroompause.cpp \
    modalroomfinishlevel.cpp \
    numberdrawer.cpp \
    bigstar.cpp \
    bigfoot.cpp

HEADERS  += \
    engine.h \
    graphics.h \
    qengine.h \
    object.h \
    room.h \
    mouselistener.h \
    qgamewidget.h \
    qgamewidgetlistener.h \
    menuroom.h \
    image.h \
    qgameimage.h \
    background.h \
    motionbackground.h \
    viewport.h \
    button.h \
    sprite.h \
    helpers.h \
    levelselectroom.h \
    objectimage.h \
    buttonlistener.h \
    buttonmenulevel.h \
    gameprogress.h \
    gameroom.h \
    levelobject.h \
    wall.h \
    robot.h \
    floor.h \
    spriteshandler.h \
    keylistener.h \
    keymap.h \
    viewportrefresher.h \
    steplistener.h \
    modalroompause.h \
    modalroomfinishlevel.h \
    numberdrawer.h \
    bigstar.h \
    bigfoot.h

LIBS += -lm

FORMS    += \
    qengine.ui

RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SharedLogic/release/ -lSharedLogic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SharedLogic/debug/ -lSharedLogic
else:symbian: LIBS += -lSharedLogic
else:unix: LIBS += -L$$OUT_PWD/../SharedLogic/ -lSharedLogic

INCLUDEPATH += $$PWD/../SharedLogic
DEPENDPATH += $$PWD/../SharedLogic

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../SharedLogic/release/SharedLogic.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../SharedLogic/debug/SharedLogic.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../SharedLogic/libSharedLogic.a
