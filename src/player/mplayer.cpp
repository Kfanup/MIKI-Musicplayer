#include "mplayer.h"

MPlayer::MPlayer(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint);
    resize(640,320);
    setStyleSheet("background-color:#1E90FF");

    titlebar = new TitleBar;
    installEventFilter(titlebar);

    setWindowTitle(tr("MIKI MUSIC PLAYER"));
    setWindowIcon(QIcon("music_logo.png"));

    nowPlayingWidget = new NowPlayingWidget;

    tophblayout = new QHBoxLayout;
    tophblayout->addWidget(nowPlayingWidget);
    tophblayout->addStretch(1);
    tophblayout->setMargin(5);

    musicsliderwidget = new MusicSliderWidget;

    btmvblayout = new QVBoxLayout;
    btmvblayout->addWidget(musicsliderwidget);
    btmvblayout->addStretch(0);
    btmvblayout->setMargin(0);

    musictoolbar=new MusicToolBar;

    toolhblayout=new QHBoxLayout;
    toolhblayout->setAlignment(Qt::AlignCenter);
    toolhblayout->addStretch(0);
    toolhblayout->addWidget(musictoolbar);
    toolhblayout->addStretch(0);
    toolhblayout->setMargin(0);

    mainvblayout = new QVBoxLayout;
    mainvblayout->addWidget(titlebar);
    mainvblayout->addLayout(tophblayout);
    mainvblayout->addSpacing(0);
    mainvblayout->addLayout(btmvblayout);
    mainvblayout->addLayout(toolhblayout);

    setLayout(mainvblayout);

    myplayer = new QMediaPlayer;


    connect(musictoolbar,SIGNAL(orderBtnClicked()),this,SLOT(onOrderBtnClicked()));
    connect(musictoolbar,SIGNAL(randoBtnClicked()),this,SLOT(onRandomBtnClicked()));
    connect(musictoolbar,SIGNAL(previousBtnClicked()),this,SLOT(onPreviousBtnClicked()));
    connect(musictoolbar,SIGNAL(pauseBtnClicked()),this,SLOT(onPausetnClicked()));
    connect(musictoolbar,SIGNAL(nextBtnClicked()),this,SLOT(onNextBtnClicked()));
}

MPlayer::~MPlayer()
{

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
