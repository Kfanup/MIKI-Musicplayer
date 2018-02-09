#pragma once

#include <QObject>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "musicdatabase.h"
#include "widgets/playlistwidget.h"
#include "widgets/musictoolbar.h"
#include "util/music_global.h"
#include "backend/musicdatabase.h"

class PlayListWidget;
class MusicToolBar;
class Player : public QObject
{
    Q_OBJECT
public:
    Player(QStringList &pathList, QObject *parent = 0);
    ~Player();
    void setPlaylist(QStringList &list);
    void playMedia(int index);
    void initPlaymode();
    enum playmode { ITEMONCE = 0, ITEMLOOP, SEQUENTIAL, LOOP, RANDOM };

signals:
    void positionChanged(qint64 pos);
    void durationChanged(qint64 d);
    // False for pause,and True for play
    void updatedState(bool state);
    void updatedMode(qint32 index);

public slots:
    void playOrPause();
    void lastMedia();
    void nextMedia();
    void updatePlaymode();

private:
    QMediaPlayer *qPlayer = NULL;
    QMediaPlaylist *playlist = NULL;
    PlayListWidget *playlistwidget = NULL;
    MusicToolBar *toolbar = NULL;
    MusicDatabase *database = NULL;
    QTimer *timer;

private:
};
