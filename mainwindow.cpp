#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QGraphicsVideoItem>

#include "utility.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_mediaPlayer(new QMediaPlayer(this)),
    m_maxTime(0),
    m_bOverlayTimeOnVideo(false)
{
    ui->setupUi(this);

    m_mediaPlayer->setVideoOutput(ui->graphicsView->getVideoItem());

    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, [&](qint64 v){
        m_maxTime = v;

        ui->timeSlider->setMaximum(static_cast<int>(v));
        ui->graphicsView->setVideoLength(v);
    });
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, [&](qint64 v){
        ui->timeSlider->setValue(static_cast<int>(v));

        ui->currentTime->setText(
                    QString("%1/%2").arg(formatTime(v)).arg(formatTime(m_maxTime)));

        ui->graphicsView->setVideoPosition(v);
    });
    connect(ui->timeSlider, &QSlider::sliderMoved, m_mediaPlayer, &QMediaPlayer::setPosition);
    connect(ui->volumeSlider, &QSlider::valueChanged, m_mediaPlayer, &QMediaPlayer::setVolume);
    connect(ui->timeSlider, &CustomSlider::notifyMouseMove, [&](int v){
        ui->notifiedTime->setText(
                    QString("(%1)").arg(formatTime(v)));
        ui->graphicsView->setNotifiedPosition(v);
        ui->graphicsView->setCursorOnTimeSlider(true);
    });
    connect(ui->timeSlider, &CustomSlider::mouseLeft, [&](){
        ui->notifiedTime->setText("");
        ui->graphicsView->setCursorOnTimeSlider(false);
    });
    connect(ui->timeSlider, &CustomSlider::barClicked, [&](){
        m_mediaPlayer->setPosition(ui->timeSlider->value());
    });

    ui->volumeSlider->setValue(m_mediaPlayer->volume());

    setFocus();
    setAcceptDrops(true);

    menuBar()->hide();
    ui->labelContainer->hide();
    ui->sliderContainer->hide();

    centralWidget()->setMouseTracking(true);
    centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_mediaPlayer;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Space:
        if(m_mediaPlayer->state() == QMediaPlayer::PlayingState){
            m_mediaPlayer->pause();
        }else{
            m_mediaPlayer->play();
        }
        break;
    case Qt::Key_Left:
        if((event->modifiers() & Qt::AltModifier) && (event->modifiers() & Qt::ControlModifier)){
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos - 10 * 60 * 1000);
        }
        else if(event->modifiers() & Qt::AltModifier){
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos - 1 * 60 * 1000);
        }
        else if(event->modifiers() & Qt::ControlModifier){
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos - 30 * 1000);
        }
        else{
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos - 5 * 1000);
        }
        event->accept();
        break;
    case Qt::Key_Right:
        if((event->modifiers() & Qt::AltModifier) && (event->modifiers() & Qt::ControlModifier)){
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos + 10 * 60 * 1000);
        }
        else if(event->modifiers() & Qt::AltModifier){
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos + 1 * 60 * 1000);
        }
        else if(event->modifiers() & Qt::ControlModifier){
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos + 30 * 1000);
        }
        else{
            auto pos = m_mediaPlayer->position();
            m_mediaPlayer->setPosition(pos + 5 * 1000);
        }
        event->accept();
        break;
    case Qt::Key_F11:
        if(isFullScreen()){
            showNormal();
        }else{
            showFullScreen();
        }
    case Qt::Key_O:
        m_bOverlayTimeOnVideo = !m_bOverlayTimeOnVideo;
        ui->graphicsView->setOverlayTime(m_bOverlayTimeOnVideo);
        if(m_bOverlayTimeOnVideo){
            ui->labelContainer->hide();
        }else if(!ui->sliderContainer->isHidden()){
            ui->labelContainer->show();
        }
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    auto url = event->mimeData()->urls().first();
    open(url);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
#if !defined(Q_OS_MAC)
    if(event->y() < 30){
        menuBar()->show();
    }else{
        menuBar()->hide();
    }
#endif
    
    if(event->y() > height() - 70){
        if(!m_bOverlayTimeOnVideo){
            ui->labelContainer->show();
        }
        ui->sliderContainer->show();
    }else{
        ui->labelContainer->hide();
        ui->sliderContainer->hide();
    }

    event->accept();

    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::open(const QUrl &url)
{
    m_mediaPlayer->setMedia(url);
    setWindowTitle(url.fileName() + " - mp9");
}
