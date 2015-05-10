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
    items/itemsmodel.cpp \
    toolbar/toolbar.cpp \
    navigation/navigation.cpp \
    items/item.cpp \
    database/database.cpp \
    items/itemspresenter.cpp \
    addguardian/addguardiandialog.cpp \
    mount/getStoragesInfo.cpp \
    addguardian/drivewidget.cpp \
    guardians/guardiansmodel.cpp \
    crypto/encryptFunctions.cpp \
    crypto/Rijndael.cpp \
    file/fileFunctions.cpp \
    string/stringFunctions.cpp \
    guardians/guardianwidget.cpp \
    guardians/guardian.cpp \
    guardians/guardiansview.cpp \
    guardians/guardianspresenter.cpp \
    drivesscanner/drivesscanner.cpp

HEADERS  += mainwindow.h \
    items/itemwidget.h \
    items/itemsview.h \
    items/itemsmodel.h \
    toolbar/toolbar.h \
    navigation/navigation.h \
    items/item.h \
    database/database.h \
    items/itemspresenter.h \
    addguardian/addguardiandialog.h \
    mount/getStoragesInfo.h \
    addguardian/drivewidget.h \
    guardians/guardiansmodel.h \
    crypto/encryptFunctions.h \
    crypto/Rijndael.h \
    file/fileFunctions.h \
    string/stringFunctions.h \
    guardians/guardianwidget.h \
    guardians/guardian.h \
    guardians/guardiansview.h \
    guardians/guardianspresenter.h \
    mount/storageinfo.h \
    drivesscanner/drivesscanner.h

DISTFILES += \
    res/stylesheet.qss

RESOURCES += \
    res/resources.qrc

@win32:LIBS += -LC:/Windows/System32 -lcrypt32@
