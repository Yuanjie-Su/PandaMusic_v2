#pragma once

#include <QVariantMap>
#include <QStringList>

namespace {
    const QString DEFAULT_COVER_PATH = ":/cover/images/panda-listening-music.jpg";
}

class TagLibHelper {
public:
    static QStringList propertyNames();
    static QVariantMap getPropertyList(const QString &path
                                       , const QStringList &nameList);

private:
    TagLibHelper() = default;
    static bool extractAndSaveAlbumCover(const QString &path, const QString &outputFilePath);
};
