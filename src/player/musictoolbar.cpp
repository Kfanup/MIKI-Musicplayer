#include "musictoolbar.h"
#include <QHBoxLayout>
#include <QtGlobal>

MusicToolBar::MusicToolBar(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("color:white");
    toolBar = new QToolBar;
    playModeBtn = new QToolButton;
    previousBtn = new QToolButton;
    pauseBtn = new QToolButton;
    pauseBtn->setFixedSize(40, 40);
    nextBtn = new QToolButton;

    addSong = new QAction("添加音乐", this);
    addSongDir = new QAction("添加音乐文件", this);
    toolBar->addAction(addSong);
    toolBar->addAction(addSongDir);

#ifdef Q_OS_WIN
    pauseBtn->setIcon(QIcon(":/new/prefix1/res/music_logo.ico"));
    previousBtn->setIcon(QIcon(":/new/prefix1/res/previous.ico"));
    playModeBtn->setIcon(QIcon(":/new/prefix1/res/random.ico"));
    //    toolBar->setIcon(QIcon(":/new/prefix1/res/setting.ico"));
    nextBtn->setIcon(QIcon(":/new/prefix1/res/next.ico"));
#else
    pauseBtn->setIcon(QIcon(":/new/prefix1/res/pause.png"));
    previousBtn->setIcon(QIcon(":/new/prefix1/res/previous.png"));
    playModeBtn->setIcon(QIcon(":/new/prefix1/res/order.png"));
    //    toolBar->setIcon(QIcon(":/new/prefix1/res/setting.png"));
    nextBtn->setIcon(QIcon(":/new/prefix1/res/next.png"));
#endif

    QSlider *volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setFixedSize(100, 12);
    volumeSlider->setMaximum(100);
    volumeSlider->setMinimum(0);
    volumeSlider->setValue(30);

    QHBoxLayout *mainlayout = new QHBoxLayout;
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->addWidget(toolBar);
    mainlayout->setSpacing(15);
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

// inline void MusicToolBar::onAddSongClicked()
//{
//    emit addSongClicked();
//}

// inline void MusicToolBar::onAddSongDirClicked()
//{
//    emit addSongDirClicked();
//}

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
