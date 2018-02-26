#include "playlistwidget.h"
#include <QEvent>
#include <QTableWidget>
#include <QHeaderView>
#include <QStandardPaths>
#include <QDebug>

using namespace MMusic;

PlayListWidget::PlayListWidget(QWidget *parent)
    : QWidget(parent)
{
    model = new Mysqlquerymodel;
    model->refresh();
    filemanager = new MusicFileManager(this);

    QTableView *view = new QTableView(this);
    view->setModel(model);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->resizeColumnsToContents();
    view->sortByColumn(0, Qt::AscendingOrder);
    view->verticalHeader()->hide();
//    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setAlternatingRowColors(true);
    view->setShowGrid(false);
    view->setColumnWidth(0,340);
    view->setColumnWidth(1,100);


    QHeaderView *header = view->horizontalHeader();
    header->setStretchLastSection(true);
//    header->setSectionResizeMode(QHeaderView::ResizeToContents);


    sizePolicy();
//    setMinimumSize(450, 500);
    setStyleSheet("color:black");

    nowPlayingLabel = new QLabel(tr("正在播放"),this);
    nowPlayingLabel->setAlignment(Qt::AlignLeft);
    nowPlayingLabel->setStyleSheet("font-size: 16px");
    playListLabel = new QLabel(tr("播放列表"),this);
    playListLabel->setAlignment(Qt::AlignLeft);
    playListLabel->setStyleSheet("font-size: 16px");

    playout = new QVBoxLayout(this);
    playout->addWidget(nowPlayingLabel);
    playout->addWidget(playListLabel);
    playout->addWidget(view);
    //    playout->addStretch(1);

    setLayout(playout);

    nowPlayingLabel->installEventFilter(this);
    playListLabel->installEventFilter(this);

    connect(view, &QTableView::doubleClicked, this, &PlayListWidget::playByIndex);
}

PlayListWidget::~PlayListWidget()
{
    delete model;
    delete nowPlayingLabel;
    delete playListLabel;
}

/***
 * @brief 事件过滤器
 * @param obj
 * @param ev
 * @return
 */
bool PlayListWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == nowPlayingLabel)
        if (ev->type() == QEvent::MouseButtonPress) {
            emit nowPlayingClicked();
            return true;
        } else {
            return false;
        }
    else if (obj == playListLabel)
        if (ev->type() == QEvent::MouseButtonPress) {
            emit playingListClicked();
            return true;
        } else {
            return false;
        }
    else {
        return PlayListWidget::eventFilter(obj, ev);
    }
}

QStringList PlayListWidget::getPlaylistFromDB()
{
    MusicDatabase *database = new MusicDatabase;
    QList<MusicMeta> songs;
    songs = database->getAllMeta();
    QStringList songList;
    //--将列表转为可迭代对象进行遍历
    QList<MusicMeta>::iterator i;
    int index = 0;
    for (i = songs.begin(); i != songs.end(); ++i) {
        songList.append(i->localPath);
        ++index;
    }
    qDebug() << "songList" << songList;
    database->deleteLater();
    return songList;
}

inline void PlayListWidget::playByIndex(const QModelIndex &index)
{
    emit gettedPlayIndex(index.row());
}

void PlayListWidget::updatePlaylist()
{
    model->refresh();
}
