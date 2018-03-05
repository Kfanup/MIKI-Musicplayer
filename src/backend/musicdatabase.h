#ifndef MUSICDATABASE_H
#define MUSICDATABASE_H

#include <QObject>
#include "util/music_global.h"
#include "util/musicfilemanager.h"
#include "musicmeta.h"
#include "playlistmeta.h"

class MusicDatabase : public QObject, public MMusic::MSingleTon<MusicDatabase>
{
    Q_OBJECT
public:
    explicit MusicDatabase(QObject *parent = nullptr);
    static MusicDatabase* getInstance(void);

    void initDatabase();
    void initSetup();

    bool isPlayListExist(const QString &id);
    bool isMusicMetaExist(const QString &hash);

    QList<MusicMeta> getAllMeta();
    QStringList getAllPlaylist();
    qint32 getPlaymodeFromSetup();
    qint32 getVolumeFromSetup();

signals:

public slots:
    void addPlaylist(const PlaylistMeta &PlaylistMeta);
    void addMusicMeta(const MusicMeta meta);
    void addMusicMetaList(const QList<MusicMeta> metaList);
    void removePlaylist(const PlaylistMeta &PlaylistMeta);
    void removeMusic(const MetaPtr meta, const PlaylistMeta &PlaylistMeta);
    void updatePlaymode(qint32 index);
    void updateVolume(qint32 volume);

private:
};

#endif // MUSICDATABASE_H
