#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class PlayListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayListWidget(QWidget *parent = 0);

signals:
    void nowPlayingClicked();
    void playingListClicked();

public slots:

private:
    QLabel *nowPlayingLabel;
    QLabel *playListLabel;
    QVBoxLayout *playout;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
};

#endif // PLAYLISTWIDGET_H
