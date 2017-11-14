#pragma once

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
    void onPlayModeBtnClicked();
    void onPreviousBtnClicked();
    void onPauseBtnClicked();
    void onNextBtnClicked();

signals:
    void playModeBtnClicked();
    void previousBtnClicked();
    void pauseBtnClicked();
    void nextBtnClicked();

private:
    QToolButton *playModeBtn;
    QToolButton *previousBtn;
    QToolButton *pauseBtn;
    QToolButton *nextBtn;
};
