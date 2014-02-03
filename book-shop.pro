#-------------------------------------------------
#
# Project created by QtCreator 2014-01-21T21:03:19
#
#-------------------------------------------------

QT += core gui network
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = book-shop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlkepper.cpp \
    downloadmanager.cpp \
    manager.cpp

HEADERS  += mainwindow.h \
    sqlkepper.h \
    downloadmanager.h \
    manager.h

FORMS    += mainwindow.ui
