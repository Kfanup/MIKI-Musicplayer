#ifndef MPLAYER_H
#define MPLAYER_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QtMultimedia/QMediaPlayer>
#include "nowplayingwidget.h"
#include "playlistwidget.h"
#include "musicsliderwidget.h"
#include "musictoolbar.h"
#include "titlebar.h"

class NowPlayingWidget;
class MusicToolBar;
class TitleBar;
class MPlayer : public QDialog
{
    Q_OBJECT

public:
    MPlayer(QDialog *parent = 0);
    ~MPlayer();
    void setInitStyle();
    void setInitWidget();

public slots:
    void onOrderBtnClicked();
    void onRandomBtnClicked();
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

private:
    QMediaPlayer *myplayer;
};

#endif // MPLAYER_H
