#pragma once

#include <QDir>
#include <QWidget>
#include <QFileInfoList>
#include <QFileDialog>

class MusicFileManager : public QWidget
{
    Q_OBJECT
public:
    explicit MusicFileManager(QWidget *parent = nullptr);
    QFileInfoList getMusicFiles(QString path);
    QFileInfoList addMusicFiles(QStringList paths);
    QFileInfoList addMediaDir();
    QFileInfoList addMedia();
    void updateMusicFiles();

private:
    QStringList filter = { "*.mp3", "*.wav", "*.wma" };
    QFileDialog *fileDialog;
};
