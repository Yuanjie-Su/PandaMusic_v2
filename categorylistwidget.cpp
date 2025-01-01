#include "categorylistwidget.h"
#include "songtable/songtablemodel.h"
#include "playlistwidget.h"
#include "database/database.h"
#include "utils/imageutils.h"
#include "mymenu/basemenu.h"

#include <QFontMetrics>
#include <QMessageBox>
#include <QMouseEvent>
#include <QFileDialog>

CategoryListWidget *CategoryListWidget::m_instance = nullptr;

CategoryListWidget::CategoryListWidget(QWidget *parent)
    : QListWidget(parent)
{
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    this->setFixedWidth(180);
    this->setCursor(Qt::PointingHandCursor);
    this->setFocusPolicy(Qt::NoFocus);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 字体看能不能在样式表中实现
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
        "QListWidget QScrollBar:vertical {"
        "  border: none;"
        "  background: rgb(240,240,240);"
        "  width: 4px;"
        "  margin: 0px 0px 0px 0px;"
        "}"

        "QListWidget QScrollBar::handle:vertical {"
        "  background: rgb(200, 200, 200);"
        "  min-height: 20px;"
        "  border-radius: 2px;"
        "}"

        "QListWidget QScrollBar::add-line:vertical {"
        "  background: rgb(240,240,240);"
        "  height: 0px;"
        "  subcontrol-position: bottom;"
        "}"

        "QListWidget QScrollBar::sub-line:vertical {"
        "  background: rgb(240,240,240);"
        "  height: 0px;"
        "  subcontrol-position: top;"
        "}"
        );

    this->setIconSize(QSize(32, 32));
    initList();

    connect(this, &QListWidget::itemClicked,
            this, &CategoryListWidget::do_itemClicked);
    connect(this->itemDelegate(), &QAbstractItemDelegate::closeEditor
            , this, &CategoryListWidget::do_ItemEditFinished);
}

CategoryListWidget *CategoryListWidget::instance(QWidget *parent)
{
    if (!m_instance) {
        m_instance = new CategoryListWidget(parent);
    }
    return m_instance;
}

void CategoryListWidget::initList()
{
    QVariantList categoryMapList = DB->selectFromCategory();
    QFontMetrics fontMetrics(QFont("Microsoft YaHei", 10));
    const int availableWidth = m_columnCategoryWidgth - 6;

    this->setUpdatesEnabled(false); // 暂时禁用更新提高性能

    for (const QVariant &categoryData : categoryMapList) {
        QVariantMap categoryMap = categoryData.toMap();
        QString categoryName = categoryMap["name"].toString();
        m_categoryNameSet.insert(categoryName);

        QListWidgetItem *item = new QListWidgetItem();
        item->setToolTip(categoryName);
        item->setText(fontMetrics.elidedText(categoryName, Qt::ElideRight, availableWidth));
        item->setIcon(QIcon(ImageUtils::getRoundedPixmap(categoryMap["cover"].toString())));
        this->addItem(item);
    }

    this->setUpdatesEnabled(true);
}

void CategoryListWidget::createNewCategoryName(int songId)
{
    if (songId != -1) {
        m_tempSongId = songId;
        m_tempCoverPath = DB->getSongCoverPath(songId);
    }
    if (m_tempCoverPath.isEmpty())
        m_tempCoverPath = ":/cover/images/panda-listening-music.jpg";

    m_isNewNameEditing = true;
    m_editRow = 0;
    m_tempCategoryName = getNewCategoryName();

    insertCategory();
}

void CategoryListWidget::createNewCategoryName(const QVector<int> &songIdVector)
{
    if (songIdVector.isEmpty())
        return;

    if (songIdVector.isEmpty()) {
        return;
    }
    m_tempSongIdVector = songIdVector;

    if (m_tempCoverPath.isEmpty())
        m_tempCoverPath = ":/cover/images/panda-listening-music.jpg";

    m_isNewNameEditing = true;
    m_editRow = 0;
    m_tempCategoryName = getNewCategoryName();

    insertCategory();
}

