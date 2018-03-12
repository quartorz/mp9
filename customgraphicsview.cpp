#include "customgraphicsview.h"

#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QResizeEvent>

#include "utility.h"

CustomGraphicsView::CustomGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_videoItem(new QGraphicsVideoItem()),
    m_bOverlayTime(false),
    m_bCursorOnTimeSlider(false),
    m_videoLength(0),
    m_videoPosition(0),
    m_notifiedPosition(0)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);

    setScene(m_scene);
    m_scene->addItem(m_videoItem);
    m_videoItem->setOffset(QPointF(0.0f, 0.0f));
    m_videoItem->setSize(size());
    m_videoItem->setAspectRatioMode(Qt::KeepAspectRatio);
}

QGraphicsVideoItem *CustomGraphicsView::getVideoItem() const
{
    return m_videoItem;
}

void CustomGraphicsView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    QPainter painter(this->viewport());

    if(m_bOverlayTime){
        QString text;

        if(m_bCursorOnTimeSlider){
            text = QString("%1/%2(%3)")
                    .arg(formatTime(m_videoPosition))
                    .arg(formatTime(m_videoLength))
                    .arg(formatTime(m_notifiedPosition));
        }else{
            text = QString("%1/%2")
                    .arg(formatTime(m_videoPosition))
                    .arg(formatTime(m_videoLength));
        }

        QRect rect(0, height() - painter.fontMetrics().ascent(),
                   painter.fontMetrics().width(text),
                   painter.fontMetrics().ascent());

        painter.fillRect(rect, QColor(255, 255, 255, 80));

        painter.setPen(QColor(0, 0, 0, 128));
        painter.drawText(rect, text);
    }
}

void CustomGraphicsView::resizeEvent(QResizeEvent *event)
{
    m_videoItem->setSize(event->size());
}

void CustomGraphicsView::setOverlayTime(bool overlay)
{
    m_bOverlayTime = overlay;
    m_scene->update();
}

void CustomGraphicsView::setCursorOnTimeSlider(bool v)
{
    m_bCursorOnTimeSlider = v;
    m_scene->update();
}

void CustomGraphicsView::setVideoLength(qint64 length)
{
    m_videoLength = length;
    if(m_bOverlayTime){
        m_scene->update();
    }
}

void CustomGraphicsView::setVideoPosition(qint64 position)
{
    m_videoPosition = position;
    if(m_bOverlayTime){
        m_scene->update();
    }
}

void CustomGraphicsView::setNotifiedPosition(qint64 position)
{
    m_notifiedPosition = position;
    if(m_bOverlayTime){
        m_scene->update();
    }
}
