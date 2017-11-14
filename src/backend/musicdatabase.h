#ifndef MUSICDATABASE_H
#define MUSICDATABASE_H

#include <QObject>
#include "util/music_global.h"
#include "musicmeta.h"
#include "playlistmeta.h"

class MusicDatabase : public QObject, public MMusic::MSingleTon<MusicDatabase>
{
    Q_OBJECT
public:
    explicit MusicDatabase(QObject *parent = nullptr);

    void initDatabase();

    bool isPlayListExist(const QString &id);
    bool isMusicMetaExist(const QString &hash);

    QList<MusicMeta> getAllMeta();
    QStringList getAllPlaylist();
signals:

public slots:
    void addPlaylist(const PlaylistMeta &PlaylistMeta);
    void addMusicMeta(const MusicMeta meta);
    void addMusicMetaList(const QList<MusicMeta> metaList);
    void removePlaylist(const PlaylistMeta &PlaylistMeta);
    void removeMusic(const MetaPtr meta, const PlaylistMeta &PlaylistMeta);

private:
};

#endif // MUSICDATABASE_H
