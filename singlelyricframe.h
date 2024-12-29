#ifndef SINGLELYRICFRAME_H
#define SINGLELYRICFRAME_H

#include <QFrame>

class SingleLyricFrame : public QFrame
{
    Q_OBJECT
public:
    explicit SingleLyricFrame(QWidget *parent = nullptr);

signals:
    // 隐藏的信号
    void btnVisable(bool);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
};

#endif // SINGLELYRICFRAME_H
