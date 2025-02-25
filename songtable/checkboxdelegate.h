#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>

class CheckBoxDelegate : public QStyledItemDelegate {
public:
    explicit CheckBoxDelegate(QObject *parent = nullptr);

    void setCheckStateEdit(bool edit);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

private:
    bool m_checkStateEdit = false;
    QPixmap m_checkedPixmap;
    QPixmap m_uncheckedPixmap;
};

#endif // CHECKBOXDELEGATE_H
