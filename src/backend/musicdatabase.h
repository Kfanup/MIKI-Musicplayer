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
    void initSetup();

    bool isPlayListExist(const QString &id);
    bool isMusicMetaExist(const QString &hash);

    QList<MusicMeta> getAllMeta();
    QStringList getAllPlaylist();
    qint8 getDataFromSetup(QString key);

signals:

public slots:
    void addPlaylist(const PlaylistMeta &PlaylistMeta);
    void addMusicMeta(const MusicMeta meta);
    void addMusicMetaList(const QList<MusicMeta> metaList);
    void removePlaylist(const PlaylistMeta &PlaylistMeta);
    void removeMusic(const MetaPtr meta, const PlaylistMeta &PlaylistMeta);
    void updatePlaymode(qint8 index);
    void updateVolume(qint8 volume);

private:
};

#endif // MUSICDATABASE_H
