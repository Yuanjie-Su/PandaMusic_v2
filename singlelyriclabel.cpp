#include "singlelyriclabel.h"

#include <QPainter>


SingleLyricLabel::SingleLyricLabel(QWidget *parent) : QLabel(parent) {}


void SingleLyricLabel::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font = this->font();
    painter.setFont(font);

    // 获取文字绘制区域
    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(text());
    int textHeight = metrics.height();

    int x = (width() - textWidth) / 2;
    int y = (height() + textHeight) / 2 - metrics.descent();
    int yCenter = height() / 2;

    // 绘制阴影
    painter.setPen(QColor(50, 50, 50, 180)); // 半透明黑色阴影
    painter.drawText(x - 1, y - 1, text()); // 偏移1像素

    // 绘制上半部分颜色（固定颜色）
    painter.setClipRect(x, 0, width(), yCenter); // 上半部分
    painter.setPen(QColor(122, 198, 246)); // 固定颜色
    painter.drawText(x, y, text());

    // 绘制下半部分颜色（渐变颜色）
    QLinearGradient gradient(x, yCenter, x, yCenter + textHeight / 2);
    gradient.setColorAt(0, QColor(36, 112, 190)); // 上半渐变起始色
    gradient.setColorAt(1, QColor(122, 198, 246)); // 下半渐变终止色

    painter.setClipRect(x, yCenter, width(), yCenter); // 下半部分
    painter.setPen(QPen(gradient, 0));
    painter.drawText(x, y, text());

    // 取消剪裁限制
    painter.setClipping(false);
}
