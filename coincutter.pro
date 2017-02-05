#-------------------------------------------------
#
# Project created by QtCreator 2017-01-06T10:29:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = coincutter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    circlerecognizer.cpp \
    convolution.cpp

HEADERS  += mainwindow.h \
    circlerecognizer.h \
    Circle.h \
    convolution.h

FORMS    += mainwindow.ui
