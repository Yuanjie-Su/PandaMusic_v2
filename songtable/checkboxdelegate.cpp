#include "checkboxdelegate.h"
#include "utils/constants.h"

#include <QPainter>
#include <QMouseEvent>
#include <QImageReader>

CheckBoxDelegate::CheckBoxDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void CheckBoxDelegate::setCheckStateEdit(bool edit)
{
    if (edit)
    {
        m_checkStateEdit = true;

        QImageReader reader(Paths::UncheckedIcon);
        reader.setScaledSize(QSize(32, 32));
        QImage image = reader.read();
        if (image.isNull()) {
            return;
        }
        m_uncheckedPixmap = QPixmap::fromImage(image.scaled(13, 13, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        reader.setFileName(Paths::CheckedIcon);
        image = reader.read();
        if (image.isNull()) {
            return;
        }
        m_checkedPixmap = QPixmap::fromImage(image.scaled(13, 13, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        m_checkStateEdit = false;
        m_checkedPixmap = QPixmap();
        m_uncheckedPixmap = QPixmap();
    }
}

void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (m_checkStateEdit) {
        Qt::CheckState checkState = static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt());
        QPixmap pixmap = (checkState == Qt::Checked) ? m_checkedPixmap : m_uncheckedPixmap;
        // 正中心绘制图标
        QRect iconRect = option.rect;
        iconRect.setSize(QSize(13, 13));
        iconRect.moveCenter(option.rect.center());
        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        if (option.state & QStyle::State_Selected) {
            painter->fillRect(option.rect, QBrush(QColor(221, 221, 221)));
        } else {
            painter->fillRect(option.rect, index.data(Qt::BackgroundRole).value<QBrush>());
        }
        painter->drawPixmap(iconRect, pixmap);
    }
}

bool CheckBoxDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    Q_UNUSED(option);
    // 检查事件类型是否为鼠标按下事件
    if (m_checkStateEdit && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        // 检查是否为左键点击
        if (mouseEvent->button() == Qt::LeftButton) {
            // 获取当前状态
            Qt::CheckState checkState = static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt());
            // 切换状态
            checkState = (checkState == Qt::Checked) ? Qt::Unchecked : Qt::Checked;
            // 更新数据
            model->setData(index, checkState, Qt::CheckStateRole);
            return true;
        }
    }
    return false;
}
