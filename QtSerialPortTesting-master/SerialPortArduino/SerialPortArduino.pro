#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T11:37:58
#
#-------------------------------------------------

QT       += core serialport gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialPortArduino
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
