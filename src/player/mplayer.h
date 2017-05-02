#ifndef MPLAYER_H
#define MPLAYER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtMultimedia/QMediaPlayer>
#include "nowplayingwidget.h"
#include "musicsliderwidget.h"
#include "musictoolbar.h"
#include "titlebar.h"

class NowPlayingWidget;
class MusicToolBar;
class TitleBar;
class MPlayer : public QWidget {
    Q_OBJECT

public:
    MPlayer(QWidget* parent = 0);
    ~MPlayer();

public
slots:
    void onOrderBtnClicked();
    void onRandomBtnClicked();
    void onPreviousBtnClicked();
    void onPausetnClicked();
    void onNextBtnClicked();

private:
    QHBoxLayout* tophblayout;
    QVBoxLayout* btmvblayout;
    QHBoxLayout* toolhblayout;
    QVBoxLayout* mainvblayout;
    NowPlayingWidget* nowPlayingWidget = NULL;
    MusicSliderWidget* musicsliderwidget = NULL;
    MusicToolBar* musictoolbar = NULL;
    TitleBar* titlebar = NULL;

private:
    QMediaPlayer* myplayer;

};

#endif // MPLAYER_H
