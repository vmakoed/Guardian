#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T20:41:43
#
#-------------------------------------------------

QT       += core gui
QT       += sql

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Guardian
TEMPLATE = app


SOURCES += main.cpp \
    common/stringFunctions.cpp \
    database/database.cpp \
    database/datamanager.cpp \
    drivesscanner/drivesscanner.cpp \
    drivesscanner/getStoragesInfo.cpp \
    fileencryption/encryptFunctions.cpp \
    fileencryption/encryptmanager.cpp \
    fileencryption/fileencryption.cpp \
    fileencryption/fileFunctions.cpp \
    fileencryption/filemanager.cpp \
    fileencryption/Rijndael.cpp \
    gui/addguardiandialog.cpp \
    gui/additemdialog.cpp \
    gui/drivelistwidget.cpp \
    gui/guardianlistwidget.cpp \
    gui/icontextlabel.cpp \
    gui/itemlistwidget.cpp \
    gui/mainwindow.cpp \
    itemslocker/itemslocker.cpp \
    itemslocker/redefineAccess.cpp \
    itemslocker/systemlocker.cpp \
    guardian.cpp \
    item.cpp \
    maincontroller.cpp

HEADERS  += \
    common/stringFunctions.h \
    database/database.h \
    database/datamanager.h \
    drivesscanner/drivesscanner.h \
    drivesscanner/getStoragesInfo.h \
    drivesscanner/storageinfo.h \
    fileencryption/cryptobject.h \
    fileencryption/encryptFunctions.h \
    fileencryption/encryptmanager.h \
    fileencryption/fileencryption.h \
    fileencryption/fileFunctions.h \
    fileencryption/filemanager.h \
    fileencryption/Rijndael.h \
    gui/addguardiandialog.h \
    gui/additemdialog.h \
    gui/drivelistwidget.h \
    gui/guardianlistwidget.h \
    gui/icontextlabel.h \
    gui/itemlistwidget.h \
    gui/mainwindow.h \
    itemslocker/itemslocker.h \
    itemslocker/RedefineAccess.h \
    itemslocker/systemlocker.h \
    guardian.h \
    item.h \
    maincontroller.h

RESOURCES += \
    res/resources.qrc

DISTFILES += \
    res/stylesheet.qss
