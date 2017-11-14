#pragma once

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QFileInfoList>
#include <QTableWidget>
#include <QMediaContent>
#include <QMediaResource>
#include <QVBoxLayout>
#include "backend/musicdatabase.h"
#include "backend/musicmeta.h"
#include "util/music_global.h"

class PlayListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayListWidget(QList<MusicMeta> songList, QWidget *parent = 0);

signals:
    void nowPlayingClicked();
    void playingListClicked();

private:
    void initPlayList(QList<MusicMeta> songs);

private:
    qint32 songCount;
    //    QList<QMediaContent *> songList;
    QLabel *nowPlayingLabel;
    QLabel *playListLabel;
    QTableWidget *playListWidget;
    QVBoxLayout *playout;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
};
