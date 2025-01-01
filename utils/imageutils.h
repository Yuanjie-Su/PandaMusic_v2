#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <QPixmap>

namespace ImageUtils {

// 加载并缩放封面图片
QPixmap getRoundedPixmap(const QString &coverPath, int width = 64, int height = 64, int radius = 6);
QPixmap getRoundedPixmap(const QImage &coverImage, int width = 64, int height = 64, int radius = 6);
QPixmap getRoundedPixmap(const QPixmap &coverPixmap, int width = 64, int height = 64, int radius = 6);

} // namespace ImageUtils

#endif // IMAGEUTILS_H
