#ifndef MUSICTOOLBAR_H
#define MUSICTOOLBAR_H

#include <QWidget>
#include <QSlider>
#include <QToolButton>
#include "mplayer.h"

class MusicToolBar : public QWidget {
    Q_OBJECT
public:
    explicit MusicToolBar(QWidget* parent = 0);
    static QSlider* volumeSlider;

signals:
    void orderBtnClicked();
    void randoBtnClicked();
    void previousBtnClicked();
    void pauseBtnClicked();
    void nextBtnClicked();

public
slots:
    void onOrderBtnClicked();
    void onRandomBtnClicked();
    void onPreviousBtnClicked();
    void onPauseBtnClicked();
    void onNextBtnClicked();

private:
    QToolButton* orderBtn;
    QToolButton* randomBtn;
    QToolButton* previousBtn;
    QToolButton* pauseBtn;
    QToolButton* nextBtn;

};


#endif // MUSICTOOLBAR_H
