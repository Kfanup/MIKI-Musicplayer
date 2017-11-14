#include "musicsliderwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MusicSliderWidget::MusicSliderWidget(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("color:white");
    musicSlider = new QSlider(Qt::Horizontal);
    musicSlider->setMaximum(100);
    musicSlider->setMinimum(0);
    musicSlider->setValue(0);
    musicSlider->setMinimumSize(400, 12);

    QLabel *nowTimeLabel = new QLabel(tr("00:00"));
    nowTimeLabel->setStyleSheet("color:black");
    nowTimeLabel->sizePolicy();
    nowTimeLabel->setMaximumSize(40, 12);
    QLabel *allTimeLabel = new QLabel(tr("00:00"));
    allTimeLabel->setStyleSheet("color:black");
    allTimeLabel->sizePolicy();
    allTimeLabel->setMaximumSize(40, 12);

    QHBoxLayout *musiclayout = new QHBoxLayout;
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
