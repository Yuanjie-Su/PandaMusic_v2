#ifndef VOLUMECONTROLWIDGET_H
#define VOLUMECONTROLWIDGET_H

#include <QWidget>
#include <QEvent>

namespace Ui {
class VolumeControlWidget;
}

class VolumeControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeControlWidget(QWidget *parent = nullptr, int volume = 50, bool muted = false);
    ~VolumeControlWidget();

signals:
    void volumeChanged(float volume);
    void mutedChanged(bool muted);
    void widgetClosed(); // 自定义关闭信号

private slots:
    void on_verticalSliderVolume_valueChanged(int value);
    void on_btnVolume_clicked();


private:
    Ui::VolumeControlWidget *ui;
    bool muted;
};

#endif // VOLUMECONTROLWIDGET_H
