#include "mplayer.h"
#include <QtGlobal>

MPlayer::MPlayer(QDialog *parent)
    : QDialog(parent)
{
    setInitStyle();
    setInitWidget();

    titlebar = new TitleBar(this);

    mainvblayout = new QVBoxLayout;
    mainvblayout->addWidget(titlebar);
    mainvblayout->addLayout(tophblayout);
    mainvblayout->addStretch(2);
    mainvblayout->addLayout(btmvblayout);
    mainvblayout->addStretch(1);
    mainvblayout->addLayout(toolhblayout);

    setLayout(mainvblayout);

    myplayer = new QMediaPlayer;

    connect(musictoolbar, SIGNAL(orderBtnClicked()), this, SLOT(onOrderBtnClicked()));
    connect(musictoolbar, SIGNAL(randoBtnClicked()), this, SLOT(onRandomBtnClicked()));
    connect(musictoolbar, SIGNAL(previousBtnClicked()), this, SLOT(onPreviousBtnClicked()));
    connect(musictoolbar, SIGNAL(pauseBtnClicked()), this, SLOT(onPausetnClicked()));
    connect(musictoolbar, SIGNAL(nextBtnClicked()), this, SLOT(onNextBtnClicked()));

    connect(nowPlayingWidget, SIGNAL(nowPlayingClicked()), this, SLOT(onNowPlayingClicked()));
    connect(nowPlayingWidget, SIGNAL(playingListClicked()), this, SLOT(onPlayingListClicked()));
    connect(playinglistwidget, SIGNAL(nowPlayingClicked()), this, SLOT(onNowPlayingClicked()));
    connect(playinglistwidget, SIGNAL(playingListClicked()), this, SLOT(onPlayingListClicked()));
}

MPlayer::~MPlayer()
{
}

void MPlayer::setInitStyle()
{

#ifdef Q_OS_WIN
    this->setWindowIcon(QIcon(":/new/prefix1/res/music_logo.ico"));
#else
    this->setWindowIcon(QIcon(":/new/prefix1/res/music_logo.png"));
#endif

    this->setWindowFlags(Qt::CustomizeWindowHint);
    this->resize(640, 320);
    this->setStyleSheet("background-color:#1E90FF");
    this->setWindowTitle(tr("MIKI MUSIC PLAYER"));
}

void MPlayer::setInitWidget()
{
    //播放界面与歌曲列表切换
    nowPlayingWidget = new NowPlayingWidget;
    playinglistwidget = new PlayListWidget;
    musicStacked = new QStackedWidget;

    musicStacked->addWidget(nowPlayingWidget);
    musicStacked->addWidget(playinglistwidget);
    musicStacked->setCurrentIndex(0);

    tophblayout = new QHBoxLayout;
    tophblayout->addWidget(musicStacked);
    tophblayout->addStretch(1);
    tophblayout->setMargin(5);

    //播放进度条
    musicsliderwidget = new MusicSliderWidget;

    btmvblayout = new QVBoxLayout;
    btmvblayout->addWidget(musicsliderwidget);
    btmvblayout->addStretch(0);
    btmvblayout->setMargin(0);

    //播放控件
    musictoolbar = new MusicToolBar;

    toolhblayout = new QHBoxLayout;
    toolhblayout->setAlignment(Qt::AlignCenter);
    toolhblayout->addStretch(0);
    toolhblayout->addWidget(musictoolbar);
    toolhblayout->addStretch(0);
    toolhblayout->setMargin(0);
}

void MPlayer::onNowPlayingClicked()
{
    if (musicStacked->currentIndex() == 0) {
        musicStacked->setCurrentIndex(1);
    } else {
        musicStacked->setCurrentIndex(0);
    }
}

void MPlayer::onPlayingListClicked()
{
    if (musicStacked->currentIndex() == 0) {
        musicStacked->setCurrentIndex(1);
    } else {
        musicStacked->setCurrentIndex(0);
    }
}

void MPlayer::onOrderBtnClicked()
{
}

void MPlayer::onRandomBtnClicked()
{
}

void MPlayer::onPreviousBtnClicked()
{
}

void MPlayer::onPausetnClicked()
{
}

void MPlayer::onNextBtnClicked()
{
}
