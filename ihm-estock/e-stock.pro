#-------------------------------------------------
#
# Project created by QtCreator 2019-03-14T14:22:32
#
#-------------------------------------------------

QT       += core gui sql serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = e-stock
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    utilisateur.cpp \
    article.cpp \
    baseDeDonnees.cpp \
    IhmAuthentification.cpp \
    IhmGestionArmoire.cpp \
    IhmGestionGroupe.cpp \
    IhmAuthentificationSansBadge.cpp \
    casier.cpp \
    AuthentificationBadge.cpp \
    GestionBalances.cpp \
    IhmGestionBalances.cpp

HEADERS += \
    utilisateur.h \
    article.h \
    baseDeDonnees.h \
    e-stock.h \
    IhmAuthentification.h \
    IhmGestionArmoire.h \
    IhmGestionGroupe.h \
    IhmAuthentificationSansBadge.h \
    casier.h \
    AuthentificationBadge.h \
    GestionBalances.h \
    IhmGestionBalances.h

FORMS += \
    IhmAuthentification.ui \
    IhmGestionArmoire.ui \
    IhmGestionGroupe.ui \
    IhmAuthentificationSansBadge.ui

target.path = /home/pi
INSTALLS += target

