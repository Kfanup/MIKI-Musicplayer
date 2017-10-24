#pragma once

#include <QMap>
#include "musicmeta.h"

class PlaylistMeta
{
public:
    QString id;
    QString displayName;

    uint sortID = 0;
    int sortType = 0;
    bool active;

    MetaPtr playingMeta;
    QStringList sortMetas;

    QMap<QString, MetaPtr> metas;
};
