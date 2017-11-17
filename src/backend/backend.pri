HEADERS  += \
    $$PWD/musicmeta.h \
    $$PWD/musiclibrary.h \
    $$PWD/musicdatabase.h \
    $$PWD/playlistmeta.h \
    $$PWD/playlist.h \
    $$PWD/player.h


SOURCES  += \
    $$PWD/musicmeta.cpp \
    $$PWD/musiclibrary.cpp \
    $$PWD/musicdatabase.cpp \
    $$PWD/playlist.cpp \ 
    $$PWD/player.cpp

#INCLUDEPATH += /usr/local/include/

LIBS += -lavcodec -lavformat -lswscale -lavutil
