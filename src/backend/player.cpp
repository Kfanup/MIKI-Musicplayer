#include "player.h"

using namespace MMusic;
Player::Player(QStringList &pathList, QObject *parent)
    : QObject(parent)
{
    playlist = new QMediaPlaylist;
    qPlayer = new QMediaPlayer;
    toolbar = new MusicToolBar;
    database = new MusicDatabase;
    timer = new QTimer;

    setPlaylist(pathList);

    connect(toolbar, &MusicToolBar::pauseBtnClicked, this, &Player::playOrPause);
    connect(toolbar, &MusicToolBar::nextBtnClicked, this, &Player::nextMedia);
    connect(toolbar, &MusicToolBar::previousBtnClicked, this, &Player::lastMedia);
    connect(toolbar, &MusicToolBar::playModeBtnClicked, this, &Player::updatePlaymode);
}

Player::~Player()
{
    qPlayer->deleteLater();
    timer->stop();
    delete timer;
}

void Player::playMedia(int index)
{

    qDebug() << "accept signal";
    qDebug() << qPlayer->mediaStatus();
    qDebug() << qPlayer->position();
    qDebug() << qPlayer->duration();
    timer->start(500);
    qDebug() << index;
    playlist->setCurrentIndex(index);
    qPlayer->play();

    connect(qPlayer, &QMediaPlayer::durationChanged, this, &Player::durationChanged);
    connect(qPlayer, &QMediaPlayer::positionChanged, this, &Player::positionChanged);
}

void Player::initPlaymode()
{
    auto mode = database->getDataFromSetup(QString("playmode"));
    switch (mode) {
    case ITEMONCE:
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        break;
    case ITEMLOOP:
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        break;
    case SEQUENTIAL:
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
        break;
    case LOOP:
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        break;
    case RANDOM:
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        break;
    default:
        break;
    }
}

void Player::playOrPause()
{
    qDebug() << "accpet playbtn signal";
    if (QMediaPlayer::PlayingState == qPlayer->state()) {
        qPlayer->pause();
        emit updatedState(false);
    } else {
        qPlayer->play();
        emit updatedState(true);
    }
}

void Player::nextMedia()
{
    qDebug() << "accept next song signal";
    playlist->setCurrentIndex(playlist->nextIndex());
    qPlayer->play();
}

void Player::lastMedia()
{
    qDebug() << "accept last song signal";
    playlist->setCurrentIndex(playlist->previousIndex());
    qPlayer->play();
}

void Player::updatePlaymode()
{
    qDebug() << "accept mode change signal";
    qint8 index = database->getDataFromSetup("playmode");
    if (index < 4) {
        index += index;
    } else {
        index = 0;
    }

    switch (index) {
    case ITEMONCE:
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        break;
    case ITEMLOOP:
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        break;
    case SEQUENTIAL:
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
        break;
    case LOOP:
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        break;
    case RANDOM:
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        break;
    default:
        break;
    }
    database->updatePlaymode(index);
    emit updatedMode(index);
}

void Player::setPlaylist(QStringList &list)
{
    //    Q_ASSERT(!list.isEmpty());
    QListIterator<QString> path(list);
    while (path.hasNext()) {
        auto song = path.next();
        playlist->addMedia(QUrl::fromLocalFile(song));
    }

    initPlaymode();
    qPlayer->setPlaylist(playlist);
}