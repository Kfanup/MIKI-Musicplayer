#include "musicdatabase.h"
#include "databaseconnection.h"

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

    QSqlDatabase::database().commit();
}

bool MusicDatabase::isPlayListExist(const QString &id)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM playlist where id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << query.lastError();
        return false;
    }
    query.first();
    return query.value(0).toInt() > 0;
}

bool MusicDatabase::isMusicMetaExist(const QString &hash)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM mymusic where hash = :hash");
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
        return;
    }

    if (!query.exec(
            QString("CREATE TABLE IF NOT EXISTS playlist_%1 (music_id TEXT primary key not null, "
                    "playlist_id TEXT, sort_id INTEGER )")
                .arg(PlaylistMeta.id))) {
        qWarning() << query.lastError();
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

QList<MusicMeta> MusicDatabase::getAllMeta()
{
    QList<MusicMeta> metaList;
    QString execString = QString("SELECT hash, timestamp, title, author, album, mediatype, "
                                 "offset, length, size, search_id, favourite FROM mymusic");

    QSqlQuery query;
    query.prepare(execString);
    if (!query.exec()) {
        qWarning() << query.lastError();
        return metaList;
    }

    MusicMeta meta;
    while (query.next()) {
        meta.hash = query.value(0).toString();
        meta.timestamp = query.value(1).toInt();
        meta.title = query.value(2).toString();
        meta.author = query.value(3).toString();
        meta.album = query.value(4).toString();
        meta.mediaType = query.value(5).toString();
        meta.offset = query.value(6).toInt();
        meta.length = query.value(7).toInt();
        meta.size = query.value(8).toInt();
        meta.favourite = query.value(9).toBool();
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
