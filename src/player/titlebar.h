#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0);

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
    QPoint mPoint;
    QLabel *pIconLabel;
    QLabel *pTitleLabel;
    QPushButton *pMinimumBtn;
    QPushButton *pMaximumBtn;
    QPushButton *pCloseBtn;
};

#endif // TITLEBAR_H
