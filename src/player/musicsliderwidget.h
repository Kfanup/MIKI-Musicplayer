#ifndef MUSICSLIDERWIDGET_H
#define MUSICSLIDERWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>

class MusicSliderWidget : public QWidget {
    Q_OBJECT
public:
    explicit MusicSliderWidget(QWidget* parent = 0);

signals:

public
slots:

private:
    QSlider* musicSlider;
    QLabel* nowTimeLabel;
    QLabel* allTimeLabel;
};

#endif // MUSICSLIDERWIDGET_H
