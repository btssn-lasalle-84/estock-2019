QT += quick quickcontrols2 sql
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    baseDeDonnees.h \
    mouvement.h \
    mouvements.h \
    utilisateurArmoire.h \
    utilisateursArmoire.h \
    utilisateurTerminal.h \
    armoire.h \
    armoires.h \
    casier.h \
    casiers.h \
    profil.h \
    groupe.h

SOURCES += main.cpp \
    baseDeDonnees.cpp \
    mouvement.cpp \
    mouvements.cpp \
    utilisateurArmoire.cpp \
    utilisateursArmoire.cpp \
    utilisateurTerminal.cpp \
    armoire.cpp \
    armoires.cpp \
    casier.cpp \
    casiers.cpp \
    profil.cpp \
    groupe.cpp

RESOURCES += qml.qrc
CONFIG += qml_debug
DISTFILES +=

QML_IMPORT_PATH =
QML_DESIGNER_IMPORT_PATH =

unix:!macx:
{
    android:
    {
        # déploie la base de données avec l'apk
        deployment.files += estock.sqlite
        deployment.path = /assets/db
        INSTALLS += deployment
        # le plugin pour MySQL/MariaDB
        contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
            ANDROID_EXTRA_LIBS = \
                $$PWD/android/libs/arm/libmariadb.so
        }
    }
    !android:
    {
        # copie la base de données dans le dossier build
        CONFIG += file_copies
        COPIES += bd
        bd.files = estock.sqlite
        bd.path = $$OUT_PWD/
        bd.base = $$PWD/
    }
}


