#include "musicsliderwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MusicSliderWidget::MusicSliderWidget(QWidget* parent)
    : QWidget(parent)
{
    setStyleSheet("color:white");
    musicSlider = new QSlider(Qt::Horizontal);
    musicSlider->setMaximum(100);
    musicSlider->setMinimum(0);
    musicSlider->setValue(0);
    musicSlider->setFixedSize(400, 12);

    QLabel *nowTimeLabel=new QLabel(tr("00:00"));
    nowTimeLabel->setMaximumSize(40,12);
    QLabel *allTimeLabel=new QLabel(tr("00:00"));
    allTimeLabel->setMaximumSize(40,12);

    QHBoxLayout* mhlayout = new QHBoxLayout;
    mhlayout->setAlignment(Qt::AlignCenter);
    mhlayout->addStretch(2);
    mhlayout->addWidget(nowTimeLabel);
    mhlayout->addStretch(5);
    mhlayout->addWidget(allTimeLabel);
    mhlayout->addStretch(2);

    QHBoxLayout *musiclayout=new QHBoxLayout;
    musiclayout->setAlignment(Qt::AlignCenter);
    musiclayout->addWidget(musicSlider);

    QVBoxLayout* mvlayout = new QVBoxLayout;
    mvlayout->setAlignment(Qt::AlignCenter);
    mvlayout->addLayout(musiclayout);
    mvlayout->setMargin(0);
    mvlayout->addSpacing(0);
    mvlayout->addLayout(mhlayout);

    setLayout(mvlayout);
}
