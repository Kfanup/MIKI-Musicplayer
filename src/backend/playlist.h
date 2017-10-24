#pragma once

#include <QObject>
#include <QSharedPointer>
#include "playlistmeta.h"
#include "musicmeta.h"

class Playlist : public QObject
{
    Q_OBJECT
public:
    explicit Playlist(const PlaylistMeta &PlaylistMeta, QObject *parent = nullptr);

    enum SortType {
        SortByTitle = 0,
        SortByAddTime,
        SortByAuthor,
    };

    void loadMusic();

public:
    QString getID() const;
    QString getDisplayName() const;
    int getLength() const;
    int getSortType() const;
    int getSortID() const;
    bool isActive() const;
    bool isContains(const MetaPtr meta) const;
    void setActive(bool isActive);

    const MetaPtr getFirst() const;
    const MetaPtr getPrevious(const MetaPtr meta) const;
    const MetaPtr getNext(const MetaPtr meta) const;
    const MetaPtr getNowPlaying() const;

signals:

public slots:

private:
    PlaylistMeta playlistMeta;
};

typedef QSharedPointer<Playlist> PlaylistPtr;
