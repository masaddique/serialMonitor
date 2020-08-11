#-------------------------------------------------
#
# Project created by QtCreator 2020-07-22T09:56:02
#
#-------------------------------------------------

QT += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serialPortApp
TEMPLATE = app


SOURCES += main.cpp\
        serialportapp.cpp \
    cmdinputdlg.cpp

HEADERS  += serialportapp.h \
    cmdinputdlg.h

FORMS    += serialportapp.ui \
    cmdinputdlg.ui

QMAKE_CXXFLAGS += -std=c++11
