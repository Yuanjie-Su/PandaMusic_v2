#include "coverpushbutton.h"

#include <QPaintEvent>
#include <QPainter>
// #include <QStyleOptionButton>

CoverPushButton::CoverPushButton(QWidget *parent) : QPushButton(parent) {}

void CoverPushButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    // 设置画笔抗锯齿，平滑变换等属性
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // // 获取按钮的样式选项，使用它来绘制按钮
    // QStyleOptionButton option;
    // option.initFrom(this);
    // option.state |= QStyle::State_Raised;  // 状态可以根据需要调整

    // // 绘制按钮样式
    // style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);

    // 获取图标并绘制它
    if (!icon().isNull()) {
        QRect targetRect = this->rect(); // 获取按钮的矩形区域
        QPixmap pixmap = icon().pixmap(size());  // 获取图标的 pixmap
        painter.drawPixmap(targetRect, pixmap);  // 绘制图标
    }
}
