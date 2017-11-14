#include "musictoolbar.h"
#include <QHBoxLayout>
#include <QtGlobal>

MusicToolBar::MusicToolBar(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("color:white");
    playModeBtn = new QToolButton;
    previousBtn = new QToolButton;
    pauseBtn = new QToolButton;
    nextBtn = new QToolButton;

    playModeBtn->sizePolicy();
    previousBtn->sizePolicy();
    pauseBtn->sizePolicy();
    nextBtn->sizePolicy();
    pauseBtn->setMinimumSize(40, 40);

#ifdef Q_OS_WIN
    pauseBtn->setIcon(QIcon(":/new/prefix1/res/music_logo.ico"));
    previousBtn->setIcon(QIcon(":/new/prefix1/res/previous.ico"));
    playModeBtn->setIcon(QIcon(":/new/prefix1/res/random.ico"));
    nextBtn->setIcon(QIcon(":/new/prefix1/res/next.ico"));
#else
    pauseBtn->setIcon(QIcon(":/images/res/icon_unix/pause.png"));
    previousBtn->setIcon(QIcon(":/images/res/icon_unix/previous.png"));
    playModeBtn->setIcon(QIcon(":/images/res/icon_unix/order.png"));
    nextBtn->setIcon(QIcon(":/images/res/icon_unix/next.png"));
#endif

    QSlider *volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setFixedSize(100, 12);
    volumeSlider->setMaximum(100);
    volumeSlider->setMinimum(0);
    volumeSlider->setValue(30);

    QHBoxLayout *mainlayout = new QHBoxLayout;
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->addWidget(playModeBtn);
    mainlayout->setSpacing(15);
    mainlayout->addWidget(previousBtn);
    mainlayout->setSpacing(20);
    mainlayout->addWidget(pauseBtn);
    mainlayout->setSpacing(20);
    mainlayout->addWidget(nextBtn);
    mainlayout->setSpacing(20);
    mainlayout->addWidget(volumeSlider);

    setLayout(mainlayout);
}

inline void MusicToolBar::onPlayModeBtnClicked()
{
    emit playModeBtnClicked();
}

inline void MusicToolBar::onPreviousBtnClicked()
{
    emit previousBtnClicked();
}

inline void MusicToolBar::onPauseBtnClicked()
{
    emit pauseBtnClicked();
}

inline void MusicToolBar::onNextBtnClicked()
{
    emit nextBtnClicked();
}