QString CategoryListWidget::currentCategoryName()
{
    QListWidgetItem *item = this->currentItem();
    if (item)
        return item->toolTip();
    return QString();
}

void CategoryListWidget::insertCategory()
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(m_tempCategoryName);
    item->setToolTip(m_tempCategoryName);
    item->setIcon(QIcon(ImageUtils::getRoundedPixmap(m_tempCoverPath)));
    this->insertItem(m_editRow, item);

    item->setFlags(item->flags() | Qt::ItemIsEditable);
    this->editItem(item);
}

QString CategoryListWidget::getNewCategoryName()
{
    QString baseCategoryName = "新建歌单";
    QString newCategoryName;

    int i = 1;
    do {
        newCategoryName = QString("%1%2").arg(baseCategoryName).arg(i);
        ++i;
    } while (m_categoryNameSet.contains(newCategoryName));

    return newCategoryName;
}

void CategoryListWidget::editCategoryName(int row)
{
    QListWidgetItem *item = this->item(row);
    m_editRow = row;
    m_isNewNameEditing = false;
    m_tempSongId = -1;
    m_tempCategoryName = item->toolTip();
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    this->editItem(item);
}

void CategoryListWidget::updateCover(int row, const QString &coverPath)
{
    QListWidgetItem *item = this->item(row);
    item->setIcon(QIcon(ImageUtils::getRoundedPixmap(coverPath)));
}

void CategoryListWidget::updateCover(int row, const QPixmap &cover)
{
    QListWidgetItem *item = this->item(row);
    item->setIcon(QIcon(cover));
}

void CategoryListWidget::do_ItemEditFinished(QWidget *editor, QAbstractItemDelegate::EndEditHint hint)
{
    Q_UNUSED(editor)
    Q_UNUSED(hint)

    // 获取正在编辑的 item
    QListWidgetItem *item = this->item(m_editRow);
    if (!item)
        return;

    QString categoryName = item->text().trimmed();
    // 如果名称为空
    if (categoryName.isEmpty()) {
        if (m_isNewNameEditing) {
            delete this->takeItem(m_editRow);
            m_isNewNameEditing = false;
            m_tempSongId = -1;
        } else {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            QFontMetrics fontMetrics(QFont("Microsoft YaHei", 10));
            item->setText(fontMetrics.elidedText(m_tempCategoryName
                                                 , Qt::ElideRight
                                                 , m_columnCategoryWidgth - 6));
        }
        m_editRow = -1;
        m_tempCategoryName.clear();
        return;
    }

    // 如果名称重复，提示并重新编辑
    if (m_categoryNameSet.contains(categoryName)) {
        if (m_isNewNameEditing) {
            QMessageBox::warning(this, "重复值", "歌单已存在！");
            item->setText(m_tempCategoryName);
            this->editItem(item);
            return;
        } else {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            QFontMetrics fontMetrics(QFont("Microsoft YaHei", 10));
            item->setText(fontMetrics.elidedText(m_tempCategoryName
                                                 , Qt::ElideRight
                                                 , m_columnCategoryWidgth - 6));
            m_editRow = -1;
            m_tempCategoryName.clear();
        }
    } else { // 否则，更新数据库及内部状态
        m_categoryNameSet.insert(categoryName);
        QFontMetrics fontMetrics(QFont("Microsoft YaHei", 10));
        item->setToolTip(categoryName);
        item->setText(fontMetrics.elidedText(categoryName, Qt::ElideRight, m_columnCategoryWidgth - 6));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        DB->insertNameIntoCategory(categoryName, m_tempCoverPath);

        if (m_isNewNameEditing) {
            m_isNewNameEditing = false;
            if (m_tempSongId != -1) {
                DB->insertSongIntoCategory(categoryName, m_tempSongId);
                m_tempSongId = -1;
            }

            if (!m_tempSongIdVector.isEmpty()) {
                for (int songId : m_tempSongIdVector) {
                    DB->insertSongIntoCategory(categoryName, songId);
                }
                m_tempSongIdVector.clear();
            }
        } else {
            m_categoryNameSet.remove(m_tempCategoryName);
            DB->updateCategory(categoryName, m_tempCategoryName);
        }
        m_editRow = -1;
        m_tempCategoryName.clear();
    }
}

void CategoryListWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        // 通过鼠标点击的坐标获取单元格项
        QListWidgetItem *item = itemAt(event->pos());
        if (item) {

            QString categoryName = item->toolTip();
            int row = this->row(item);
            emit exitBatchProcess();

            if (row != m_currentRow) {
                m_currentRow = row;

                if (PLAY_LISTWIDGET->selectionModel()->hasSelection()) {
                    PLAY_LISTWIDGET->setCurrentRow(-1);
                    PLAY_LISTWIDGET->clearSelection();
                }

                emit listSelected(categoryName);
                SONG_TABLEMODEL->setFilter(
                    QString("id IN (SELECT song_id FROM songCategoryRelationship WHERE category_name = '%1')").arg(categoryName)
                    );
                SONG_TABLEMODEL->select();
            }

            this->setCurrentItem(item);

            // 弹出菜单
            std::unique_ptr<BaseMenu> categoryMenu(new BaseMenu());
            categoryMenu->setFixedWidth(130);

            // 播放
            QAction *action = new QAction("播放");
            action->setIcon(QIcon(":/icons/images/play_one.png"));
            categoryMenu->addAction(action);
            if (DB->isCategoryContainSong(categoryName)) {
                connect(action, &QAction::triggered
                        , this, [] () { SONG_TABLEMODEL->batchPlay(); });
            } else {
                action->setEnabled(false);
            }

            // 重命名
            action = new QAction("重命名");
            categoryMenu->addAction(action);
            connect(action, &QAction::triggered
                    , this, [this, row] () { editCategoryName(row); });

            // 编辑封面
            action = new QAction("编辑封面");
            categoryMenu->addAction(action);
            connect(action, &QAction::triggered
                    , this, [this, row] () {
                QString coverPath = QFileDialog::getOpenFileName(this
                                                                , "选择封面"
                                                                , QDir::homePath()
                                                                , "Images (*.png *.jpg *.jpeg)");
                if (!coverPath.isEmpty()) {
                    updateCover(row, coverPath);
                    DB->updateCoverOnCategory(this->item(row)->toolTip(), coverPath);
                }
            });

            // 删除
            action = new QAction("删除");
            action->setIcon(QIcon(":/icons/images/delete.png"));
            categoryMenu->addAction(action);
            connect(action, &QAction::triggered
                    , this, [this, row, categoryName] () mutable {
                DB->removeCategory(categoryName);
                delete this->takeItem(row);
                int rows = this->count();
                if (rows) {
                    if (row == rows)
                        --row;

                    SONG_TABLEMODEL->setFilter(
                        QString("id IN (SELECT song_id FROM songCategoryRelationship WHERE category_name = '%1')")
                            .arg(this->item(row)->toolTip())
                        );
                    SONG_TABLEMODEL->select();
                } else {
                    PLAY_LISTWIDGET->setCurrentRow(1);
                }
            });

            categoryMenu->exec(QCursor::pos());
        }
    }

    QListWidget::mousePressEvent(event);
}

void CategoryListWidget::do_itemClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)

    emit exitBatchProcess();

    if (this->currentRow() == m_currentRow)
        return;

    m_currentRow = this->currentRow();

    if (PLAY_LISTWIDGET->selectionModel()->hasSelection()) {
        PLAY_LISTWIDGET->setCurrentRow(-1);
        PLAY_LISTWIDGET->clearSelection();
    }

    QString categoryName = this->currentItem()->toolTip();
    emit listSelected(categoryName);
    SONG_TABLEMODEL->updateTable(categoryName, PlaylistKind::Custom);
}
