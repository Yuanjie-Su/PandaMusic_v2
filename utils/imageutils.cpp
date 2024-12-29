#include "imageutils.h"

#include <QImageReader>
#include <QPainter>
#include <QPainterPath>

QPixmap ImageUtils::getRoundedPixmap(const QString &coverPath, int width, int height, int radius)
{
    QImageReader reader(coverPath);

    // 限制加载分辨率，但不直接使用它的缩放模式
    reader.setScaledSize(QSize(width, height)); // 加载更高分辨率，避免初步模糊
    QImage image = reader.read();

    QPixmap srcPixmap;
    // 如果加载成功，进一步缩放以保持清晰度
    if (!image.isNull()) {
        srcPixmap =  QPixmap::fromImage(image.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        // 如果图片加载失败，返回一个默认的灰色占位符
        srcPixmap = QPixmap(width, height);
        srcPixmap.fill(Qt::gray); // 使用 fill 方法填充灰色
    }

    // 新建一个目标大小的画布
    QPixmap desPixMap(width, height);
    desPixMap.fill(Qt::transparent);

    QPainter painter(&desPixMap);
    painter.setRenderHints(QPainter::Antialiasing); //抗锯齿
    painter.setRenderHints(QPainter::SmoothPixmapTransform); //平滑像素图变换

    // 圆角路径
    QPainterPath path;
    path.addRoundedRect(0, 0, width, height, radius, radius);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, srcPixmap);

    return desPixMap;
}
