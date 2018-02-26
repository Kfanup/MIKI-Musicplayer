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
#include "backend/mysqlquerymodel.h"
#include "util/music_global.h"

class Player;
class PlayListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayListWidget(QWidget *parent = 0);
    ~PlayListWidget();
    QStringList getPlaylistFromDB();

signals:
    void nowPlayingClicked();
    void playingListClicked();
    //    void gettedSongList(QStringList &list);
    void gettedPlayIndex(int index);

public slots:
    void playByIndex(const QModelIndex &index);
    void updatePlaylist();

private slots:


private:
    qint32 songCount;
    //    QList<QMediaContent *> songList;
    QLabel *nowPlayingLabel = NULL;
    QLabel *playListLabel = NULL;
    Mysqlquerymodel *model = NULL;
    QVBoxLayout *playout = NULL;
    MusicFileManager *filemanager = NULL;
//    MusicDatabase *database = NULL;
//    QList<MusicMeta> songs;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
};
