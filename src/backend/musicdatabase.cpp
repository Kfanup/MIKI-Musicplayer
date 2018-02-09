#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>
#include "musicdatabase.h"

static bool createConnection()
{
    QDir dir(QStandardPaths::standardLocations(QStandardPaths::CacheLocation).first());
    if (!dir.exists()) {
        dir.mkpath(QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation).first());
        dir.setPath(
            QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation).first());
    }
    QString cachePath = dir.absolutePath() + QString("/mikimusic.sqlite");
    qDebug() << cachePath;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(cachePath);
    if (!db.open()) {
        qCritical() << db.lastError() << "please check " << cachePath;
        qDebug() << "can not open cachepath";
        return false;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS mymusic (hash TEXT primary key not null, "
               "timestamp INTEGER, "
               "title VARCHAR(256), author VARCHAR(256), "
               "album VARCHAR(256), "
               "offset INTEGER, length INTEGER, "
               "size INTEGER, favourite INTEGER(32), "
               "localpath VARCHAR(256))");
    query.exec("CREATE TABLE IF NOT EXISTS playlist (id TEXT primary key not null, "
               "displayname VARCHAR(4096), "
               "sort_type INTEGER(32), sort_id INTEGER(32)) ");
    query.exec("CREATE TABLE IF NOT EXISTS artist (id INTEGER primary key not null, "
               "name VARCHAR(20))");
    query.exec("CREATE TABLE IF NOT EXISTS setup (id TEXT primary key not null, "
               "playmode INTEGER ,volume INTEGER)");
    return true;
}

MusicDatabase::MusicDatabase(QObject *parent)
    : QObject(parent)
{
}

void MusicDatabase::initDatabase()
{
    createConnection();
    QSqlDatabase::database().transaction();
    PlaylistMeta playlistmeta;
    playlistmeta.id = "all";
    playlistmeta.displayName = "所有音乐";
    playlistmeta.sortID = 0;
    if (!isPlayListExist(playlistmeta.id)) {
        addPlaylist(playlistmeta);
    }
    playlistmeta.id = "fav";
    playlistmeta.displayName = "我最喜欢";
    playlistmeta.sortID = 1;
    if (!isPlayListExist(playlistmeta.id)) {
        addPlaylist(playlistmeta);
    }

    initSetup();
    QSqlDatabase::database().commit();
}

void MusicDatabase::initSetup()
{
    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO setup (id, playmode, volume)"
                  "VALUES (:id, :playmode, :volume)");
    query.bindValue(":id", "DefaultUser");
    query.bindValue(":playmode", 2);
    query.bindValue(":volume", 30);

    if (!query.exec()) {
        qWarning() << query.lastError();
        return;
    }
}

bool MusicDatabase::isPlayListExist(const QString &id)
{
    QSqlQuery query;
    QString sqlstring = QString("SELECT COUNT(*) FROM playlist where id = '%1'").arg(id);

    if (!query.exec(sqlstring)) {
        qWarning() << query.lastError();
        return false;
    }
    query.first();
    return query.value(0).toInt() > 0;
}

bool MusicDatabase::isMusicMetaExist(const QString &hash)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM mymusic where hash = :hash;");
    query.bindValue(":hash", hash);

    if (!query.exec()) {
        qWarning() << query.lastError();
        return false;
    }
    query.first();
    return query.value(0).toInt() > 0;
}

void MusicDatabase::addPlaylist(const PlaylistMeta &PlaylistMeta)
{
    QSqlQuery query;
    query.prepare("INSERT INTO playlist (id, displayname, sort_type, sort_id )"
                  "VALUES (:id, :displayname, :sort_type, :sort_id )");
    query.bindValue(":id", PlaylistMeta.id);
    query.bindValue(":displayname", PlaylistMeta.displayName);
    query.bindValue(":sort_type", PlaylistMeta.sortType);
    query.bindValue(":sort_id", PlaylistMeta.sortID);

    if (!query.exec()) {
        qWarning() << query.lastError();
        qDebug() << "add playlist fail";
        return;
    }

    if (!query.exec(
            QString("CREATE TABLE IF NOT EXISTS playlist_%1 (music_id TEXT primary key not null, "
                    "playlist_id TEXT, sort_id INTEGER )")
                .arg(PlaylistMeta.id))) {
        qWarning() << query.lastError();
        qDebug() << "add playlist_% fail";
        return;
    }
    return;
}

void MusicDatabase::removePlaylist(const PlaylistMeta &PlaylistMeta)
{
    QSqlQuery query;
    if (!query.exec(QString("DROP TABLE IF EXISTS playlist_%1").arg(PlaylistMeta.id))) {
        qWarning() << query.lastError();
        return;
    }

    if (!query.exec(QString("DELETE FROM playlist WHERE id = '%1'").arg(PlaylistMeta.id))) {
        qWarning() << query.lastError();
        return;
    }
}

