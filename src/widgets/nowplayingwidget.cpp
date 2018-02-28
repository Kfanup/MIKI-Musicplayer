#include "nowplayingwidget.h"
#include <QEvent>

NowPlayingWidget::NowPlayingWidget(QWidget *parent)
    : QWidget(parent)
{
    sizePolicy();
    setMinimumSize(450, 500);
    setStyleSheet("color:black");

    QString label1 = "";
    QString label2 = "Music For MIKI";
    QString label3 = "";

    QString strHeightText = "<p style=\"line-height:%1%\">%2<p>";
    label1 = strHeightText.arg(300).arg(label1);
    nowPlayingLabel = new QLabel(tr("正在播放"),this);
    nowPlayingLabel->setAlignment(Qt::AlignLeft);
    nowPlayingLabel->setStyleSheet("font-size: 16px");
    playListLabel = new QLabel(tr("播放列表"),this);
    playListLabel->setAlignment(Qt::AlignLeft);
    playListLabel->setStyleSheet("font-size: 16px");

    QFont mfont1("Microsoft YaHei", 18, 75);
    QFont mfont2("Microsoft YaHei", 14, 50);

    nameLable = new QLabel(this);
    nameLable->setAlignment(Qt::AlignLeft);
    nameLable->setText(label1);
    nameLable->setFont(mfont1);

    singerLable = new QLabel(this);
    singerLable->setAlignment(Qt::AlignLeft);
    singerLable->setText(label2);
    singerLable->setFont(mfont2);

    detailsLable = new QLabel(this);
    detailsLable->setAlignment(Qt::AlignLeft);
    detailsLable->setText(label3);
    detailsLable->setFont(mfont2);

    playout = new QVBoxLayout(this);
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

void NowPlayingWidget::updateLabel(QStringList strList)
{
    nameLable->setText(strList[0]);
    singerLable->setText(QString("歌手:\t") + strList[1]);
    detailsLable->setText(QString("专辑:\t") + strList[2]);
}

/***
 * @brief 事件过滤器
 * @param obj
 * @param ev
 * @return
 */
bool NowPlayingWidget::eventFilter(QObject *obj, QEvent *ev)
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
        return NowPlayingWidget::eventFilter(obj, ev);
    }
}
