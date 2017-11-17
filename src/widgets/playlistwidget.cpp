#include "playlistwidget.h"
#include <QEvent>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

using namespace MMusic;

PlayListWidget::PlayListWidget(QWidget *parent)
    : QWidget(parent)
{
    database = new MusicDatabase;
    songs = database->getAllMeta();
    songCount = songs.count();
    sizePolicy();
    setMinimumSize(450, 500);
    setStyleSheet("color:black");

    nowPlayingLabel = new QLabel(tr("正在播放"));
    nowPlayingLabel->setAlignment(Qt::AlignLeft);
    nowPlayingLabel->setStyleSheet("font-size: 16px");
    playListLabel = new QLabel(tr("播放列表"));
    playListLabel->setAlignment(Qt::AlignLeft);
    playListLabel->setStyleSheet("font-size: 16px");

    setPlayListStyle();

    playout = new QVBoxLayout;
    playout->addWidget(nowPlayingLabel);
    playout->addWidget(playListLabel);
    playout->addWidget(playListWidget);
    //    playout->addStretch(1);

    setLayout(playout);

    nowPlayingLabel->installEventFilter(this);
    playListLabel->installEventFilter(this);

    connect(playListWidget, &QTableWidget::doubleClicked, this, &PlayListWidget::playByIndex);
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

QStringList PlayListWidget::initPlaylist()
{
    QStringList songList;
    //--将列表转为可迭代对象进行遍历
    QList<MusicMeta>::iterator i;
    int index = 0;
    for (i = songs.begin(); i != songs.end(); ++i) {
        playListWidget->setItem(index, 0, new QTableWidgetItem(i->title));
        playListWidget->setItem(index, 1, new QTableWidgetItem(i->author));
        playListWidget->setItem(index, 2, new QTableWidgetItem(length2String(i->length)));
        songList.append(i->localPath);
        ++index;
    }
    qDebug() << "songList" << songList;
    return songList;
}

void PlayListWidget::setPlayListStyle()
{
    QStringList header;
    header << "歌名"
           << "歌手"
           << "长度";

    playListWidget = new QTableWidget;
    playListWidget->setColumnCount(3);
    playListWidget->setRowCount(songCount);
    playListWidget->setHorizontalHeaderLabels(header);
    playListWidget->setShowGrid(false);
    //    playListWidget->setFrameShape(QFrame::NoFrame);
    playListWidget->verticalHeader()->setVisible(false);
    playListWidget->horizontalHeader()->setVisible(false);
    playListWidget->horizontalHeader()->setStretchLastSection(true);
    playListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    playListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    playListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    playListWidget->horizontalHeader()->resizeSection(0, 180);
    playListWidget->horizontalHeader()->resizeSection(1, 140);
    playListWidget->horizontalHeader()->resizeSection(2, 80);
}

inline void PlayListWidget::playByIndex(const QModelIndex &index)
{
    emit gettedPlayIndex(index.row());
}
