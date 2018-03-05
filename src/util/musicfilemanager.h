#pragma once

#include <QDir>
#include <QWidget>
#include <QStandardPaths>
#include <QFileInfoList>
#include <QFileDialog>
#include "musicmeta.h"

class MusicFileManager : public QWidget
{
    Q_OBJECT
public:
    explicit MusicFileManager(QWidget *parent = nullptr);
    static MusicFileManager *getInstance();
    QFileInfoList getMusicFiles(QString path);
    QString getCachePath() const ;
    //    QStringList addMusicFiles(QStringList paths);
    QFileInfoList addMediaDir();
    QStringList addMedia();
    void updateMusicFiles();
    MetaPtr meta2metaPtr(MusicMeta meta);

private:
    QStringList filter = { "*.mp3", "*.wav", "*.wma" };
    QFileDialog *fileDialog;
};
