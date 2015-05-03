#-------------------------------------------------
#
# Project created by QtCreator 2015-04-29T14:12:01
#
#-------------------------------------------------

QT       += core gui
QT       += sql
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Guardian
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    items/itemwidget.cpp \
    items/itemsview.cpp \
    items/itemscontroller.cpp \
    items/itemsmodel.cpp \
    items/itemsmain.cpp \
    toolbar/toolbar.cpp \
    navigation/navigation.cpp \
    items/item.cpp \
    database/database.cpp \
    navigation/add/additemdialog.cpp \
    navigation/add/addguardiandialog.cpp \
    items/guardian.cpp \
    navigation/add/selectguardian.cpp

HEADERS  += mainwindow.h \
    items/itemwidget.h \
    items/itemsview.h \
    items/itemscontroller.h \
    items/itemsmodel.h \
    items/itemsmain.h \
    toolbar/toolbar.h \
    navigation/navigation.h \
    items/item.h \
    database/database.h \
    navigation/add/additemdialog.h \
    navigation/add/addguardiandialog.h \
    items/guardian.h \
    navigation/add/selectguardian.h

DISTFILES += \
    res/stylesheet.qss

RESOURCES += \
    res/resources.qrc
