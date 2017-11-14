#include "musicmeta.h"
#include "util/music_global.h"
#include <QDateTime>
#include <QDebug>

using namespace MMusic;

void MusicMeta::init()
{
    //注册库中含有的所有可用的文件格式和编码器
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
        av_dump_format(pFormatCtx, 0, meta->localPath.toStdString().c_str(), 0);
        int64_t duration = pFormatCtx->duration / 1000;

        if (duration > 0) {
            meta->length = duration;
        }
    }
    avformat_close_input(&pFormatCtx);
    avformat_free_context(pFormatCtx);

    meta->size = fileinfo.size();
    auto current = QDateTime::currentDateTime();
    meta->timestamp = current.toMSecsSinceEpoch() * 1000;
    meta->title = fileinfo.completeBaseName();
}
