#include "playlistwidget.h"
#include "categorylistwidget.h"
#include "songtable/songtablemodel.h"

PlayListWidget* PlayListWidget::m_instance = nullptr;

PlayListWidget::PlayListWidget(QWidget *parent)
    : QListWidget(parent)
{
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setMinimumSize(180, 165);
    this->setMaximumSize(180, 165);
    this->setCursor(Qt::PointingHandCursor);
    this->setFocusPolicy(Qt::NoFocus);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setStyleSheet(
        "QListWidget {"
        "background-color:  rgb(240,240,240);"
        "border: none;"
        "font-family: Microsoft YaHei;"
        "font-size: 10pt;"
        "font-weight: normal;"
        "color: rgb(80,80,80);"
        "}"
        "QListWidget::item {"
        " height: 40px;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: rgb(221,221,221);"
        "    color: #000000;"
        "}"
        "QListWidget::item:selected {"
        "    background-color: rgb(221,221,221);"
        "    color: #000000;"
        "}"
        );
    this->setIconSize(QSize(20, 20));

    // 设置"喜欢","播放队列","最近播放","本地和下载"
    QStringList categoryStringList{"喜欢", "播放队列", "最近播放", "本地和下载"};
    QStringList iconPathList{m_pathUnlikeIcon, m_pathPlaylist, m_pathHistory, m_pathLocalDownload};
    for (int i = 0; i < 4; ++i) {
        QListWidgetItem *item = new QListWidgetItem(categoryStringList[i]);
        item->setIcon(QIcon(iconPathList[i]));
        this->addItem(item);
    }

    connect(this, &QListWidget::currentRowChanged,
            this, &PlayListWidget::do_currentRowChanged);
}

PlayListWidget* PlayListWidget::instance(QWidget *parent)
{
    if (!m_instance) {
        m_instance = new PlayListWidget(parent);
    }
    return m_instance;
}

void PlayListWidget::do_currentRowChanged(int row)
{
    emit exitBatchProcess();

    if (row == -1) {
        return;
    }

    if (CATEGORY_LISTWIDGET->selectionModel()->hasSelection()) {
        CATEGORY_LISTWIDGET->m_currentRow = -1;
        CATEGORY_LISTWIDGET->clearSelection();
    }

    switch (row) {
    case 0 :{
        SONG_TABLEMODEL->updateTable("喜欢", PlaylistKind::Favorite);
        emit listSelected("喜欢");
        break;
    }
    case 1:{
        SONG_TABLEMODEL->updateTable("播放队列", PlaylistKind::PlayQueue);
        emit listSelected("播放队列");
        break;
    }
    case 2: {
        SONG_TABLEMODEL->updateTable("最近播放", PlaylistKind::History);
        emit listSelected("最近播放");
        break;
    }
    default: {
        SONG_TABLEMODEL->updateTable("本地和下载", PlaylistKind::LocalAndDownload);
        emit listSelected("本地和下载");
        break;
    }
    }
}
