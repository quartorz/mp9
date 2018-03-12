#include "customslider.h"

#include <QMouseEvent>

CustomSlider::CustomSlider(QWidget *parent) :
    QSlider(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void CustomSlider::leaveEvent(QEvent *event)
{
    emit mouseLeft();
    QSlider::enterEvent(event);
}

void CustomSlider::mouseMoveEvent(QMouseEvent *event)
{
    emit notifyMouseMove(valueByPoint(event->pos()));
    QSlider::mouseMoveEvent(event);
}

void CustomSlider::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        setValue(valueByPoint(event->pos()));
        emit barClicked();
        event->accept();
    }

    QSlider::mousePressEvent(event);
}

int CustomSlider::valueByPoint(const QPoint &p)
{
    if(orientation() == Qt::Vertical){
        return minimum() + qint64(maximum() - minimum()) * (height() - p.y()) / height();
    }else{
        return minimum() + qint64(maximum() - minimum()) * p.x() / width();
    }
}
