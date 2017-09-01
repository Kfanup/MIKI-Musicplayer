#ifndef MUSICTOOLBAR_H
#define MUSICTOOLBAR_H

#include <QWidget>
#include <QSlider>
#include <QToolBar>
#include <QToolButton>
#include "mplayer.h"

class MusicToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit MusicToolBar(QWidget *parent = 0);
    static QSlider *volumeSlider;
    //    void onAddSongClicked();
    //    void onAddSongDirClicked();
    void onPlayModeBtnClicked();
    void onPreviousBtnClicked();
    void onPauseBtnClicked();
    void onNextBtnClicked();
    QAction *addSong;
    QAction *addSongDir;

signals:
    //    void addSongClicked();
    //    void addSongDirClicked();
    void playModeBtnClicked();
    void previousBtnClicked();
    void pauseBtnClicked();
    void nextBtnClicked();

private:
    QToolBar *toolBar;
    QToolButton *playModeBtn;
    QToolButton *previousBtn;
    QToolButton *pauseBtn;
    QToolButton *nextBtn;
};

#endif // MUSICTOOLBAR_H
