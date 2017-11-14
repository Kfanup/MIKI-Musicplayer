#pragma once

#include <QWidget>
#include <QSlider>
#include <QLabel>

class MusicSliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicSliderWidget(QWidget *parent = 0);

private:
    QSlider *musicSlider;
    QLabel *nowTimeLabel;
    QLabel *allTimeLabel;
};
