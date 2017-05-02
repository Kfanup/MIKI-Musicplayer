#include "musictoolbar.h"
#include <QHBoxLayout>

MusicToolBar::MusicToolBar(QWidget* parent)
    : QWidget(parent)
{
    setStyleSheet("color:white");
    orderBtn = new QToolButton;
    orderBtn->setIcon(QIcon(":/new/prefix1/res/order.png"));
    randomBtn = new QToolButton;
    randomBtn->setIcon(QIcon(":/new/prefix1/res/random.png"));
    previousBtn = new QToolButton;
    previousBtn->setIcon(QIcon(":/new/prefix1/res/previous.png"));
    pauseBtn = new QToolButton;
    pauseBtn->setIcon(QIcon(":/new/prefix1/res/pause.png"));
    pauseBtn->setFixedSize(40,40);
    nextBtn = new QToolButton;
    nextBtn->setIcon(QIcon(":/new/prefix1/res/next.png"));

    QSlider* volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setFixedSize(100,12);
    volumeSlider->setMaximum(100);
    volumeSlider->setMinimum(0);
    volumeSlider->setValue(30);

    QHBoxLayout *mainlayout=new QHBoxLayout;
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->addWidget(orderBtn);
    mainlayout->setSpacing(15);
    mainlayout->addWidget(randomBtn);
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

void MusicToolBar::onOrderBtnClicked()
{
    emit orderBtnClicked();
}

void MusicToolBar::onRandomBtnClicked()
{
    emit randoBtnClicked();
}

void MusicToolBar::onPreviousBtnClicked()
{
    emit previousBtnClicked();
}

void MusicToolBar::onPauseBtnClicked()
{
    emit pauseBtnClicked();
}

void MusicToolBar::onNextBtnClicked()
{
    emit nextBtnClicked();
}

