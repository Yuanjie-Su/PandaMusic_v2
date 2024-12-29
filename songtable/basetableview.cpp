#include "basetableview.h"
#include "songtablemodel.h"

#include <QMouseEvent>
#include <QHeaderView>

BaseTableView::BaseTableView(QWidget *parent)
    : QTableView(parent)
{
    // 设置选择模式为按行选择
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);

    // 设置表格不可编辑
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 去掉水平滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 设置鼠标追踪
    setMouseTracking(true);

    // 去除网格线
    setShowGrid(false);

    // 隐藏垂直表头
    verticalHeader()->setHidden(true);
}

void BaseTableView::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    // 恢复之前悬停行的背景色
    restoreOldRowBackground();
}

void BaseTableView::mouseMoveEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        int currentRow = index.row();
        if (m_oldEnteredRow != currentRow) {
            // 恢复之前悬停行的背景色
            restoreOldRowBackground();

            // 设置当前悬停行的背景色
            m_oldEnteredRow = currentRow;
            if (m_oldEnteredRow != m_oldSelectedRow) {
                updateRowBackground(m_oldEnteredRow, m_colorSelected);
            }
        }
    } else {
        // 恢复之前悬停行的背景色
        restoreOldRowBackground();
    }
}

void BaseTableView::wheelEvent(QWheelEvent *event)
{
    QTableView::wheelEvent(event);

    QPoint mousePos = viewport()->mapFromGlobal(QCursor::pos());
    QModelIndex index = indexAt(mousePos);

    if (index.isValid()) {
        int currentRow = index.row();
        if (m_oldEnteredRow != currentRow) {
            restoreOldRowBackground();

            m_oldEnteredRow = currentRow;
            if (m_oldEnteredRow != m_oldSelectedRow) {
                updateRowBackground(m_oldEnteredRow, m_colorSelected);
            }
        }
    } else {
        restoreOldRowBackground();
    }
}

void BaseTableView::updateRowBackground(int row, const QColor &color)
{
    SongTableModel *model = qobject_cast<SongTableModel *>(this->model());
    if (!model) {
        return;
    }

    model->setData(model->index(row, 0), QBrush(color), Qt::BackgroundRole);
}

void BaseTableView::restoreOldRowBackground()
{
    if (m_oldEnteredRow != -1 && m_oldEnteredRow != m_oldSelectedRow) {
        if (m_oldEnteredRow % 2) {
            updateRowBackground(m_oldEnteredRow, m_colorUnselectedOdd);
        } else {
            updateRowBackground(m_oldEnteredRow, m_colorUnselected);
        }
        m_oldEnteredRow = -1;
    }
}
