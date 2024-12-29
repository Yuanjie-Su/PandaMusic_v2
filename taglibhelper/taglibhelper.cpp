#include "TagLibHelper.h"

#include <fileref.h>
#include <taglib.h>
#include <mpegfile.h>
#include <id3v2.h>
#include <id3v2tag.h>
#include <id3v2frame.h>
#include <attachedpictureframe.h>
#include <tag.h>

#include <QPixmap>
#include <QFileInfo>
#include <QDir>


QStringList TagLibHelper::propertyNames() {
    return {"title", "artist", "album", "duration", "cover"};
}


QVariantMap TagLibHelper::getPropertyList(const QString &path, const QStringList &nameList) {
    if (!QFile::exists(path)) {
        qCritical() << "file not exists: " << path;
        return QVariantMap();
    }

    // 提取歌曲元信息
    std::unique_ptr<TagLib::FileRef> ref(new TagLib::FileRef(TagLib::FileName(path.toLocal8Bit().data())));
    if (!ref || ref->isNull() || !ref->tag()) {
        qCritical() << "Failed to load file:" << path;
        return QVariantMap();
    }

    TagLib::Tag *tag = ref->tag();
    QVariantMap resultMap;
    for (const auto &name : nameList) {
        switch (propertyNames().indexOf(name)) {
        case 0: {
            QString title = QString::fromWCharArray(tag->title().toCWString());
            if (title.isEmpty())
                return QVariantMap();
            else
                resultMap.insert(name, QString::fromWCharArray(tag->title().toCWString()));
            break;
        }
        case 1: {
            QString artist = QString::fromWCharArray(tag->artist().toCWString());
            if (artist.isEmpty())
                return QVariantMap();
            else
                resultMap.insert(name, QString::fromWCharArray(tag->artist().toCWString()));
            break;
        }
        case 2: {
                resultMap.insert(name, QString::fromWCharArray(tag->album().toCWString()));
                break;
        }

        case 3: {
            int duration = ref->audioProperties()->lengthInSeconds();
            if (duration)
                resultMap.insert(name, duration);
            else
                return QVariantMap();
            break;
        }

            case 4: {
                // 检查是否已有封面文件
                QFileInfo fileInfo(path);
                QString pngCoverPath = fileInfo.absolutePath()
                                       + QDir::separator()
                                       + fileInfo.completeBaseName() + ".png";
                QString jpgCoverPath = fileInfo.absolutePath()
                                       + QDir::separator()
                                       + fileInfo.completeBaseName() + ".jpg";

                if (QFile::exists(pngCoverPath)) {
                    resultMap.insert(name, pngCoverPath);
                } else if (QFile::exists(jpgCoverPath)) {
                    resultMap.insert(name, jpgCoverPath);
                } else {
                    // 提取专辑封面并保存
                    resultMap.insert(name, extractAndSaveAlbumCover(path, pngCoverPath)
                                               ? pngCoverPath : DEFAULT_COVER_PATH);
                }
                break;
            }
            default:
                qCritical() << "unsupported property: " << name;
                break;
        }
    }
    return resultMap;
}


bool TagLibHelper::extractAndSaveAlbumCover(const QString &path, const QString &outputFilePath) {
    // 打开 MP3 文件
    TagLib::MPEG::File file(path.toLocal8Bit().data());
    if (!file.isValid()) {
        qCritical() << "Invalid MP3 file for extracting album cover:" << path;
        return false;
    }

    // 获取 ID3v2 标签
    TagLib::ID3v2::Tag *tag = file.ID3v2Tag();
    if (!tag) {
        qCritical() << "No ID3v2 tag found for album cover:" << path;
        return false;
    }

    // 获取帧列表映射（FrameListMap）
    const TagLib::ID3v2::FrameListMap &frameListMap = tag->frameListMap();

    // 检查是否存在 "APIC" 帧
    if (!frameListMap.contains("APIC")) {
        qCritical() << "No APIC frame found for album cover:" << path;
        return false;
    }

    // 获取与 "APIC" 相关的帧列表
    const TagLib::ID3v2::FrameList &frames = frameListMap["APIC"];

    if (frames.isEmpty()) {
        qCritical() << "APIC frame list is empty for album cover:" << path;
        return false;
    }

    // 提取第一帧（通常为专辑封面图片）
    auto *pictureFrame = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame *>(frames.front());
    if (!pictureFrame) {
        qCritical() << "Failed to extract picture frame for album cover:" << path;
        return false;
    }

    // 转换图片数据为 QByteArray
    QByteArray imageData(pictureFrame->picture().data(), pictureFrame->picture().size());

    // 检查是否有数据
    if (imageData.isEmpty()) {
        qCritical() << "Image data is empty for album cover:" << path;
        return false;
    }

    // 保存图片到文件
    QPixmap pixmap;
    if (!pixmap.loadFromData(imageData)) {
        qCritical() << "Failed to load image data into QPixmap for album cover:" << path;
        return false;
    }

    if (!pixmap.save(outputFilePath, "PNG")) {
        qCritical() << "Failed to save album cover to file:" << outputFilePath;
        return false;
    }

    qDebug() << "Album cover saved to:" << outputFilePath;
    return true;
}
