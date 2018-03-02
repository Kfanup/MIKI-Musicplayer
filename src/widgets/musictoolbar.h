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
    explicit MusicToolBar(qint32 volume, QWidget *parent = 0);
    ~MusicToolBar();

    void onPlayModeBtnClicked();
    void onPreviousBtnClicked();
    void onPauseBtnClicked();
    void onNextBtnClicked();
    void setPlayModeIcon(qint32 index);
    void setPauseBtnIcon(bool status);

public slots:
    void updateModeIcon(qint32 index);
    void updateStateIcon(bool state);
    void updateVolumeValue(int value);

signals:
    void playModeBtnClicked();
    void previousBtnClicked();
    void pauseBtnClicked();
    void nextBtnClicked();
    void volumeChanged(int);

private:
    QToolButton *playModeBtn = NULL;
    QToolButton *previousBtn = NULL;
    QToolButton *pauseBtn = NULL;
    QToolButton *nextBtn = NULL;
    QSlider *volumeSlider = NULL;
};
