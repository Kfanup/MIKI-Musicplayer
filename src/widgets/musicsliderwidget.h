#pragma once

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include "backend/player.h"
#include "util/music_global.h"

class MusicSliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicSliderWidget(QWidget *parent = 0);
    void updatePosition(const qint64 pos);
    void updateTimeLabel(const qint64 time);

public slots:
    void setPosition(const qint64 pos);
    void setTimeLabel(const qint64 time);

private:
    QSlider *musicSlider;
    QLabel *nowTimeLabel;
    QLabel *allTimeLabel;
};
