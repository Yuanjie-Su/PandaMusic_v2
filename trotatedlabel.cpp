#include "trotatedlabel.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QDebug>

TRotatedLabel::TRotatedLabel(QWidget *parent)
    : QLabel(parent)
{
    setPalette(Qt::white);
    diskPixmap.load(":/cover/images/mediaDisk.png");
    diskPixmapBackgrond.load(":/cover/images/mediaDiskBackgound.png");
    polePixmap.load(":/cover/images/pole.png");
    setMinimumSize(300, 300);

    // 初始化角度变化计时器
    connect(&angleTimer, &QTimer::timeout, this, [this] {
        angle += 1.0;
        if (angle == 360.0)
            angle = 0.0;
        update();
    });
    angleTimer.setInterval(40);

    // 初始化杆旋转计时器
    connect(&poleSpinTimer, &QTimer::timeout, this, [this] {
        if (isPlaying) {
            poleSpinAngle = qMin(poleSpinAngle + 1.0, 365.0);
            if (poleSpinAngle >= 365.0) {
                poleSpinAngle = 365.0;
                poleSpinTimer.stop();
            }
        } else {
            poleSpinAngle = qMax(poleSpinAngle - 1.0, 340.0);
            if (poleSpinAngle <= 340.0) {
                poleSpinAngle = 340.0;
                poleSpinTimer.stop();
            }
        }
        update();
    });
    poleSpinTimer.setInterval(20);
}

TRotatedLabel::~TRotatedLabel() {}

void TRotatedLabel::trogglePlay(bool isPlaying)
{
    this->isPlaying = isPlaying;
    if (isPlaying) {
        if (std::abs(poleSpinAngle - 365) > 0.1)
            poleSpinTimer.start();
        angleTimer.start();
    } else {
        if (std::abs(poleSpinAngle - 340) > 0.1)
            poleSpinTimer.start();
        angleTimer.stop();
    }
}

void TRotatedLabel::setCenterPixmap(const QPixmap &pixmap)
{
    centerPixmap = pixmap;
}

void TRotatedLabel::setPoleState(bool isPlaying)
{
    poleSpinAngle = isPlaying ? 365.0 : 340.0;
}

void TRotatedLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 设置抗锯齿和平滑变换
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    // 设置画笔颜色
    painter.setPen(Qt::transparent);

    // 获取绘制区域的矩形和半径
    const auto rect = event->rect();
    auto radius = std::min(rect.width(), rect.height()) / 2;
    // 创建一个正方形矩形框，用于绘制唱片背景的边界
    QRect rectangle(-radius, -radius, radius * 2, radius * 2);
    // 将坐标系的原点平移到绘制区域的中心，以便后续绘图以中心为基准进行操作
    painter.translate(rect.center());
    // 添加圆角效果
    QPainterPath path;
    path.addRoundedRect(rectangle, 40, 40);  // 创建圆角矩形路径
    painter.setClipPath(path);  // 设置剪切路径
    // 绘制唱片背景
    painter.drawPixmap(rectangle, diskPixmapBackgrond);

    // 绘制mediaDisk
    painter.save();
    painter.rotate(angle);
    auto tempImgRadius = radius * 0.72;
    auto tempImgRect = QRect(-tempImgRadius-5, -tempImgRadius, tempImgRadius * 2, tempImgRadius * 2);
    QPainterPath tempPath;
    tempPath.addEllipse(tempImgRect);
    painter.setClipPath(tempPath);
    painter.drawPixmap(tempImgRect, centerPixmap.scaledToWidth(tempImgRect.width()));
    painter.restore();

    painter.save();
    auto diskImgRadius = radius * 0.89;
    auto diskImgRect = QRect(-diskImgRadius, -diskImgRadius, diskImgRadius * 2, diskImgRadius * 2);
    painter.rotate(angle);
    painter.setOpacity(0.9);
    painter.drawPixmap(diskImgRect, diskPixmap);
    painter.restore();

    // 计算中间专辑封面的圆形区域
    auto centerImgRadius = radius *0.38;
    auto centerImgRect = QRect(-centerImgRadius, -centerImgRadius, centerImgRadius * 2, centerImgRadius * 2);
    // 裁剪中间图像为圆形并旋转
    painter.save();
    QPainterPath imgPath;
    imgPath.addEllipse(centerImgRect);
    painter.setClipPath(imgPath);
    painter.rotate(angle);
    painter.setOpacity(1);
    painter.drawPixmap(centerImgRect, centerPixmap.scaledToWidth(centerImgRect.width()));
    painter.restore();

    // 计算杆子的绘制大小
    auto poleRectWidth = rect.width() * 0.2;
    auto poleRectHeight = rect.width() * 0.365;
    auto polePixmapTemp = polePixmap.scaled(QSize(poleRectWidth, poleRectHeight), Qt::KeepAspectRatio);
    // 计算旋转的中心点
    auto rotationCenter = rectangle.topRight() + QPoint(- poleRectWidth * 0.7, poleRectHeight * 0.4);
    // 绘制杆子
    painter.save();
    painter.translate(rotationCenter);  // 平移到旋转中心
    painter.rotate(fmod(poleSpinAngle, 360.0));
    painter.drawPixmap(QPoint(- poleRectWidth / 2, - 7* poleRectHeight / 24), polePixmapTemp);
    painter.restore();
}
