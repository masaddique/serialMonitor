#-------------------------------------------------
#
# Project created by QtCreator 2020-07-21T21:26:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serialPortApp
TEMPLATE = app


SOURCES += main.cpp\
        serialportapp.cpp \
    serialobject.cpp

HEADERS  += serialportapp.h \
    serialobject.h

FORMS    += serialportapp.ui
