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
