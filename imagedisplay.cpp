#include "imagedisplay.h"


ImageDisplay::ImageDisplay(QWidget *parent):QLabel(parent)
{
    this->setAttribute(Qt::WA_Hover, true);
    this->setMouseTracking(true);
}

void ImageDisplay::mouseMoveEvent(QMouseEvent *ev) {
    mouseMoved(ev->pos());
}
