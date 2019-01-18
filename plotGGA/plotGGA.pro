#-------------------------------------------------
#
# Project created by QtCreator 2016-01-25T15:27:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = plotGGA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    nemagga.h \
    geoconst.h \
    geotrans.h

FORMS    += mainwindow.ui
