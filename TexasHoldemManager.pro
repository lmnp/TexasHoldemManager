#-------------------------------------------------
#
# Project created by QtCreator 2014-03-31T13:24:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TexasHoldemManager
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    settingsdialog.cpp \
    helpdialog.cpp \
    pregameonedialog.cpp \
    pregametwodialog.cpp \
    tablewidget.cpp \
    mainwindow.cpp \
    playerwidget.cpp

HEADERS  += maindialog.h \
    settingsdialog.h \
    helpdialog.h \
    pregameonedialog.h \
    pregametwodialog.h \
    tablewidget.h \
    mainwindow.h \
    playerwidget.h

FORMS    += maindialog.ui \
    settingsdialog.ui \
    helpdialog.ui \
    pregameonedialog.ui

CONFIG += mobility
MOBILITY = 

