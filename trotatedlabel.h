#ifndef ROTATEDLABEL_H
#define ROTATEDLABEL_H

#include <QLabel>
#include <QTimer>

class TRotatedLabel : public QLabel
{
    Q_OBJECT

public:
    TRotatedLabel(QWidget *parent = nullptr);
    ~TRotatedLabel() override;

    void trogglePlay(bool);
    void setCenterPixmap(const QPixmap &pixmap);
    void setPoleState(bool isPlaying);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap diskPixmap;
    QPixmap diskPixmapBackgrond;
    QPixmap polePixmap;
    QPixmap centerPixmap;

    bool isPlaying{true};
    qreal angle{0.0};
    QTimer angleTimer;

    qreal poleSpinAngle{340.0};
    QTimer poleSpinTimer;
};

#endif // ROTATEDLABEL_H

