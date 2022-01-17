#pragma once

#include <QLabel>
#include <QMouseEvent>

class ImageDisplay : public QLabel
{
    Q_OBJECT
public:
    ImageDisplay(QWidget *parent=nullptr);

    void mouseMoveEvent(QMouseEvent *ev);

signals:
    void mouseMoved(const QPoint& mousePos);
};
