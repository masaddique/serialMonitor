#-------------------------------------------------
#
# Project created by QtCreator 2020-07-22T09:56:02
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
