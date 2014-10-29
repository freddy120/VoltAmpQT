#-------------------------------------------------
#
# Project created by QtCreator 2014-10-01T12:57:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

QT += serialport
QMAKE_CXXFLAGS += -std=c++11

TARGET = voltampIPEN
TEMPLATE = app

CONFIG += debug

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    settingsdialog.cpp \
    viewlog.cpp \
    serialThread.cpp \
    voltagrama.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    settingsdialog.h \
    viewlog.h \
    serialThread.h \
    voltagrama.h \
    util.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    viewlog.ui
