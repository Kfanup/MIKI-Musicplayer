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
    Player(QString &localPath, QStringList &pathList, qint32 volume, QObject *parent = 0);
    static Player *getInstance(QString &localPath, QStringList &pathList, qint32 volume);
    ~Player();
    void setPlaylist(QString localPath, QStringList list);
    void updatePlaylist(QStringList list);
    void playMedia(int index);
    void initPlaymode();
    enum playmode { ITEMONCE = 0, ITEMLOOP, SEQUENTIAL, LOOP, RANDOM };

signals:
    void positionChanged(qint64);
    void durationChanged(qint64);
    // False for pause,and True for play
    void updatedState(bool);
    void updatedMode(qint32);
    void gettedMetadata(QStringList);

public slots:
    void playOrPause();
    void lastMedia();
    void nextMedia();
    void updatePlaymode();
    void sendMetaSignal(QMediaPlayer::MediaStatus status);
    void updateMediaPosition(int pos);
    void updateVolume(int value);
//    void updatePlaylist(QStringList songlist);

private:
    QMediaPlayer *qPlayer = NULL;
    QMediaPlaylist *playlist = NULL;
    PlayListWidget *playlistwidget = NULL;
    MusicToolBar *toolbar = NULL;
    MusicDatabase *database = NULL;
    QTimer *timer;
    QString localPlaylist;

private:
};
