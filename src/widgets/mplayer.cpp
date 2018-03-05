#include "mplayer.h"
#include <QtGlobal>

MPlayer::MPlayer(QWidget *parent)
    : QWidget(parent)
{
    setInitStyle();
    setInitWidget();

    titlebar = new TitleBar;
    musicfilemanager = MusicFileManager::getInstance();

    mainvblayout = new QVBoxLayout;
    mainvblayout->addWidget(titlebar);
    mainvblayout->addLayout(tophblayout);
    mainvblayout->addStretch(5);
    mainvblayout->addLayout(btmvblayout);
    mainvblayout->addStretch(1);
    mainvblayout->addLayout(toolhblayout);

    setLayout(mainvblayout);

    musiclibrary = MusicLibrary::getInstance();

    QString localPlaylist = getPlaylistFromLocal();
    QStringList pathList= playinglistwidget->getPlaylistFromDB();
    qint32 volume = database->getVolumeFromSetup();
    player = new Player(localPlaylist, pathList, volume, this);

    bind();
}

MPlayer::~MPlayer()
{
    delete nowPlayingWidget;
    delete playinglistwidget;
    delete musicStacked;
    delete musicsliderwidget;
    delete musictoolbar;
    delete titlebar;
}

/***
 ** @brief 初始化风格
 **/
void MPlayer::setInitStyle()
{

#ifdef Q_OS_WIN
    this->setWindowIcon(QIcon(":/new/prefix1/res/music_logo.ico"));
#else
    this->setWindowIcon(QIcon(":/images/res/icon_unix/music_logo.png"));
#endif

    this->setWindowFlags(Qt::CustomizeWindowHint);
    this->resize(960, 640);
    this->setStyleSheet("background-color:white");
}

/***
 ** @brief 初始化窗口
 **/
void MPlayer::setInitWidget()
{

    //播放界面与歌曲列表切换
    nowPlayingWidget = new NowPlayingWidget;
    playinglistwidget = new PlayListWidget;
    musicStacked = new QStackedWidget;
    database = MusicDatabase::getInstance();

    musicStacked->addWidget(nowPlayingWidget);
    musicStacked->addWidget(playinglistwidget);
    musicStacked->setCurrentIndex(0);

    tophblayout = new QHBoxLayout;
    tophblayout->addWidget(musicStacked);
    tophblayout->addStretch(0);
    tophblayout->setMargin(5);

    //播放进度条
    musicsliderwidget = new MusicSliderWidget;

    btmvblayout = new QVBoxLayout;
    btmvblayout->addWidget(musicsliderwidget);
    btmvblayout->addStretch(0);
    btmvblayout->setMargin(0);

    //播放控件
    musictoolbar = new MusicToolBar(database->getVolumeFromSetup());

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

QString MPlayer::getPlaylistFromLocal()
{

    QString cacheStr = musicfilemanager->getCachePath();
    QString cachePath = cacheStr + QString("/myplaylist.txt");
    QFile file(cachePath);
    if (!file.exists())
    {
       if (file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           file.close();
       }
    }
    return cachePath;
}

void MPlayer::updateVolumeOnDatabase(int value)
{
    database->updateVolume(value);
}

inline void MPlayer::onAddSongClicked()
{
    QStringList songList = musicfilemanager->addMedia();
    for (auto &song : songList) {
        QFileInfo fileinfo(song);
        auto meta = MusicMeta::fromLocalfile(fileinfo);

        if (!database->isMusicMetaExist(meta.hash)) {
            qDebug() << "start to insert media";
            database->addMusicMeta(meta);
        }
    }
    emit toUpdatePlaylist(songList);
}

inline void MPlayer::onAddSongDirClicked()
{
    QFileInfoList songList = musicfilemanager->addMediaDir();
    QStringList list;

    for (auto &song : songList) {
        auto meta = MusicMeta::fromLocalfile(song);
        list.append(song.absoluteFilePath());
        if (!database->isMusicMetaExist(meta.hash)) {
            qDebug() << "start to insert media";
            database->addMusicMeta(meta);
        }
    }
    emit toUpdatePlaylist(list);
}

void MPlayer::bind()
{
    connect(titlebar, &TitleBar::addMedia, this, &MPlayer::onAddSongClicked);
    connect(titlebar, &TitleBar::addMediaDir, this, &MPlayer::onAddSongDirClicked);

    connect(nowPlayingWidget, &NowPlayingWidget::nowPlayingClicked, this,
            &MPlayer::onNowPlayingClicked);
    connect(nowPlayingWidget, &NowPlayingWidget::playingListClicked, this,
            &MPlayer::onPlayingListClicked);
    connect(playinglistwidget, &PlayListWidget::nowPlayingClicked, this,
            &MPlayer::onNowPlayingClicked);
    connect(playinglistwidget, &PlayListWidget::playingListClicked, this,
            &MPlayer::onPlayingListClicked);

    connect(playinglistwidget, &PlayListWidget::gettedPlayIndex, player, &Player::playMedia);

    //播放进度条以及时间显示
    connect(player, &Player::durationChanged, musicsliderwidget, &MusicSliderWidget::setTimeLabel);
    connect(player, &Player::durationChanged, musicsliderwidget, &MusicSliderWidget::setPosition);
    connect(player, &Player::positionChanged, musicsliderwidget,
            &MusicSliderWidget::updatePosition);
    connect(player, &Player::positionChanged, musicsliderwidget,
            &MusicSliderWidget::updateTimeLabel);
    connect(musicsliderwidget,&MusicSliderWidget::positionChanged, player, &Player::updateMediaPosition);

    //工具栏信号
    connect(musictoolbar, &MusicToolBar::pauseBtnClicked, player, &Player::playOrPause);
    connect(musictoolbar, &MusicToolBar::nextBtnClicked, player, &Player::nextMedia);
    connect(musictoolbar, &MusicToolBar::previousBtnClicked, player, &Player::lastMedia);
    connect(musictoolbar, &MusicToolBar::playModeBtnClicked, player, &Player::updatePlaymode);
    connect(musictoolbar, &MusicToolBar::volumeChanged, player, &Player::updateVolume);
    connect(musictoolbar, &MusicToolBar::volumeChanged, this, &MPlayer::updateVolumeOnDatabase);

    connect(player, &Player::updatedState, musictoolbar, &MusicToolBar::updateStateIcon);
    connect(player, &Player::updatedMode, musictoolbar, &MusicToolBar::updateModeIcon);
    connect(player,&Player::gettedMetadata, nowPlayingWidget, &NowPlayingWidget::updateLabel);

    //更新model
    connect(titlebar, &TitleBar::addMedia, playinglistwidget, &PlayListWidget::updatePlaylist);
    connect(titlebar, &TitleBar::addMediaDir, playinglistwidget, &PlayListWidget::updatePlaylist);

    //更新歌曲列表
    connect(this, &MPlayer::toUpdatePlaylist, player, &Player::updatePlaylist);
}
