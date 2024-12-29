QT       += core gui

include($$PWD/player/player.pri)
include($$PWD/taglibhelper/taglibhelper.pri)
include($$PWD/database/database.pri)
include($$PWD/mymenu/mymenu.pri)
include($$PWD/utils/utils.pri)
include($$PWD/songtable/songtable.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    categorylistwidget.cpp \
    coverpushbutton.cpp \
    main.cpp \
    mainwindow.cpp \
    playlistwidget.cpp \
    playmodecontrolwidget.cpp \
    trotatedlabel.cpp \
    volumecontrolwidget.cpp \
    lyricswidget.cpp \
    singlelyricframe.cpp \
    singlelyriclabel.cpp \
    singlelyricwidget.cpp \
    basewidget.cpp

HEADERS += \
    categorylistwidget.h \
    coverpushbutton.h \
    mainwindow.h \
    playlistwidget.h \
    playmodecontrolwidget.h \
    trotatedlabel.h \
    volumecontrolwidget.h \
    lyricswidget.h \
    singlelyricframe.h \
    singlelyriclabel.h \
    singlelyricwidget.h \
    basewidget.h

FORMS += \
    mainwindow.ui \
    playmodecontrolwidget.ui \
    volumecontrolwidget.ui \
    singlelyricwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