void MusicDatabase::removeMusic(const MetaPtr meta, const PlaylistMeta &PlaylistMeta)
{
    if (meta.isNull()) {
        return;
    }

    QSqlQuery query;
    if (!query.exec(QString("DELETE FROM playlist_%1 WHERE music_id = '%2'")
                        .arg(PlaylistMeta.id)
                        .arg(meta->hash))) {
        qWarning() << query.lastError();
        return;
    }
}

void MusicDatabase::updatePlaymode(qint32 index)
{
    QSqlQuery query;
    query.prepare(QString("UPDATE setup SET playmode = %1 WHERE id = 'DefaultUser'").arg(index));

    if (!query.exec()) {
        qWarning() << query.lastError();
        qDebug() << "update playmode fail";
        return;
    }
}

void MusicDatabase::updateVolume(qint32 volume)
{
    QSqlQuery query;
    query.prepare(QString("UPDATE setup SET volume = %1 WHERE id = 'DefaultUser'").arg(volume));

    if (!query.exec()) {
        qWarning() << query.lastError();
        qDebug() << "update volume fail";
        return;
    }
}

QList<MusicMeta> MusicDatabase::getAllMeta()
{
    QList<MusicMeta> metaList;
    QString execString = QString("SELECT hash, timestamp, title, author, album, "
                                 "offset, length, size, favourite, localpath FROM mymusic");

    QSqlQuery query;
    query.prepare(execString);
    if (!query.exec()) {
        qWarning() << query.lastError();
        qDebug() << "get allmeta fail";
        return metaList;
    }

    while (query.next()) {
        MusicMeta meta;
        meta.hash = query.value(0).toString();
        meta.timestamp = query.value(1).toInt();
        meta.title = query.value(2).toString();
        meta.author = query.value(3).toString();
        meta.album = query.value(4).toString();
        meta.offset = query.value(5).toInt();
        meta.length = query.value(6).toInt();
        meta.size = query.value(7).toInt();
        meta.favourite = query.value(8).toBool();
        meta.localPath = query.value(9).toString();
        metaList << meta;
    }

    return metaList;
}

QStringList MusicDatabase::getAllPlaylist()
{
    QStringList list;
    QSqlQuery query;
    query.prepare("SELECT displayname FROM playlist");

    if (!query.exec()) {
        qWarning() << query.lastError();
        return list;
    }

    while (query.next()) {
        list << query.value(0).toString();
    }
    return list;
}

qint32 MusicDatabase::getPlaymodeFromSetup()
{
    QSqlQuery query;
    query.prepare(QString("SELECT playmode FROM setup WHERE id = 'DefaultUser'"));

    if (!query.exec()) {
        qWarning() << query.lastError();
        qDebug() << "get playmode setup fail";
    }
    query.next();
    qint32 index = query.value(0).toInt();
    qDebug() << "getted playmode index is "<<index;
    return query.value(0).toInt();
}

qint32 MusicDatabase::getVolumeFromSetup()
{
    QSqlQuery query;
    query.prepare(QString("SELECT volume FROM setup WHERE id = 'DefaultUser'"));

    if (!query.exec()) {
        qWarning() << query.lastError();
        qDebug() << "get volume setup fail";
    }
    query.next();
    qint32 index = query.value(0).toInt();
    qDebug() << "getted volume value is "<<index;
    return query.value(0).toInt();
}

void MusicDatabase::addMusicMeta(const MusicMeta meta)
{
    QSqlQuery query;
    query.prepare("INSERT INTO mymusic("
                  "hash, timestamp, title, author,album,"
                  "offset, length, size,"
                  "favourite,localpath)"
                  "VALUES ("
                  ":hash, :timestamp, :title, :author,"
                  ":album, :offset, :length,"
                  ":size, :favourite, :localpath)");
    query.bindValue(":hash", meta.hash);
    query.bindValue(":timestamp", meta.timestamp);
    query.bindValue(":title", meta.title);
    query.bindValue(":author", meta.author);
    query.bindValue(":album", meta.album);
    query.bindValue(":offset", meta.offset);
    query.bindValue(":length", meta.length);
    query.bindValue(":size", meta.size);
    query.bindValue(":favourite", meta.favourite);
    query.bindValue(":localpath", meta.localPath);

    if (!query.exec()) {
        qCritical() << query.lastError();
        qDebug() << "add musicmeta fail";
        return;
    }
}

void MusicDatabase::addMusicMetaList(const QList<MusicMeta> metaList)
{
    QSqlDatabase::database().transaction();
    for (auto &meta : metaList) {
        addMusicMeta(meta);
    }
    QSqlDatabase::database().commit();
}
