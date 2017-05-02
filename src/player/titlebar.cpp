#include <QEvent>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QApplication>
#include "titlebar.h"

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget* parent)
    : QWidget(parent)
{
    setFixedHeight(27);
    setStyleSheet("color:white");

    pIconLabel = new QLabel;
    pTitleLabel = new QLabel;
    pMaximumBtn = new QPushButton;
    pMinimumBtn = new QPushButton;
    pCloseBtn = new QPushButton;

    pIconLabel->setFixedSize(20, 20);
    pIconLabel->setScaledContents(true);

    QPixmap pixmap(":/new/prefix1/res/music_logo.png");
    pIconLabel->setPixmap(pixmap);

    pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    pMaximumBtn->setFixedSize(27, 22);
    pMinimumBtn->setFixedSize(27, 22);
    pCloseBtn->setFixedSize(27, 22);

    pTitleLabel->setObjectName("TitleLabel");
    pMaximumBtn->setObjectName("maximumsizeBtn");
    pMinimumBtn->setObjectName("minimumsizeBtn");
    pCloseBtn->setObjectName("closeBtn");

    pMaximumBtn->setToolTip("Maximumsize Button");
    pMinimumBtn->setToolTip("Minimumsize Button");
    pCloseBtn->setToolTip("Close Button");

    QHBoxLayout* playout = new QHBoxLayout;
    playout->addWidget(pIconLabel);
    playout->addSpacing(50);
    playout->addWidget(pTitleLabel);
    playout->addWidget(pMinimumBtn);
    playout->addWidget(pMaximumBtn);
    playout->addWidget(pCloseBtn);
    playout->setSpacing(0);
    playout->setContentsMargins(5, 0, 5, 0);

    setLayout(playout);

    connect(pMaximumBtn, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(pMinimumBtn, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(pCloseBtn, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
    Q_UNUSED(event);

    emit pMaximumBtn->clicked();
}

/**


void TitleBar::mousePressEvent(QMouseEvent* event)
{
#ifdef Q_OS_WIN
    if (ReleaseCapture()) {
        QWidget* pWindow = this->window();
        if (pWindow->isTopLevel()) {
            SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
    event->ignore();
#else
#endif
}

**/

bool TitleBar::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type()) {
    case QEvent::WindowTitleChange: {
        QWidget* pwidget = qobject_cast<QWidget*>(obj);
        if (pwidget) {
            pTitleLabel->setText(pwidget->windowTitle());
            return true;
        }
    }
        break;
    case QEvent::WindowIconChange: {
        QWidget* pwidget = qobject_cast<QWidget*>(obj);
        if (pwidget) {
            QIcon icon = pwidget->windowIcon();
            pIconLabel->setPixmap(icon.pixmap(pIconLabel->size()));
            return true;
        }
    }
        break;
    case QEvent::WindowStateChange:break;
    case QEvent::Resize:
        updateMaximumsize();
        return true;
        break;
    default:break;
    }
    return QWidget::eventFilter(obj, event);
}

void TitleBar::onClicked()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    QWidget* pWindow = this->window();
    if (pWindow->isTopLevel()) {
        if (pButton == pMinimumBtn) {
            pWindow->showMinimized();
        } else if (pButton == pMaximumBtn) {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        } else if (pButton == pCloseBtn) {
            pWindow->close();
        }
    }
}

void TitleBar::updateMaximumsize()
{
    QWidget* window = this->window();
    if (window->isTopLevel()) {
        bool bMaximumsize = window->isMaximized();
        if (bMaximumsize) {
            pMaximumBtn->setToolTip("Restore");
            pMaximumBtn->setProperty("maximumsizeProperty", "restore");
        } else {
            pMaximumBtn->setProperty("maximumsizeProperty", "maximumsize");
            pMaximumBtn->setToolTip("Maximumsize");
        }
        pMaximumBtn->setStyle(QApplication::style());
    }
}
