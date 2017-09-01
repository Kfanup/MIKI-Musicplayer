#pragma once

#include <QDialog>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include "nowplayingwidget.h"
#include "playlistwidget.h"
#include "musicsliderwidget.h"
#include "musictoolbar.h"
#include "titlebar.h"
#include "util/musicfilemanager.h"

class MusicToolBar;
class MPlayer : public QWidget
{
    Q_OBJECT

public:
    MPlayer(QWidget *parent = 0);
    ~MPlayer();
    void setInitStyle();
    void setInitWidget();
    void onAddSongClicked();
    void onAddSongDirClicked();
    void onPlayModeBtnClicked();
    void onPreviousBtnClicked();
    void onPausetnClicked();
    void onNextBtnClicked();
    void onNowPlayingClicked();
    void onPlayingListClicked();

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

private:
    QMediaPlayer *myPlayer;
    QMediaPlaylist *playList;
    QFileInfoList songList;
};
