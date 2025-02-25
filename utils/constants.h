#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

// 文件路径
class Paths {
public:
    // 默认封面
    static const QString DefaultCover;

    // 图标
    static const QString PlayOneIcon;
    static const QString PlayNextIcon;
    static const QString PlaySimilarIcon;
    static const QString PlayMvIcon;
    static const QString PlayIcon;
    static const QString PauseIcon;

    static const QString AddToNewIcon;
    static const QString DownloadIcon;
    static const QString ShareIcon;
    static const QString CopyIcon;

    static const QString DeleteIcon;
    static const QString LyricHideIcon;

    static const QString LikeIcon;
    static const QString UnlikeIcon;

    static const QString CheckedIcon;
    static const QString UncheckedIcon;
    static const QString PartiallyCheckedIcon;

    static const QString VolumeIcon;
    static const QString MuteIcon;

    static const QString SearchIcon;

    static const QString SequentialIcon;
    static const QString LoopSequentialIcon;
    static const QString LoopSingleIcon;
    static const QString RandomIcon;

    static const QString LocalDownloadIcon;
    static const QString HistoryIcon;
    static const QString PlaylistIcon;
};

// 表格列索引
namespace TableColumns {
constexpr int IdColumn = 0;
constexpr int CheckStateColumn = 1;
constexpr int TitleColumn = 2;
constexpr int ArtistColumn = 3;
constexpr int CoverColumn = 4;
constexpr int FavoriteColumn = 5;
constexpr int AlbumColumn = 6;
constexpr int DurationColumn = 7;
constexpr int PathColumn = 8;
constexpr int LyricColumn = 9;
constexpr int CreatedAtColumn = 10;
}

enum class PlaylistKind {
    Favorite = 0,
    PlayQueue,
    History,
    LocalAndDownload,
    Custom,
    SearchList,
};

#endif // CONSTANTS_H
