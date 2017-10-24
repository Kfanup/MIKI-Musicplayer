#pragma once

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QFileInfoList>
#include <QTableWidget>
#include <QMediaContent>
#include <QMediaResource>
#include <QVBoxLayout>

class PlayListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayListWidget(QFileInfoList songList, QWidget *parent = 0);

signals:
    void nowPlayingClicked();
    void playingListClicked();

private:
    qint32 songCount;
    QList<QMediaContent *> songList;
    QLabel *nowPlayingLabel;
    QLabel *playListLabel;
    QTableWidget *playListWidget;
    QVBoxLayout *playout;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
};
