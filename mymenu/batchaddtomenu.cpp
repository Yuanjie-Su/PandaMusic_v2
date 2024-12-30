#include "batchaddtomenu.h"
#include "player/player.h"
#include "categorylistwidget.h"
#include "database/database.h"

BatchAddToMenu::BatchAddToMenu(QWidget *parent, QVector<int> songIdVector, const QString &sourceCategoryName, PlaylistKind listKind)
{
    if (songIdVector.isEmpty())
        return;

    this->setFixedWidth(244);
    // 播放队列
    QAction *action = new QAction("播放队列", this);
    this->addAction(action);
    if (listKind == PlaylistKind::PlayQueue) {
        action->setEnabled(false);
    } else {
        connect(action, &QAction::triggered, this, [songIdVector](){
            PLAYER->addSong(songIdVector);
        });
    }

    // 添加到新歌单
    this->addSeparator();
    action = new QAction("添加到新歌单", this);
    action->setIcon(QIcon(":/icons/images/add_to_new.png"));
    this->addAction(action);
    connect(action, &QAction::triggered, this, [songIdVector](){
        CATEGORY_ListWIDGET->createNewCategoryName(songIdVector);
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
            if (listKind == PlaylistKind::Custom && categoryName == sourceCategoryName) {
                action->setEnabled(false);
            } else {
                connect(action, &QAction::triggered,
                        this, [categoryName, songIdVector](){
                            DB->insertSongIntoCategory(categoryName, songIdVector);
                        });
            }
        }
    }
}
