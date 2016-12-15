#-------------------------------------------------
#
# Project created by QtCreator 2016-12-14T08:56:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graphs
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        painterwindow.cpp \
    circleitem.cpp \
    lineitem.cpp \
    textitem.cpp \
    dialog.cpp

HEADERS  += painterwindow.h \
    circleItem.h \
    textitem.h \
    lineItem.h \
    dialog.h

FORMS    += painterwindow.ui \
    dialog.ui
