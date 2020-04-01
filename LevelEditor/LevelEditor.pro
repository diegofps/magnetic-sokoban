#-------------------------------------------------
#
# Project created by QtCreator 2012-05-27T15:12:58
#
#-------------------------------------------------

QT       += core gui

TARGET = LevelEditor
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    mapdialog.cpp \
    commandhistory.cpp \
    mapeditor.cpp \
    editmapcommand.cpp \
    addmapcommand.cpp \
    removemapcommand.cpp \
    movemapupcommand.cpp \
    movemapdowncommand.cpp \
    putobjectcommand.cpp \
    aboutdialog.cpp \
    mappencil.cpp \
    imagehandler.cpp \
    floorpencil.cpp \
    robotpencil.cpp \
    wallpencil.cpp \
    rigidpencil.cpp \
    platepencil.cpp

HEADERS  += mainwindow.h \
    mapdialog.h \
    commandhistory.h \
    command.h \
    mapeditor.h \
    commandslistener.h \
    editmapcommand.h \
    addmapcommand.h \
    removemapcommand.h \
    movemapupcommand.h \
    movemapdowncommand.h \
    putobjectcommand.h \
    aboutdialog.h \
    mappencil.h \
    imagehandler.h \
    floorpencil.h \
    robotpencil.h \
    wallpencil.h \
    rigidpencil.h \
    platepencil.h

FORMS    += mainwindow.ui \
    mapdialog.ui \
    aboutdialog.ui

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
