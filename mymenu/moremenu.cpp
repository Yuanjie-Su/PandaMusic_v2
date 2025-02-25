#include "moremenu.h"
#include "addtomenu.h"
#include "player/player.h"
#include "database/database.h"
#include "songtable/songtablemodel.h"
#include "utils/constants.h"

#include <QMessageBox>
#include <QApplication>
#include <QClipboard>

MoreMenu::MoreMenu(QWidget *parent
                   , int songId
                   , int favorite
                   , PlaylistKind listKind
                   , const QString &categoryName)
    : BaseMenu(parent)
{
    this->setFixedWidth(200);
    bool visible = songId != -1;
    // 播放
    QAction *action = new QAction("播放");
    action->setIcon(QIcon(Paths::PlayOneIcon));
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
    action->setIcon(QIcon(Paths::PlayNextIcon));
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
    action->setIcon(QIcon(Paths::PlaySimilarIcon));
    this->addAction(action);
    action->setEnabled(false);

    // 播放MV
    action = new QAction("播放MV");
    action->setIcon(QIcon(Paths::PlayMvIcon));
    this->addAction(action);
    action->setEnabled(false);

    // 我喜欢
    this->addSeparator();
    action = new QAction("我喜欢");
    if (favorite)
        action->setIcon(QIcon(Paths::LikeIcon));
    else
        action->setIcon(QIcon(Paths::UnlikeIcon));
    this->addAction(action);
    if (visible) {
        connect(action, &QAction::triggered, this, [favorite, songId](){
            SONG_TABLEMODEL->changeFavorite(favorite ? 0 : 1, songId);
        });
    } else {
        action->setEnabled(false);
    }

    // 添加到
    AddToMenu *addToMenu = new AddToMenu(this, songId);
    // 子菜单标题
    addToMenu->setTitle("添加到");
    addToMenu->setIcon(QIcon(Paths::AddToNewIcon));
    this->addMenu(addToMenu);
    if (!visible) {
        addToMenu->setEnabled(false);
    }

    // 下载
    action = new QAction("下载");
    action->setIcon(QIcon(Paths::DownloadIcon));
    this->addAction(action);
    action->setEnabled(false);

    // 分享
    action = new QAction("分享");
    action->setIcon(QIcon(Paths::ShareIcon));
    this->addAction(action);
    action->setEnabled(false);

    // 复制歌曲信息
    action = new QAction("复制歌曲信息");
    action->setIcon(QIcon(Paths::CopyIcon));
    this->addAction(action);
    if (visible) {
        connect(action, &QAction::triggered, this, [songId](){
            QVariantMap songDetails = DB->getSongDetails(songId);
            QString info = "歌曲: " + songDetails["title"].toString() + "\n" +
                           "歌手: " + songDetails["artist"].toString() + "\n" +
                           "专辑: " + songDetails["album"].toString() + "\n";
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(info);
        });
    } else {
        action->setEnabled(false);
    }

    // 删除
    this->addSeparator();
    action = new QAction("删除");
    action->setIcon(QIcon(Paths::DeleteIcon));
    this->addAction(action);
    if (visible) {
        connect(action, &QAction::triggered, this, [songId, listKind, categoryName](){
            int ret = QMessageBox::question(nullptr, "删除歌曲", "确定删除该歌曲吗？");
            if (ret == QMessageBox::Yes) {
                SONG_TABLEMODEL->removeSong(songId, listKind, categoryName);
            }
        });
    } else {
        action->setEnabled(false);
    }
}
