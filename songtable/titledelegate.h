#ifndef TITLEDELEGATE_H
#define TITLEDELEGATE_H

#include <QStyledItemDelegate>

class TitleDelegate : public QStyledItemDelegate
{
public:
    explicit TitleDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TITLEDELEGATE_H
