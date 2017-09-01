#include "musicfilemanager.h"
#include <QStandardPaths>

MusicFileManager::MusicFileManager(QWidget *parent)
    : QWidget(parent)
{
}

QFileInfoList MusicFileManager::getMusicFiles(QString path)
{
    QDir dir(path);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    dir.setNameFilters(filter);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);

    for (int i = 0; i < folder_list.size(); i++) {
        QString path = folder_list.at(i).absoluteFilePath();
        QFileInfoList child_file_list = getMusicFiles(path);
        file_list.append(child_file_list);
    }
    return file_list;
}

QFileInfoList MusicFileManager::addMusicFiles(QStringList paths)
{
    QFileInfoList file_list;
    QFileInfo fileInfo;
    foreach (QString filePath, paths) {
        fileInfo.setFile(filePath);
        if (fileInfo.isFile()) {
            file_list.append(filePath);
        }
    }
    return file_list;
}

void MusicFileManager::updateMusicFiles()
{
}

QFileInfoList MusicFileManager::addMediaDir()
{
    fileDialog = new QFileDialog(this);
    QString dirPath = QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0);
    //    QDir dir(dirPath);
    //    fileDialog->setFileMode(QFileDialog::Directory);
    //    fileDialog->setDirectory(dir);
    dirPath = fileDialog->getExistingDirectory(this, "请选择音乐文件夹", dirPath);
    return getMusicFiles(dirPath);
}

QFileInfoList MusicFileManager::addMedia()
{
    fileDialog = new QFileDialog(this);
    QString filePath = QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0);
    //    QDir dir(filePath);
    QStringList filePaths =
        fileDialog->getOpenFileNames(this, "请选择音乐文件", filePath, "Media file(*.mp3 *.wav)");
    return addMusicFiles(filePaths);
}
