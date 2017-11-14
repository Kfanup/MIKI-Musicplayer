#pragma once

#include <QWidget>
#include <QLabel>
#include <QPoint>
#include "mplayer.h"
#include <QMouseEvent>
#include <QPushButton>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0);

signals:
    void addMedia();
    void addMediaDir();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual bool eventFilter(QObject *obj, QEvent *event);
    void onClicked();

private:
    void updateMaximumsize();

private:
    bool mMoveing = false;
    QPoint ptPress;
    QPoint ptMove;
    QLabel *pIconLabel;
    QLabel *pTitleLabel;
    QPushButton *pMenuBtn;
    QPushButton *pMinimumBtn;
    QPushButton *pMaximumBtn;
    QPushButton *pCloseBtn;
};
