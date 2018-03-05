#include "playlist.h"

Playlist::Playlist(const PlaylistMeta &PlaylistMeta, QObject *parent)
    : QObject(parent)
{
    this->playlistMeta = PlaylistMeta;
}

Playlist *Playlist::getInstance(const PlaylistMeta &PlaylistMeta)
{
    static Playlist instance(PlaylistMeta);
    return &instance;
}

inline QString Playlist::getID() const
{
    return playlistMeta.id;
}

inline QString Playlist::getDisplayName() const
{
    return playlistMeta.displayName;
}

inline int Playlist::getLength() const
{
    return playlistMeta.metas.size();
}

inline int Playlist::getSortID() const
{
    return playlistMeta.sortID;
}

inline int Playlist::getSortType() const
{
    return playlistMeta.sortType;
}

inline bool Playlist::isActive() const
{
    return playlistMeta.active;
}

inline bool Playlist::isContains(const MetaPtr meta) const
{
    return !meta.isNull() && playlistMeta.metas.contains(meta->hash);
}

inline void Playlist::setActive(bool isActive)
{
    playlistMeta.active = isActive;
}

const MetaPtr Playlist::getFirst() const
{
    return playlistMeta.metas.value(playlistMeta.sortMetas.value(0));
}

const MetaPtr Playlist::getPrevious(const MetaPtr meta) const
{
    if (meta.isNull() || 0 == playlistMeta.sortMetas.size()) {
        return MetaPtr();
    }
    auto index = playlistMeta.sortMetas.indexOf(meta->hash);
    auto previous = (index + playlistMeta.sortMetas.length() - 1) % playlistMeta.sortMetas.length();
    return playlistMeta.metas.value(playlistMeta.sortMetas.at(previous));
}

const MetaPtr Playlist::getNext(const MetaPtr meta) const
{
    if (meta.isNull() || 0 == playlistMeta.sortMetas.size()) {
        return MetaPtr();
    }
    auto index = playlistMeta.sortMetas.indexOf(meta->hash);
    auto next = (index + 1) % playlistMeta.sortMetas.length();
    return playlistMeta.metas.value(playlistMeta.sortMetas.at(next));
}

const MetaPtr Playlist::getNowPlaying() const
{
    return playlistMeta.playingMeta;
}
