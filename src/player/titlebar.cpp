#include <QEvent>
#include <QMenu>
#include <QHBoxLayout>
#include <QApplication>
#include "titlebar.h"

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(27);
    setStyleSheet("color:black");

    pIconLabel = new QLabel;
    pTitleLabel = new QLabel;
    pMenuBtn = new QPushButton;
    pMaximumBtn = new QPushButton;
    pMinimumBtn = new QPushButton;
    pCloseBtn = new QPushButton;

    pIconLabel->setFixedSize(28, 28);
    pIconLabel->setScaledContents(true);

    QPixmap pixmap(":/new/prefix1/res/music_logo.png");
    pIconLabel->setPixmap(pixmap);

    pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pTitleLabel->setText("MIKI MUSIC PLAYER");
    pTitleLabel->setStyleSheet("font-size: 16px;font-weight:500;color:black;");

    pMenuBtn->setFixedSize(27, 22);
    pMaximumBtn->setFixedSize(27, 22);
    pMinimumBtn->setFixedSize(27, 22);
    pCloseBtn->setFixedSize(27, 22);

    pTitleLabel->setObjectName("TitleLabel");
    pMaximumBtn->setObjectName("maximumsizeBtn");
    pMinimumBtn->setObjectName("minimumsizeBtn");
    pCloseBtn->setObjectName("closeBtn");

    pMaximumBtn->setToolTip("最小化");
    pMinimumBtn->setToolTip("最大化");
    pCloseBtn->setToolTip("关闭");

    pMenuBtn->setIcon(QIcon(":/new/prefix1/res/setting.png"));
    pMaximumBtn->setIcon(QIcon(":/new/prefix1/res/maximize.png"));
    pMinimumBtn->setIcon(QIcon(":/new/prefix1/res/min.png"));
    pCloseBtn->setIcon(QIcon(":/new/prefix1/res/close.png"));

    QMenu *pMenu = new QMenu(this);
    QAction *addMediaAct = new QAction(QString("添加音乐文件"));
    QAction *addMediaDirAct = new QAction(QString("添加音乐文件夹"));
    pMenu->addAction(addMediaAct);
    pMenu->addAction(addMediaDirAct);
    pMenuBtn->setMenu(pMenu);
    pMenuBtn->setStyleSheet("QPushButton::menu-indicator{image:none;}"); //取消菜单的三角下拉图标

    QHBoxLayout *playout = new QHBoxLayout;
    playout->addWidget(pIconLabel);
    playout->addSpacing(10);
    playout->addWidget(pTitleLabel);
    playout->addWidget(pMenuBtn);
    playout->addWidget(pMinimumBtn);
    playout->addWidget(pMaximumBtn);
    playout->addWidget(pCloseBtn);
    playout->setSpacing(0);
    playout->setContentsMargins(5, 0, 5, 0);

    setLayout(playout);

    connect(addMediaAct, &QAction::triggered, this, &TitleBar::addMedia);
    connect(addMediaDirAct, &QAction::triggered, this, &TitleBar::addMediaDir);
    connect(pMaximumBtn, &QPushButton::clicked, this, &TitleBar::onClicked);
    connect(pMinimumBtn, &QPushButton::clicked, this, &TitleBar::onClicked);
    connect(pCloseBtn, &QPushButton::clicked, this, &TitleBar::onClicked);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit pMaximumBtn->clicked();
}

/***
 ** @brief 鼠标按下事件
 ** @param event
 **/
void TitleBar::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
#ifdef Q_OS_WIN
//    if (ReleaseCapture()) {
//        QWidget *pWindow = this->window();
//        if (pWindow->isTopLevel()) {
//            SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
//        }
//    }
//    event->ignore();
#else
    if (event->button() == Qt::LeftButton) {
        //设置鼠标样式为手势
        setCursor(Qt::OpenHandCursor);

        mMoveing = true;

        ptPress = event->globalPos();
    }
    event->ignore();
#endif
}

/***
 ** @brief 鼠标移动事件
 ** @param event
 **/
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (mMoveing) {
        ptMove = event->globalPos();
        MPlayer *pWidget = qobject_cast<MPlayer *>(parent());
        pWidget->move(pWidget->pos() + ptMove - ptPress);
        ptPress = ptMove;
    }
    event->ignore();
}

/***
 ** @brief 鼠标释放事件
 ** @param event
 **/
void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        //设置鼠标样式为正常
        setCursor(Qt::ArrowCursor);
        if (event->button() == Qt::LeftButton) {
            mMoveing = false;
        }
    }
    event->ignore();
}

/***
 ** @brief 事件过滤器
 ** @param obj
 ** @param event
 ** @return
 **/
bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::WindowTitleChange: {
        QWidget *pwidget = qobject_cast<QWidget *>(obj);
        if (pwidget) {
            pTitleLabel->setText(pwidget->windowTitle());
            return true;
        }
    } break;
    case QEvent::WindowIconChange: {
        QWidget *pwidget = qobject_cast<QWidget *>(obj);
        if (pwidget) {
            QIcon icon = pwidget->windowIcon();
            pIconLabel->setPixmap(icon.pixmap(pIconLabel->size()));
            return true;
        }
    } break;
    case QEvent::WindowStateChange:
        break;
    case QEvent::Resize:
        updateMaximumsize();
        return true;
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

/***
 ** @brief 鼠标点击按钮槽函数
 **/
void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
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

/***
 ** @brief 更新窗口大小
 **/
void TitleBar::updateMaximumsize()
{
    QWidget *window = this->window();
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
