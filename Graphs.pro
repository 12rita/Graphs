#-------------------------------------------------
#
# Project created by QtCreator 2016-12-09T23:08:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHopeItWillWork
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        painterwindow.cpp \
    lineitem.cpp \
    circleitem.cpp \
    textitem.cpp

HEADERS  += painterwindow.h \
    CircleItem.h \
    lineItem.h \
    textitem.h

FORMS    += painterwindow.ui
