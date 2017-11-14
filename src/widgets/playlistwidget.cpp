#include "playlistwidget.h"
#include <QEvent>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

using namespace MMusic;

PlayListWidget::PlayListWidget(QList<MusicMeta> songList, QWidget *parent)
    : QWidget(parent)
{
    songCount = songList.count();
    sizePolicy();
    setMinimumSize(450, 500);
    setStyleSheet("color:black");

    nowPlayingLabel = new QLabel(tr("正在播放"));
    nowPlayingLabel->setAlignment(Qt::AlignLeft);
    nowPlayingLabel->setStyleSheet("font-size: 16px");
    playListLabel = new QLabel(tr("播放列表"));
    playListLabel->setAlignment(Qt::AlignLeft);
    playListLabel->setStyleSheet("font-size: 16px");

    QStringList header;
    header << "歌名"
           << "歌手"
           << "长度";

    playListWidget = new QTableWidget;
    playListWidget->setColumnCount(3);
    playListWidget->setRowCount(songCount);
    playListWidget->setHorizontalHeaderLabels(header);
    playListWidget->setShowGrid(false);
    playListWidget->verticalHeader()->setVisible(false);
    playListWidget->horizontalHeader()->setStretchLastSection(true);
    playListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    playListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    playListWidget->horizontalHeader()->resizeSection(0, 180);
    playListWidget->horizontalHeader()->resizeSection(1, 140);
    playListWidget->horizontalHeader()->resizeSection(2, 80);

    playout = new QVBoxLayout;
    playout->addWidget(nowPlayingLabel);
    playout->addWidget(playListLabel);
    playout->addWidget(playListWidget);
    //    playout->addStretch(1);

    setLayout(playout);

    initPlayList(songList);
    nowPlayingLabel->installEventFilter(this);
    playListLabel->installEventFilter(this);
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

void PlayListWidget::initPlayList(QList<MusicMeta> songs)
{
    //将列表转为可迭代对象进行遍历
    QList<MusicMeta>::iterator i;
    int index = 0;
    for (i = songs.begin(); i != songs.end(); ++i) {
        playListWidget->setItem(index, 0, new QTableWidgetItem(i->title));
        playListWidget->setItem(index, 1, new QTableWidgetItem(i->author));
        qDebug() << i->author;
        playListWidget->setItem(index, 2, new QTableWidgetItem(length2String(i->length)));
        qDebug() << length2String(i->length);
        ++index;
    }
}
