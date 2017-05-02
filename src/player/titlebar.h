#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class TitleBar : public QWidget {
    Q_OBJECT
public:
    explicit TitleBar(QWidget* parent = 0);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual bool eventFilter(QObject* obj, QEvent* event);

private
slots:
    void onClicked();

private:
    void updateMaximumsize();

private:
    QLabel* pIconLabel;
    QLabel* pTitleLabel;
    QPushButton* pMinimumBtn;
    QPushButton* pMaximumBtn;
    QPushButton* pCloseBtn;
};

#endif // TITLEBAR_H
