#-------------------------------------------------
#
# Project created by QtCreator 2014-05-06T22:09:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RagaEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    headers/syntax_check.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources/icons.qrc
