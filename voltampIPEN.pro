#-------------------------------------------------
#
# Project created by QtCreator 2014-10-01T12:57:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

QT += serialport


TARGET = voltampIPEN
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    settingsdialog.cpp \
    viewlog.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    settingsdialog.h \
    viewlog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    viewlog.ui
