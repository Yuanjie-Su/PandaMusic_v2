#include "playmodecontrolwidget.h"
#include "ui_playmodecontrolwidget.h"


#include <QGraphicsEffect>
#include <QListWidgetItem>
#include <QIcon>

PlayModeControlWidget::PlayModeControlWidget(QWidget *parent,
                                             Player::PlayBackMode playBackMode)
    : QWidget(parent)
    , ui(new Ui::PlayModeControlWidget)
    , m_playBackMode(playBackMode)
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

    // 设置列表
    QListWidgetItem * item;
    QIcon icon;

    item = new QListWidgetItem(" 顺序播放");
    icon.addFile(":/icons/images/sequential.png");
    item->setIcon(icon);
    ui->listWidget->addItem(item);

    item = new QListWidgetItem(" 列表循环");
    icon.addFile(":/icons/images/loopSequential.png");
    item->setIcon(icon);
    ui->listWidget->addItem(item);

    item = new QListWidgetItem(" 单曲循环");
    icon.addFile(":/icons/images/loopSingle.png");
    item->setIcon(icon);
    ui->listWidget->addItem(item);

    item = new QListWidgetItem(" 随机播放");
    icon.addFile(":/icons/images/random.png");
    item->setIcon(icon);
    ui->listWidget->addItem(item);

    ui->listWidget->setSpacing(3);
    ui->listWidget->setStyleSheet("QListWidget::item { height: 30px; }");
    ui->listWidget->setIconSize(QSize(20, 20));
    ui->listWidget->setFocusPolicy(Qt::NoFocus);
    ui->listWidget->setStyleSheet("QListWidget::item:hover { background-color: transparent; }");
}


PlayModeControlWidget::~PlayModeControlWidget()
{
    delete ui;
}


void PlayModeControlWidget::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int row = ui->listWidget->row(item);
    if (row >= Player::Sequential && row <= Player::Random) {
        Player::PlayBackMode newPlayBackMode = static_cast<Player::PlayBackMode>(row);
        if (newPlayBackMode != m_playBackMode)
            emit playBackModeChanged(newPlayBackMode);
    }
    this->close();
}
