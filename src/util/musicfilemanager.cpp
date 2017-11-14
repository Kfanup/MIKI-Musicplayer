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

// QStringList MusicFileManager::addMusicFiles(QStringList paths)
//{
//    QFileInfoList file_list;
//    QFileInfo fileInfo;
//    foreach (QString filePath, paths) {
//        fileInfo.setFile(filePath);
//        if (fileInfo.isFile()) {
//            file_list.append(filePath);
//        }
//    }
//    return QStringList(file_list);
//}

void MusicFileManager::updateMusicFiles()
{
}

QFileInfoList MusicFileManager::addMediaDir()
{
    fileDialog = new QFileDialog(this);
    QString dirPath = QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0);
    //    QDir dir(dirPath);
    dirPath = fileDialog->getExistingDirectory(this, "请选择音乐文件夹", dirPath);
    return getMusicFiles(dirPath);
}

QStringList MusicFileManager::addMedia()
{
    fileDialog = new QFileDialog(this);
    QString filePath = QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0);

    QStringList filePaths = fileDialog->getOpenFileNames(this, "请选择音乐文件", filePath,
                                                         "Media file(*.mp3 *.wma *.wav)");
    return filePaths;
}

MetaPtr MusicFileManager::meta2metaPtr(MusicMeta meta)
{
    MetaPtr metaptr = MetaPtr(new MusicMeta);
    metaptr->hash = meta.hash;
    metaptr->album = meta.album;
    metaptr->author = meta.author;
    metaptr->favourite = meta.favourite;
    metaptr->length = meta.length;
    metaptr->localPath = meta.localPath;
    metaptr->offset = meta.offset;
    metaptr->size = meta.size;
    metaptr->timestamp = meta.timestamp;
    metaptr->title = meta.title;
    return metaptr;
}
