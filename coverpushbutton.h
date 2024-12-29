#ifndef COVERPUSHBUTTON_H
#define COVERPUSHBUTTON_H

#include <QPushButton>

class CoverPushButton : public QPushButton
{
    Q_OBJECT

public:
    CoverPushButton(QWidget *parent=nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // COVERPUSHBUTTON_H
