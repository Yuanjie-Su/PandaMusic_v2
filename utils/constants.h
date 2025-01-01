#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

// 图标路径
namespace Icons {

}

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
