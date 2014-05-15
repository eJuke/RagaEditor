#-------------------------------------------------
#
# Project created by QtCreator 2014-05-06T22:09:30
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RagaEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += \
    headers/syntax_check.h \
    headers/mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources/Other.qrc
