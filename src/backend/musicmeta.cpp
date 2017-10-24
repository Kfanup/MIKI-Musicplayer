#include "musicmeta.h"
#include "util/music_global.h"
#include <QDateTime>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/taglib.h>
#include <taglib/tpropertymap.h>
#include <libavformat/avformat.h>

using namespace MMusic;

void MusicMeta::init()
{
    av_register_all();
}

MusicMeta MusicMeta::fromLocalfile(const QFileInfo &fileinfo)
{
    MusicMeta meta;
    meta.hash = filePathToHash(fileinfo.absoluteFilePath());
    updateMetaFromLocalfile(&meta, fileinfo);
    return meta;
}

void MusicMeta::updateMetaFromLocalfile(MusicMeta *meta, const QFileInfo &fileinfo)
{
    meta->localPath = fileinfo.absoluteFilePath();
    if (meta->localPath.isEmpty()) {
        return;
    }
    AVFormatContext *pFormatCtx = avformat_alloc_context();
    avformat_open_input(&pFormatCtx, meta->localPath.toStdString().c_str(), NULL, NULL);
    if (pFormatCtx) {
        avformat_find_stream_info(pFormatCtx, NULL);
        int64_t duration = pFormatCtx->duration / 1000;
        if (duration > 0) {
            meta->length = duration;
        }
    }
    avformat_close_input(&pFormatCtx);
    avformat_free_context(pFormatCtx);

    meta->size = fileinfo.size();
    meta->mediaType = fileinfo.suffix();
    auto current = QDateTime::currentDateTime();
    meta->timestamp = current.toMSecsSinceEpoch() * 1000;
    meta->title = fileinfo.completeBaseName();
}
