#include "favoritedelegate.h"
#include "utils/constants.h"

#include <QPainter>
#include <QMouseEvent>

FavoriteDelegate::FavoriteDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
    // 加载图标
    m_favoritePixmap = QPixmap(Paths::LikeIcon)
                           .scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    m_unfavoritePixmap = QPixmap(Paths::UnlikeIcon)
                             .scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void FavoriteDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, QBrush(QColor(221, 221, 221)));
    } else {
        painter->fillRect(option.rect, index.data(Qt::BackgroundRole).value<QBrush>());
    }
    // 绘制图标
    QRect iconRect = option.rect;
    iconRect.setSize(QSize(16, 16));
    iconRect.moveCenter(option.rect.center());
    int favorite = index.data(Qt::DisplayRole).toInt();
    if (favorite)
    {
        painter->drawPixmap(iconRect, m_favoritePixmap);
    }
    else
    {
        painter->drawPixmap(iconRect, m_unfavoritePixmap);
    }
}

bool FavoriteDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(option);
    // 检查事件类型是否为鼠标按下事件
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        // 检查是否为左键点击
        if (mouseEvent->button() == Qt::LeftButton) {
            int favorite = 1 - index.data(Qt::DisplayRole).toInt();
            model->setData(index, favorite, Qt::EditRole);
            return true;
        }
    }
    return false;
}
