#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

class BaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    // 鼠标按下时的位置
    QPoint m_pos;
    // 鼠标是否按下
    bool m_pressed = false;

};

#endif // BASEWIDGET_H
