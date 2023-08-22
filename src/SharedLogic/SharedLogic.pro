#-------------------------------------------------
#
# Project created by QtCreator 2012-05-27T15:12:32
#
#-------------------------------------------------

QT       -= core gui

TARGET = SharedLogic
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    map.cpp \
    mappack.cpp \
    mapmemento.cpp \
    mapobject.cpp

HEADERS += \
    map.h \
    mappack.h \
    mapmemento.h \
    mapobject.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
