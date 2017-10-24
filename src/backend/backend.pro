
QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE  = lib

HEADERS  += \
    util/musicfilemanager.h \
    util/music_global.h \
    musicmeta.h \
    musiclibrary.h \
    musicdatabase.h \
    databaseconnection.h \
    playlistmeta.h \
    playlist.h \
    util/playlistmanager.h

SOURCES  += \
    util/musicfilemanager.cpp \
    musicmeta.cpp \
    musiclibrary.cpp \
    musicdatabase.cpp \
    playlist.cpp \
    util/playlistmanager.cpp

INCLUDEPATH += /usr/local/include/taglib/
INCLUDEPATH += /usr/local/include/libavformat/
