#include "musiclibrary.h"

#include <QDebug>
#include <QFileInfo>
#include <QMap>

#include "musicmeta.h"

class MusicLibraryPrivate
{
public:
    MusicLibraryPrivate(MusicLibrary *parent)
        : q_ptr(parent)
    {
    }

    void initDataBase();
    MetaPtr createMeta(const QFileInfo &fileInfo);
    MetaPtr importMeta(const QString &filePath);

private:
    QMap<QString, MetaPtr> metas;
    MusicLibrary *q_ptr;
    Q_DECLARE_PUBLIC(MusicLibrary)
};

void MusicLibraryPrivate::initDataBase()
{
}

MetaPtr MusicLibraryPrivate::createMeta(const QFileInfo &fileInfo)
{
    auto hash = MMusic::filePathToHash(fileInfo.absoluteFilePath());
    auto meta = MetaPtr(new MusicMeta);
    meta->hash = hash;
    return meta;
}

MetaPtr MusicLibraryPrivate::importMeta(const QString &filePath)
{
    QFileInfo fileinfo(filePath);
    auto hash = MMusic::filePathToHash(filePath);
    if (MusicLibrary::instance()->iscontains(hash)) {
        qDebug() << "exit becase meta is exist:" << MusicLibrary::instance()->getMeta(hash);
        return MusicLibrary::instance()->getMeta(hash);
    }
    auto meta = createMeta(fileinfo);

    metas.insert(meta->hash, meta);

    return meta;
}

MusicLibrary::MusicLibrary(QObject *parent)
    : QObject(parent)
    , d_ptr(new MusicLibraryPrivate(this))
{
}

MusicLibrary::~MusicLibrary()
{
}

bool MusicLibrary::isEmpty()
{
    Q_D(MusicLibrary);
    return d->metas.isEmpty();
}

bool MusicLibrary::iscontains(const QString &hash)
{
    Q_D(MusicLibrary);
    return d->metas.contains(hash);
}

MetaPtr MusicLibrary::getMeta(const QString &hash)
{
    Q_D(MusicLibrary);
    return d->metas.value(hash);
}

MetaPtrList MusicLibrary::importFile(const QString &filePath)
{
    Q_D(MusicLibrary);
    auto meta = d->importMeta(filePath);
    return MetaPtrList() << meta;
}

namespace MMusic {
QString filePathToHash(const QString &filePath)
{
    return QString(QCryptographicHash::hash(filePath.toUtf8(), QCryptographicHash::Md5).toHex());
}
}
