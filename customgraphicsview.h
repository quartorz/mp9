#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>

class QGraphicsScene;
class QGraphicsVideoItem;

class CustomGraphicsView : public QGraphicsView
{
public:
    CustomGraphicsView(QWidget *parent = nullptr);

    QGraphicsVideoItem *getVideoItem() const;

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

public slots:
    void setOverlayTime(bool);
    void setCursorOnTimeSlider(bool);
    void setVideoLength(qint64);
    void setVideoPosition(qint64);
    void setNotifiedPosition(qint64);

private:
    QGraphicsScene *m_scene;
    QGraphicsVideoItem *m_videoItem;

    bool m_bOverlayTime;
    bool m_bCursorOnTimeSlider;
    qint64 m_videoLength;
    qint64 m_videoPosition;
    qint64 m_notifiedPosition;
};

#endif // CUSTOMGRAPHICSVIEW_H
