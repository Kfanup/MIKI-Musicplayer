#pragma once

#include <QObject>
#include <memory>
#include <QCryptographicHash>
#include "musicmeta.h"
#include "util/music_global.h"

class MusicLibraryPrivate;
class MusicLibrary : public QObject, public MMusic::MSingleTon<MusicLibrary>
{
    Q_OBJECT
public:
    explicit MusicLibrary(QObject *parent = nullptr);
    static MusicLibrary *getInstance(void);
    ~MusicLibrary();

    MetaPtr getMeta(const QString &hash);
    MetaPtrList importFile(const QString &filePath);
    bool iscontains(const QString &hash);
    bool isEmpty();

signals:

public slots:

private:
    //    MusicLibraryPrivate *d_ptr;
    friend class MMusic::MSingleTon<MusicLibrary>;
    QScopedPointer<MusicLibraryPrivate> d_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_ptr), MusicLibrary)
};
