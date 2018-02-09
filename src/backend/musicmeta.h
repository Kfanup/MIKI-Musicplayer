#pragma once

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QSharedPointer>
//#include <taglib/tag.h>
//#include <taglib/fileref.h>
//#include <taglib/taglib.h>
//#include <taglib/tpropertymap.h>
extern "C" {
#include "libavformat/avformat.h"
}

class MusicMeta
{
public:
    QString hash;
    QString localPath;
    QString title;
    QString author;
    QString album;
    //    QString mediaType;
    //    QStringList keyWords;

    qint64 timestamp = 0;
    qint64 offset = 0;
    qint64 length = 0;
    qint64 size = 0;
    //    qint64 searchID = 0;

    bool favourite = false;

    static void init();
    static MusicMeta fromLocalfile(const QFileInfo &fileinfo);
    static void updateMetaFromLocalfile(MusicMeta *meta, const QFileInfo &fileinfo);
};

typedef QSharedPointer<MusicMeta> MetaPtr;
typedef QList<MetaPtr> MetaPtrList;
