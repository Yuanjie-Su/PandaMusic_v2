#include "addtomenu.h"
#include "player/player.h"
#include "database/database.h"
#include "categorylistwidget.h"

#include <QFontMetrics>


AddToMenu::AddToMenu(QWidget *parent, int songId)
    : BaseMenu(parent)
{
    if (songId == -1)
        return;

    this->setFixedWidth(244);
    // 播放队列
    QAction *action = new QAction("播放队列", this);
    this->addAction(action);
    if (PLAYER->isInPlaylist(songId)) {
        action->setEnabled(false);
    } else {
        connect(action, &QAction::triggered, this, [songId](){
            PLAYER->addSong(songId);
        });
    }

    // 添加到新歌单
    this->addSeparator();
    action = new QAction("添加到新歌单", this);
    action->setIcon(QIcon(":/icons/images/add_to_new.png"));
    this->addAction(action);
    connect(action, &QAction::triggered, this, [songId](){
        CATEGORY_ListWIDGET->createNewCategoryName(songId);
    });
    this->addSeparator();

    // 自建歌单列表
    QList<QString> categoryList = DB->selectNameFromCategory();
    if (!categoryList.isEmpty()) {
        QFontMetrics fontMetrics(this->font());
        for (const auto &categoryName : categoryList) {
            action = new QAction(fontMetrics.elidedText(categoryName, Qt::ElideRight, 180), this);
            action->setToolTip(categoryName);
            this->addAction(action);
            if (DB->isSongInCategory(categoryName, songId)) {
                action->setEnabled(false);
            } else {
                connect(action, &QAction::triggered,
                        this, [categoryName, songId](){
                            DB->insertSongIntoCategory(categoryName, songId);
                        });
            }
        }
    }
}
