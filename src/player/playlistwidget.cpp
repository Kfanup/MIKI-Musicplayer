#include "playlistwidget.h"
#include <QEvent>

PlayListWidget::PlayListWidget(QFileInfoList songList, QWidget *parent)
    : QWidget(parent)
{
    songCount = songList.count();
    setFixedSize(300, 180);
    setStyleSheet("color:black");

    nowPlayingLabel = new QLabel(tr("正在播放"));
    nowPlayingLabel->setAlignment(Qt::AlignLeft);
    nowPlayingLabel->setStyleSheet("font-size: 16px");
    playListLabel = new QLabel(tr("播放列表"));
    playListLabel->setAlignment(Qt::AlignLeft);
    playListLabel->setStyleSheet("font-size: 16px");

    playListWidget = new QTableWidget(songCount, 2, this);

    playout = new QVBoxLayout;
    playout->addWidget(nowPlayingLabel);
    playout->addWidget(playListLabel);
    playout->addWidget(playListWidget);
    playout->addStretch(1);

    setLayout(playout);
    nowPlayingLabel->installEventFilter(this);
    playListLabel->installEventFilter(this);
}

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
