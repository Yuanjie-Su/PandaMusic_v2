#include "titledelegate.h"

#include <QPainter>
#include <QTextDocument>

TitleDelegate::TitleDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

void TitleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 绘制封面
    painter->save();
    QRect iconRect = option.rect;
    iconRect.setSize(QSize(40, 40));
    iconRect.moveTop(iconRect.top() + 5);
    iconRect.moveLeft(iconRect.left() + 10);
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, QBrush(QColor(221, 221, 221)));
    } else {
        painter->fillRect(option.rect, index.data(Qt::BackgroundRole).value<QBrush>());
    }
    painter->drawPixmap(iconRect, index.data(Qt::DecorationRole).value<QPixmap>());
    painter->restore();

    // 绘制 title/artist
    QRect textRect = option.rect;
    textRect.moveTop(textRect.top() + 3);
    textRect.setLeft(iconRect.right() + 10);
    painter->save();
    QTextDocument doc;
    doc.setHtml(index.data(Qt::DisplayRole).toString());
    // 设置 QTextOption 为不换行
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::NoWrap);
    doc.setDefaultTextOption(textOption);
    painter->translate(textRect.topLeft());
    doc.drawContents(painter);
    painter->restore();
}
