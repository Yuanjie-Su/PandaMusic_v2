#include "headerwithcheckbox.h"
#include "utils/constants.h"

#include <QMouseEvent>
#include <QPainter>
#include <QImageReader>

HeaderWithCheckbox::HeaderWithCheckbox(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent)
{
    m_checkState = Qt::Unchecked;
}

void HeaderWithCheckbox::setColumnNames(const QVector<QString> &columnNames)
{
    m_columnNames = columnNames;
}

void HeaderWithCheckbox::setCheckState(Qt::CheckState checkState)
{
    if (this->m_checkState == checkState)
        return;

    this->m_checkState = checkState;
    updateSection(m_checkColumn);
}

void HeaderWithCheckbox::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const {
    // 填充背景色
    painter->fillRect(rect, QBrush(QColor(249, 249, 249)));

    if (logicalIndex != 1)
    {
        QRect textRect = rect;
        textRect.moveLeft(textRect.left() + 5);
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, m_columnNames[logicalIndex]);
    } else if (m_checkStateEdit) {
        QString iconPath;
        switch (m_checkState) {
        case Qt::Unchecked:
            iconPath = Paths::UncheckedIcon;
            break;
        case Qt::Checked:
            iconPath = Paths::CheckedIcon;
            break;
        case Qt::PartiallyChecked:
            iconPath = Paths::PartiallyCheckedIcon;
            break;
        }
        QImageReader reader(iconPath);
        reader.setScaledSize(QSize(32, 32));
        QImage image = reader.read();
        if (image.isNull()) {
            return;
        }

        QPixmap pixmap = QPixmap::fromImage(image.scaled(13, 13, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        // 正中心绘制图标
        QRect iconRect = rect;
        iconRect.setSize(QSize(13, 13));
        iconRect.moveCenter(rect.center());
        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter->drawPixmap(iconRect, pixmap);
    }
}

void HeaderWithCheckbox::mousePressEvent(QMouseEvent *event) {
    int logicalIndex = logicalIndexAt(event->pos());
    if (m_checkStateEdit && logicalIndex == m_checkColumn) {
            m_checkState = m_checkState == Qt::Checked ? Qt::Unchecked : Qt::Checked;
            emit checkBoxToggled(m_checkState);
            updateSection(logicalIndex);
    }
}
