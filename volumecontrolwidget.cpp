#include "volumecontrolwidget.h"
#include "ui_volumecontrolwidget.h"

#include <QGraphicsEffect>

VolumeControlWidget::VolumeControlWidget(QWidget *parent, int volume, bool muted)
    : QWidget(parent)
    , ui(new Ui::VolumeControlWidget)
    , muted(muted)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup | Qt::NoDropShadowWindowHint); // 无边框
    this->setAttribute(Qt::WA_TranslucentBackground); // 透明
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);

    // 窗口设置阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(Qt::gray);
    shadow->setBlurRadius(16);
    ui->frame->setGraphicsEffect(shadow);

    ui->verticalSliderVolume->setValue(volume);
    ui->labelVolume->setText(QString::number(volume) + "%");
    if (muted) {
        ui->btnVolume->setIcon(QIcon(":/icons/images/mute.png"));
    } else {
        ui->btnVolume->setIcon(QIcon(":/icons/images/volume.png"));
    }
}

VolumeControlWidget::~VolumeControlWidget()
{
    delete ui;
}

void VolumeControlWidget::on_verticalSliderVolume_valueChanged(int value)
{
    float volume = value / 100.0;
    emit volumeChanged(volume);
    ui->labelVolume->setText(QString::number(value) + "%");
    if (value) {
        if (muted) {
            emit mutedChanged(false);
            QIcon icon;
            icon.addFile(":/icons/images/volume.png");
            ui->btnVolume->setIcon(icon);
            muted = false;
        }
    } else {
        if (!muted) {
            emit mutedChanged(true);
            QIcon icon;
            icon.addFile(":/icons/images/mute.png");
            ui->btnVolume->setIcon(icon);
            muted = true;
        }
    }
}

void VolumeControlWidget::on_btnVolume_clicked()
{
    if (ui->verticalSliderVolume->value() == 0)
        return;

    if (muted) {
        emit mutedChanged(false);
        ui->btnVolume->setIcon(QIcon(":/icons/images/volume.png"));
        muted = false;
    } else {
        emit mutedChanged(true);
        ui->btnVolume->setIcon(QIcon(":/icons/images/mute.png"));
        muted = true;
    }
}
