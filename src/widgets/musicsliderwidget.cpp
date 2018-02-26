#include "musicsliderwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

using namespace MMusic;
MusicSliderWidget::MusicSliderWidget(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("color:white");
    musicSlider = new QSlider(Qt::Horizontal,this);
    musicSlider->setMinimum(0);
    musicSlider->setValue(0);
    musicSlider->setMinimumSize(400, 12);

    nowTimeLabel = new QLabel(QString("00:00"),this);
    nowTimeLabel->setStyleSheet("color:black");
    nowTimeLabel->sizePolicy();
    nowTimeLabel->setMaximumSize(40, 12);
    allTimeLabel = new QLabel(QString("00:00"),this);
    allTimeLabel->setStyleSheet("color:black");
    allTimeLabel->sizePolicy();
    allTimeLabel->setMaximumSize(40, 12);

    QHBoxLayout *musiclayout = new QHBoxLayout(this);
    musiclayout->setAlignment(Qt::AlignCenter);
    musiclayout->addStretch(10);
    musiclayout->addWidget(nowTimeLabel);
    musiclayout->addStretch(1);
    musiclayout->addWidget(musicSlider);
    musiclayout->addStretch(1);
    musiclayout->addWidget(allTimeLabel);
    musiclayout->addStretch(10);

    setLayout(musiclayout);
}

void MusicSliderWidget::updatePosition(const qint64 pos)
{
    musicSlider->setSliderPosition(pos);
}

void MusicSliderWidget::updateTimeLabel(const qint64 time)
{
    nowTimeLabel->setText(length2String(time));
}

void MusicSliderWidget::setPosition(const qint64 pos)
{
    musicSlider->setMaximum(pos);
    musicSlider->setSliderPosition(0);
}

void MusicSliderWidget::setTimeLabel(const qint64 time)
{
    allTimeLabel->setText(length2String(time));
}
