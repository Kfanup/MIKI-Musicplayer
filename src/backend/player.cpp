#include "player.h"
#include <QMediaMetaData>

using namespace MMusic;
Player::Player(QString &localPath, QStringList &pathList, qint32 volume, QObject *parent)
    : QObject(parent)
{
    playlist = new QMediaPlaylist(this);
    qPlayer = new QMediaPlayer;
    database = MusicDatabase::getInstance();
    timer = new QTimer;
    this->localPlaylist = localPath;

    initPlaymode();
    setPlaylist(localPath,pathList);
    qPlayer->setPlaylist(playlist);
    qPlayer->setVolume(volume);

    connect(qPlayer, &QMediaPlayer::mediaStatusChanged, this, &Player::sendMetaSignal);
}

Player *Player::getInstance(QString &localPath, QStringList &pathList, qint32 volume)
{
    static Player instance(localPath, pathList, volume);
    return &instance;
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
    auto mode = database->getPlaymodeFromSetup();
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
    qint32 index = database->getPlaymodeFromSetup();
    qDebug() << "current playmode index is " << index;
    if (index < 4) {
        index += 1;
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

void Player::sendMetaSignal(QMediaPlayer::MediaStatus status)
{
    if (QMediaPlayer::BufferedMedia == status){
        QString title = qPlayer->metaData(QMediaMetaData::Title).toString();
        QString singer = qPlayer->metaData(QMediaMetaData::ContributingArtist).toString();
        QString album = qPlayer->metaData(QMediaMetaData::AlbumTitle).toString();
        QStringList metas = qPlayer->availableMetaData();
        QStringList strList;
        strList<<title<<singer<<album;
        qDebug() <<"title:"<<strList[0]<<"\tsinger:"<<strList[1]<<"\talbum:"<<strList[2];
        qDebug() <<"metas: "<<metas;
        emit gettedMetadata(strList);
    }
}

void Player::updateMediaPosition(int pos)
{
    qPlayer->pause();
    qPlayer->setPosition(pos);
    qPlayer->play();
}

void Player::updateVolume(int value)
{
    qPlayer->setVolume(value);
}

void Player::setPlaylist(QString localPath, QStringList list)
{
    //    Q_ASSERT(!list.isEmpty());
    playlist->load(QUrl::fromLocalFile(localPath),"m3u8");
    if (playlist->isEmpty()){
        QListIterator<QString> path(list);
        while (path.hasNext()) {
            auto song = path.next();
            playlist->addMedia(QUrl::fromLocalFile(song));
        }
        playlist->save(QUrl::fromLocalFile(localPath),"m3u8");
    }
}

void Player::updatePlaylist(QStringList list)
{
    QListIterator<QString> path(list);
    while (path.hasNext()) {
        auto song = path.next();
        playlist->addMedia(QUrl::fromLocalFile(song));
    }
    playlist->save(QUrl::fromLocalFile(localPlaylist),"m3u8");
}
