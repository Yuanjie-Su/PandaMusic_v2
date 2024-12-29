#ifndef PLAYMODECONTROLWIDGET_H
#define PLAYMODECONTROLWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include "player/player.h"

namespace Ui {
class PlayModeControlWidget;
}

class PlayModeControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayModeControlWidget(QWidget *parent = nullptr,
                                   Player::PlayBackMode playBackMode = Player::Sequential);
    ~PlayModeControlWidget();

signals:
    void playBackModeChanged(Player::PlayBackMode playBackMode);

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::PlayModeControlWidget *ui;
    Player::PlayBackMode m_playBackMode;
};

#endif // PLAYMODECONTROLWIDGET_H
