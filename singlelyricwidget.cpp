#include "singlelyricwidget.h"
#include "ui_singlelyricwidget.h"
#include "singlelyricframe.h"

#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>

SingleLyricWidget::SingleLyricWidget(QWidget *parent)
    : BaseWidget(parent)
    , ui(new Ui::LyricWidget)
{
    setWindowFlags(this->windowFlags()
                   | Qt::Tool
                   | Qt::WindowStaysOnTopHint);

    ui->setupUi(this);
    ui->btnClose->setVisible(false);
    ui->btnPrevios->setVisible(false);
    ui->btnPlay->setVisible(false);
    ui->btnNext->setVisible(false);
    if (PLAYER->isPlaying()) {
        QIcon icon;
        icon.addFile(":/icons/images/pause_lyric.png");
        ui->btnPlay->setIcon(icon);
        ui->btnPlay->setToolTip("暂停");
    }

    connect(ui->frameLyric, &SingleLyricFrame::btnVisable
            , this, &SingleLyricWidget::do_btnVisable);
    connect(PLAYER->mediaPlayer(), &QMediaPlayer::playbackStateChanged,
            this, &SingleLyricWidget::do_playbackStateChanged);
    connect(ui->btnPrevios, &QPushButton::clicked,
            PLAYER, &Player::previous);
    connect(ui->btnNext, &QPushButton::clicked,
            PLAYER, &Player::next);
}

SingleLyricWidget::~SingleLyricWidget()
{
    delete ui;
}

void SingleLyricWidget::setLyricText(const QString &text)
{
    ui->labelLyric->setText(text);
}

void SingleLyricWidget::do_btnVisable(bool visible)
{
    ui->btnClose->setVisible(visible);
    ui->btnPrevios->setVisible(visible);
    ui->btnPlay->setVisible(visible);
    ui->btnNext->setVisible(visible);
}

void SingleLyricWidget::on_btnClose_clicked()
{
    this->close();
    emit widgetClosed();
}

void SingleLyricWidget::on_btnPlay_clicked()
{
    if (PLAYER->isPlaying()) {
        PLAYER->pause();
    } else {
        PLAYER->play();
    }
}

void SingleLyricWidget::do_playbackStateChanged(QMediaPlayer::PlaybackState state)
{
    QIcon icon;
    if (state == QMediaPlayer::PlayingState) {
        icon.addFile(":/icons/images/pause_lyric.png");
        ui->btnPlay->setIcon(icon);
        ui->btnPlay->setToolTip("暂停");
    } else {
        icon.addFile(":/icons/images/play_lyric.png");
        ui->btnPlay->setIcon(icon);
        ui->btnPlay->setToolTip("播放");
    }
}
