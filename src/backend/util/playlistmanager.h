#pragma once

#include <QObject>
#include "playlist.h"

class PlaylistManagerPrivate;
class PlaylistManager : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistManager(QObject *parent = nullptr);
    ~PlaylistManager();

    enum UpdateAction{
        AddPlaylist=0,
        RemovePlaylist,
        ChangeName,
    };

    QList<PlaylistPtr> getAllPlaylist();
    PlaylistPtr addPlaylist(const PlaylistMeta &PlaylistMeta);

public:
    void updatePlaylist(const PlaylistPtr &playlist,UpdateAction action);
signals:

public slots:


};
