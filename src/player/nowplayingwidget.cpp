#include "nowplayingwidget.h"
#include <QEvent>

NowPlayingWidget::NowPlayingWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(300, 180);
    setStyleSheet("color:white");

    QString strHeightText = "<p style=\"line-height:%1%\">%2<p>";
    songName = strHeightText.arg(300).arg(songName);
    nowPlayingLabel = new QLabel(tr("正在播放"));
    nowPlayingLabel->setAlignment(Qt::AlignLeft);
    nowPlayingLabel->setStyleSheet("font-size: 20px");
    playListLabel = new QLabel(tr("播放列表"));
    playListLabel->setAlignment(Qt::AlignLeft);
    playListLabel->setStyleSheet("font-size: 20px");

    QFont mfont1("Microsoft YaHei", 18, 75);
    QFont mfont2("Microsoft YaHei", 14, 50);

    nameLable = new QLabel;
    nameLable->setAlignment(Qt::AlignLeft);
    nameLable->setText(songName);
    nameLable->setFont(mfont1);

    singerLable = new QLabel;
    singerLable->setAlignment(Qt::AlignLeft);
    singerLable->setText(singer);
    singerLable->setFont(mfont2);

    detailsLable = new QLabel;
    detailsLable->setAlignment(Qt::AlignLeft);
    detailsLable->setText(more);
    detailsLable->setFont(mfont2);

    playout = new QVBoxLayout;
    playout->addWidget(nowPlayingLabel);
    playout->addSpacing(5);
    playout->addWidget(nameLable);
    playout->addSpacing(0);
    playout->addWidget(singerLable);
    playout->addWidget(detailsLable);
    playout->addSpacing(30);
    playout->addWidget(playListLabel);

    setLayout(playout);

    nowPlayingLabel->installEventFilter(this);
    playListLabel->installEventFilter(this);
}

bool NowPlayingWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == nowPlayingLabel)
        if (ev->type() == QEvent::MouseButtonPress) {
            return true;
        } else {
            return false;
        }
    else if (obj == playListLabel)
        if (ev->type() == QEvent::MouseButtonPress) {
            return true;
        } else {
            return false;
        }
    else {
        return NowPlayingWidget::eventFilter(obj, ev);
    }
}
