#-------------------------------------------------
#
# Project created by QtCreator 2015-03-10T20:44:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ngspice_gui1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spicefile.cpp \
    voltagesource.cpp \
    currentsource.cpp \
    op.cpp \
    ac.cpp \
    dc.cpp \
    tran.cpp \
    noise.cpp \
    pss.cpp \
    pz.cpp

HEADERS  += mainwindow.h \
    spicefile.h \
    voltagesource.h \
    currentsource.h \
    op.h \
    ac.h \
    dc.h \
    tran.h \
    noise.h \
    pss.h \
    pz.h

FORMS    += mainwindow.ui

RESOURCES = ngspice_gui1.qrc
