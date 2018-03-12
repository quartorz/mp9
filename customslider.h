#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QSlider>

class QMouseEvent;

class CustomSlider : public QSlider
{
    Q_OBJECT

public:
    CustomSlider(QWidget *parent = nullptr);

    void leaveEvent(QEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

signals:
    void mouseLeft();
    void notifyMouseMove(int value);
    void barClicked();

private:
    int valueByPoint(const QPoint &);
};

#endif // CUSTOMSLIDER_H
