#ifndef SINGLELYRICLABEL_H
#define SINGLELYRICLABEL_H

#include <QLabel>

class SingleLyricLabel : public QLabel
{
    Q_OBJECT

public:
    explicit SingleLyricLabel(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // SINGLELYRICLABEL_H
