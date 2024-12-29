#include "basewidget.h"

#include <QMouseEvent>

BaseWidget::BaseWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint); // 无边框
    this->setAttribute(Qt::WA_TranslucentBackground); // 透明
}

void BaseWidget::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button()) {
        m_pressed = true;
        m_pos = event->pos();
    }

    QWidget::mousePressEvent(event);
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressed) {
        move(event->pos() - m_pos + pos());
    }

    QWidget::mouseMoveEvent(event);
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    QWidget::mouseReleaseEvent(event);
}
