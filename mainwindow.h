#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class QMediaPlayer;
class QVideoWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *);
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void mouseMoveEvent(QMouseEvent *);

public slots:

    void open(const QUrl &url);

private:
    Ui::MainWindow *ui;

    QMediaPlayer *m_mediaPlayer;
    qint64 m_maxTime;

    bool m_bOverlayTimeOnVideo;
};

#endif // MAINWINDOW_H
