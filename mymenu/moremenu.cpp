#include "moremenu.h"
#include "addtomenu.h"
#include "player/player.h"
#include "database/database.h"

#include <QMessageBox>
#include <QApplication>
#include <QClipboard>

MoreMenu::MoreMenu(QWidget *parent, int songId, int favorite)
    : BaseMenu(parent)
{
    this->setFixedWidth(200);
    bool visible = songId != -1;
    // 播放
    QAction *action = new QAction("播放");
    action->setIcon(QIcon(":/icons/images/play_one.png"));
    this->addAction(action);
    if (visible) {
        connect(action, &QAction::triggered, this, [songId](){
            PLAYER->play(songId);
        });
    } else {
        action->setEnabled(false);
    }

    // 下一首播放
    action = new QAction("下一首播放");
    action->setIcon(QIcon(":/icons/images/play_next.png"));
    this->addAction(action);
    if (visible) {
        connect(action, &QAction::triggered, this, [songId](){
            PLAYER->playNext(songId);
        });
    } else {
        action->setEnabled(false);
    }

    // 播放相似单曲
    action = new QAction("播放相似单曲");
    action->setIcon(QIcon(":/icons/images/play_similar.png"));
    this->addAction(action);
    action->setEnabled(false);

    // 播放MV
    action = new QAction("播放MV");
    action->setIcon(QIcon(":/icons/images/play_mv.png"));
    this->addAction(action);
    action->setEnabled(false);

    // 我喜欢
    this->addSeparator();
    action = new QAction("我喜欢");
    if (favorite)
        action->setIcon(QIcon(":/icons/images/like.png"));
    else
        action->setIcon(QIcon(":/icons/images/unlike.png"));
    this->addAction(action);
    if (visible) {
        connect(action, &QAction::triggered, this, [favorite, songId](){
            // SONG_TABLEWIDGET->changeFavorite(1 - favorite, songId);
        });
    } else {
        action->setEnabled(false);
    }

    // 添加到
    AddToMenu *addToMenu = new AddToMenu(this, songId);
    // 子菜单标题
    addToMenu->setTitle("添加到");
    addToMenu->setIcon(QIcon(":/icons/images/add_to_new.png"));
    this->addMenu(addToMenu);
    if (!visible) {
        addToMenu->setEnabled(false);
    }

    // 下载
    action = new QAction("下载");
    action->setIcon(QIcon(":/icons/images/download.png"));
    this->addAction(action);
    action->setEnabled(false);

    // 分享
    action = new QAction("分享");
    action->setIcon(QIcon(":/icons/images/share.png"));
    this->addAction(action);
    action->setEnabled(false);

    // 复制歌曲信息
    action = new QAction("复制歌曲信息");
    action->setIcon(QIcon(":/icons/images/copy.png"));
    this->addAction(action);
    if (visible) {
        connect(action, &QAction::triggered, this, [songId](){
            QVariantMap songDetails = DB->getSongDetails(songId);
            QString info = QString("歌曲: %1\n歌手: %2\n专辑: %3\n时长: %4")
                               .arg(songDetails["title"].toString())
                               .arg(songDetails["artist"].toString())
                               .arg(songDetails["album"].toString());
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(info);
        });
    } else {
        action->setEnabled(false);
    }

    // 删除
    this->addSeparator();
    action = new QAction("删除");
    action->setIcon(QIcon(":/icons/images/trash.png"));
    this->addAction(action);
    if (visible) {
        connect(action, &QAction::triggered, this, [songId](){
            int ret = QMessageBox::question(nullptr, "删除歌曲", "确定删除该歌曲吗？");
            if (ret == QMessageBox::Yes) {
                // SONG_TABLEWIDGET->removeSong(songId);
            }
        });
    } else {
        action->setEnabled(false);
    }
}
