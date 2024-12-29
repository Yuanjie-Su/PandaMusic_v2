#ifndef FAVORITEDELEGATE_H
#define FAVORITEDELEGATE_H

#include <QStyledItemDelegate>

class FavoriteDelegate : public QStyledItemDelegate
{
public:
    explicit FavoriteDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

private:
    QPixmap m_favoritePixmap;
    QPixmap m_unfavoritePixmap;
};

#endif // FAVORITEDELEGATE_H
