#ifndef NOWPLAYINGWIDGET_H
#define NOWPLAYINGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QVBoxLayout>

class NowPlayingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NowPlayingWidget(QWidget *parent = 0);

signals:

private:
    QString songName="Take Me To Your Heart";
    QString singer="Jay";
    QString more="more";
    QLabel *nameLable;
    QLabel *singerLable;
    QLabel *detailsLable;
    QLabel *nowPlayingLabel;
    QLabel *playListLabel;
    QVBoxLayout *playout;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
};

#endif // NOWPLAYINGWIDGET_H
