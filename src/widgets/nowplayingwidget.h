#pragma once

#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QVBoxLayout>

class NowPlayingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NowPlayingWidget(QWidget *parent = 0);
    void updateLabel(QStringList strList);

signals:
    void nowPlayingClicked();
    void playingListClicked();

private:
    QLabel *nameLable = NULL;
    QLabel *singerLable = NULL;
    QLabel *detailsLable = NULL;
    QLabel *nowPlayingLabel = NULL;
    QLabel *playListLabel = NULL;
    QVBoxLayout *playout = NULL;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
};
