#pragma once

#include <QDialog>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QGraphicsOpacityEffect>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include "titlebar.h"
#include "nowplayingwidget.h"
#include "playlistwidget.h"
#include "musicsliderwidget.h"
#include "musictoolbar.h"
#include "util/musicfilemanager.h"
#include "backend/musicmeta.h"
#include "backend/musicdatabase.h"
#include "backend/musiclibrary.h"
#include "backend/player.h"

class MusicSliderWidget;
class MusicToolBar;
class TitleBar;
class MPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MPlayer(QWidget *parent = 0);
    ~MPlayer();
    void setInitStyle();
    void setInitWidget();
    void onAddSongClicked();
    void onAddSongDirClicked();
    void onNowPlayingClicked();
    void onPlayingListClicked();
    QString getPlaylistFromLocal();

    void updateVolumeOnDatabase(int value);


signals:
    void toUpdatePlaylist(QStringList);

private:
    QHBoxLayout *tophblayout;
    QVBoxLayout *btmvblayout;
    QHBoxLayout *toolhblayout;
    QVBoxLayout *mainvblayout;
    QStackedWidget *musicStacked;
    NowPlayingWidget *nowPlayingWidget = NULL;
    PlayListWidget *playinglistwidget = NULL;
    MusicSliderWidget *musicsliderwidget = NULL;
    MusicToolBar *musictoolbar = NULL;
    TitleBar *titlebar = NULL;
    MusicFileManager *musicfilemanager = NULL;
    MusicDatabase *database = NULL;
    MusicMeta *musicmeta = NULL;
    MusicLibrary *musiclibrary = NULL;
    Player *player = NULL;

private:
    QMediaPlayer *myPlayer;
    QMediaPlaylist *playList;

private:
    void bind();
};
