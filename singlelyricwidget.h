#ifndef SINGLELYRICWIDGET_H
#define SINGLELYRICWIDGET_H

#include "player/player.h"
#include "basewidget.h"

namespace Ui {
class LyricWidget;
}

class SingleLyricWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit SingleLyricWidget(QWidget *parent = nullptr);
    ~SingleLyricWidget();
    void setLyricText(const QString &text);

public slots:
    void do_playbackStateChanged(QMediaPlayer::PlaybackState state);

signals:
    void widgetClosed();

private slots:
    void do_btnVisable(bool visible);
    void on_btnClose_clicked();
    void on_btnPlay_clicked();

private:
    Ui::LyricWidget *ui;
};

#endif // SINGLELYRICWIDGET_H
