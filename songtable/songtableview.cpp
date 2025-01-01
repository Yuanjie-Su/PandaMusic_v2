#include "songtableview.h"
#include "favoritedelegate.h"
#include "titledelegate.h"
#include "songtablemodel.h"
#include "mymenu/moremenu.h"
#include "utils/constants.h"
#include "playlistwidget.h"
#include "categorylistwidget.h"

#include <QContextMenuEvent>

SongTableView *SongTableView::m_instance = nullptr;

SongTableView *SongTableView::instance(QWidget *parent)
{
    if (!m_instance) {
        m_instance = new SongTableView(parent);
    }
    return m_instance;
}

SongTableView::SongTableView(QWidget *parent)
    : BaseTableView(parent)
{
    setFocusPolicy(Qt::NoFocus);
    setStyleSheet(
        "QTableView {"
        "border: none;"
        "font-family: Microsoft YaHei;"
        "font-size: 9pt;"
        "font-weight: normal;"
        "color: rgb(80,80,80);"
        "}"
        "QTableView::item:hover {"
        "    background-color: rgb(221,221,221);"
        "    color: #000000;"
        "}"
        "QTableView::item:selected {"
        "    background-color: rgb(221,221,221);"
        "    color: #000000;"
        "}"
        "QTableView QScrollBar:vertical {"
        "  border: none;"
        "  background: rgb(240,240,240);"
        "  width: 4px;"
        "  margin: 0px 0px 0px 0px;"
        "}"
        "QTableView QScrollBar::handle:vertical {"
        "  background: rgb(200, 200, 200);"
        "  min-height: 20px;"
        "  border-radius: 2px;"
        "}"
        "QTableView QScrollBar::add-line:vertical {"
        "  background: rgb(240,240,240);"
        "  height: 0px;"
        "  subcontrol-position: bottom;"
        "}");
    // 垂直表头
    verticalHeader()->setDefaultSectionSize(50);
    // 关闭自动换行
    setWordWrap(false);

    // 设置数据模型
    SongTableModel::instance(this);
    SONG_TABLEMODEL->setEditStrategy(QSqlTableModel::OnFieldChange);
    SONG_TABLEMODEL->setSort(-1, Qt::AscendingOrder);
    setModel(SONG_TABLEMODEL);
    SONG_TABLEMODEL->setTable("song");

    // 创建自定义的表头，并将其设置为表头视图
    m_header = new HeaderWithCheckbox(Qt::Horizontal);
    // 获取表头列数
    int columnCount = SONG_TABLEMODEL->columnCount();
    QVector<QString> columnNames;
    for (int i = 0; i < columnCount; i++)
    {
        switch (i)
        {
        case TableColumns::TitleColumn:
            columnNames.append("歌名/歌手");
            break;
        case TableColumns::AlbumColumn:
            columnNames.append("专辑");
            break;
        case TableColumns::DurationColumn:
            columnNames.append("时长");
            break;
        default:
            columnNames.append("");
            break;
        }
    }
    m_header->setColumnNames(columnNames);
    m_header->setCheckEdit(true);
    setHorizontalHeader(m_header);
    // 设置复选框代理
    m_checkBoxDelegate = new CheckBoxDelegate(this);
    setItemDelegateForColumn(TableColumns::CheckStateColumn, m_checkBoxDelegate);
    // 设置"歌名/歌手"列的代理
    setItemDelegateForColumn(TableColumns::TitleColumn, new TitleDelegate(this));
    // 设置"favorite"列的代理
    setItemDelegateForColumn(TableColumns::FavoriteColumn, new FavoriteDelegate(this));

    // 设置列宽
    setColumnWidth(TableColumns::CheckStateColumn, 19); // 复选框列
    setColumnWidth(TableColumns::FavoriteColumn, 19); // favorite 列
    setColumnWidth(TableColumns::DurationColumn, 80); // 时长列
    horizontalHeader()->setSectionResizeMode(TableColumns::TitleColumn, QHeaderView::Stretch); // 歌名/歌手列
    horizontalHeader()->setSectionResizeMode(TableColumns::AlbumColumn, QHeaderView::Stretch); // 专辑列
    // 隐藏不需要显示的列
    setColumnHidden(TableColumns::IdColumn, true); // id 列
    setColumnHidden(TableColumns::CheckStateColumn, true); // checkState 列
    setColumnHidden(TableColumns::ArtistColumn, true); // artist 列
    setColumnHidden(TableColumns::CoverColumn, true); // cover 列
    setColumnHidden(TableColumns::PathColumn, true); // path 列
    setColumnHidden(TableColumns::LyricColumn, true); // lyric 列
    setColumnHidden(TableColumns::CreatedAtColumn, true); // created_at 列

    connect(m_header, &HeaderWithCheckbox::checkBoxToggled
            , this, [] (Qt::CheckState checkState) { SONG_TABLEMODEL->setCheckedAll(checkState); });

    connect(SONG_TABLEMODEL, &SongTableModel::checkStateChanged
            , m_header, &HeaderWithCheckbox::setCheckState);
}

bool SongTableView::enterBatchProcess()
{
    if (SONG_TABLEMODEL->rowCount()) {
        m_header->setCheckEdit(true);
        m_checkBoxDelegate->setCheckStateEdit(true);
        setColumnHidden(TableColumns::CheckStateColumn, false);
        return true;
    }
    return false;
}

void SongTableView::exitBatchProcess()
{
    m_header->setCheckEdit(false);
    m_checkBoxDelegate->setCheckStateEdit(false);
    m_header->setCheckState(Qt::Unchecked);
    setColumnHidden(TableColumns::CheckStateColumn, true);
    SONG_TABLEMODEL->resetCheckState();
}

void SongTableView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        int row = index.row();
        int songId = SONG_TABLEMODEL->data(SONG_TABLEMODEL->index(row, TableColumns::IdColumn), Qt::DisplayRole).toInt();
        int favorite = SONG_TABLEMODEL->data(SONG_TABLEMODEL->index(row, TableColumns::FavoriteColumn), Qt::DisplayRole).toInt();
        std::unique_ptr<MoreMenu> moreMenu(new MoreMenu(this
                                                        , songId
                                                        , favorite
                                                        , SONG_TABLEMODEL->currentPlaylistKind()
                                                        , CATEGORY_LISTWIDGET->currentCategoryName()));
        moreMenu->exec(QCursor::pos());
    } else {
        std::unique_ptr<MoreMenu> moreMenu(new MoreMenu(this, -1, 0));
        moreMenu->exec(QCursor::pos());
    }
}
