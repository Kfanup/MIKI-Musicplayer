#include "mplayer.h"
#include <QtGlobal>

MPlayer::MPlayer(QWidget *parent)
    : QWidget(parent)
{
    setInitStyle();
    setInitWidget();

    titlebar = new TitleBar(this);
    musicfilemanager = new MusicFileManager(this);

    mainvblayout = new QVBoxLayout;
    mainvblayout->addWidget(titlebar);
    mainvblayout->addLayout(tophblayout);
    mainvblayout->addStretch(2);
    mainvblayout->addLayout(btmvblayout);
    mainvblayout->addStretch(1);
    mainvblayout->addLayout(toolhblayout);

    setLayout(mainvblayout);

    myPlayer = new QMediaPlayer;
    playList = new QMediaPlaylist;

    connect(titlebar, &TitleBar::addMedia, this, &MPlayer::onAddSongClicked);
    connect(titlebar, &TitleBar::addMediaDir, this, &MPlayer::onAddSongDirClicked);
    connect(musictoolbar, &MusicToolBar::playModeBtnClicked, this, &MPlayer::onPlayModeBtnClicked);
    connect(musictoolbar, &MusicToolBar::previousBtnClicked, this, &MPlayer::onPreviousBtnClicked);
    connect(musictoolbar, &MusicToolBar::pauseBtnClicked, this, &MPlayer::onPausetnClicked);
    connect(musictoolbar, &MusicToolBar::nextBtnClicked, this, &MPlayer::onNextBtnClicked);

    connect(nowPlayingWidget, &NowPlayingWidget::nowPlayingClicked, this,
            &MPlayer::onNowPlayingClicked);
    connect(nowPlayingWidget, &NowPlayingWidget::playingListClicked, this,
            &MPlayer::onPlayingListClicked);
    connect(playinglistwidget, &PlayListWidget::nowPlayingClicked, this,
            &MPlayer::onNowPlayingClicked);
    connect(playinglistwidget, &PlayListWidget::playingListClicked, this,
            &MPlayer::onPlayingListClicked);
}

MPlayer::~MPlayer()
{
}

/***
 ** @brief 初始化风格
 **/
void MPlayer::setInitStyle()
{

#ifdef Q_OS_WIN
    this->setWindowIcon(QIcon(":/new/prefix1/res/music_logo.ico"));
#else
    this->setWindowIcon(QIcon(":/new/prefix1/res/music_logo.png"));
#endif

    this->setWindowFlags(Qt::CustomizeWindowHint);
    this->resize(640, 320);
    this->setStyleSheet("background-color:white");
}

/***
 ** @brief 初始化窗口
 **/
void MPlayer::setInitWidget()
{
    //播放界面与歌曲列表切换
    nowPlayingWidget = new NowPlayingWidget;
    playinglistwidget = new PlayListWidget(songList);
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

/***
 ** @brief 一系列鼠标点击事件
 **/
inline void MPlayer::onNowPlayingClicked()
{
    if (musicStacked->currentIndex() == 0) {
        musicStacked->setCurrentIndex(1);
    } else {
        musicStacked->setCurrentIndex(0);
    }
}

inline void MPlayer::onPlayingListClicked()
{
    if (musicStacked->currentIndex() == 0) {
        musicStacked->setCurrentIndex(1);
    } else {
        musicStacked->setCurrentIndex(0);
    }
}

inline void MPlayer::onAddSongClicked()
{
    songList = musicfilemanager->addMedia();
}

inline void MPlayer::onAddSongDirClicked()
{
    songList = musicfilemanager->addMediaDir();
}

void MPlayer::onPlayModeBtnClicked()
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
