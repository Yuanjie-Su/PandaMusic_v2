#include "songtablemodel.h"
#include "utils/imageutils.h"
#include "database/database.h"
#include "player/player.h"

#include <QBrush>

SongTableModel *SongTableModel::m_instance = nullptr;

SongTableModel *SongTableModel::instance(QObject *parent)
{
    if (!m_instance) {
        m_instance = new SongTableModel(parent, DB->db());
    }
    return m_instance;
}

SongTableModel::SongTableModel(QObject *parent, QSqlDatabase db) : QSqlTableModel(parent, db) {}

void SongTableModel::setCheckedAll(Qt::CheckState checked)
{
    notAllCheckedEdit = false;
    int rowCount = this->rowCount();
    for (int i = 0; i < rowCount; ++i)
    {
        setData(index(i, TableColumns::CheckStateColumn), checked, Qt::CheckStateRole);
    }
    notAllCheckedEdit = true;
}

void SongTableModel::batchPlay(bool allSelected)
{
    QVector<int> songIdVector;
    int rowCount = this->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        if (allSelected || checkStateMap[i] == Qt::Checked) {
            int songId = QSqlTableModel::data(this->index(i, TableColumns::IdColumn), Qt::DisplayRole).toInt();
            songIdVector.append(songId);
        }
    }
    if (songIdVector.isEmpty())
        return;

    PLAYER->play(songIdVector);
}

void SongTableModel::removeSelected(const QString &categoryName)
{
    QVector<int> songIdVector;
    int rowCount = this->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        if (checkStateMap[i] == Qt::Checked) {
            int songId = QSqlTableModel::data(this->index(i, TableColumns::IdColumn), Qt::DisplayRole).toInt();
            songIdVector.append(songId);
        }
    }
    if (songIdVector.isEmpty())
        return;

    switch (m_currentKind) {
    case PlaylistKind::Favorite:
        DB->updateFavoriteOnSong(songIdVector, 0);
        break;
    case PlaylistKind::PlayQueue:
        PLAYER->removeSongs(songIdVector);
        break;
    case PlaylistKind::History:
        DB->deleteSongsFromHistory(songIdVector);
        break;
    case PlaylistKind::Custom: {
        if (categoryName.isEmpty()) {
            qWarning() << "Category name is empty.";
            return;
        }
        DB->deleteSongFromCategory(categoryName, songIdVector);
        break;
    }
    default:
        DB->deleteSongFromSong(songIdVector);
        break;
    }

    select();
}

void SongTableModel::removeSong(int songId, PlaylistKind listKind, const QString &categoryName)
{
    switch (listKind) {
    case PlaylistKind::Favorite:
        DB->updateFavoriteOnSong(songId, 0);
        break;
    case PlaylistKind::PlayQueue:
        PLAYER->removeSong(songId);
        break;
    case PlaylistKind::History:
        DB->deleteSongFromHistory(songId);
        break;
    case PlaylistKind::Custom: {
        if (categoryName.isEmpty()) {
            qWarning() << "Category name is empty.";
            return;
        }
        DB->deleteSongFromCategory(categoryName, songId);
        break;
    }
    default:
        DB->deleteSongFromSong(songId);
        break;
    }

    if (listKind == m_currentKind)
        select();
}

QVector<int> SongTableModel::selectedSongIds()
{
    QVector<int> songIdVector;
    int rowCount = this->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        if (checkStateMap[i] == Qt::Checked) {
            int songId = QSqlTableModel::data(this->index(i, TableColumns::IdColumn), Qt::DisplayRole).toInt();
            songIdVector.append(songId);
        }
    }
    return songIdVector;
}

void SongTableModel::resetCheckState()
{
    checkStateMap.fill(Qt::Unchecked);
}

void SongTableModel::changeFavorite(int favorite, int songId)
{
    int rowCount = this->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        int id = QSqlTableModel::data(this->index(i, TableColumns::IdColumn), Qt::DisplayRole).toInt();
        if (id == songId) {
            setData(index(i, TableColumns::FavoriteColumn), favorite, Qt::EditRole);
            break;
        }
    }
}

void SongTableModel::updateTable(const QString &listName, PlaylistKind kind)
{
    switch (kind) {
    case PlaylistKind::Favorite: {
        m_currentKind = PlaylistKind::Favorite;
        setFilter("favorite = 1");
        break;
    }
    case PlaylistKind::PlayQueue: {
        m_currentKind = PlaylistKind::PlayQueue;
        setFilter("id IN (SELECT song_id FROM playlist)");
        break;
    }
    case PlaylistKind::History: {
        m_currentKind = PlaylistKind::History;
        setFilter("id IN (SELECT song_id FROM history)");
        break;
    }
    case PlaylistKind::LocalAndDownload: {
        m_currentKind = PlaylistKind::LocalAndDownload;
        setFilter("");
        break;
    }
    case PlaylistKind::Custom: {
        m_currentKind = PlaylistKind::Custom;
        setFilter(QString("id IN (SELECT song_id FROM songCategoryRelationship WHERE category_name = '%1')").arg(listName));
        break;
    }
    case PlaylistKind::SearchList: {
        m_currentKind = PlaylistKind::SearchList;
        setFilter(QString("LOWER(title) LIKE LOWER('%%1%')"
                          " OR LOWER(artist) LIKE LOWER('%%1%')"
                          " OR LOWER(album) LIKE LOWER('%%1%')").arg(listName));
        break;
    }
    }
    select();
}

QVariant SongTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::BackgroundRole)
    {
        return QBrush(m_rowBackground[index.row()]);
    }

    // 缓存原始数据，减少多次调用
    QVariant baseData = QSqlTableModel::data(index, role);
    // 针对 title 列的处理
    if (index.column() == TableColumns::TitleColumn) {
        if (role == Qt::DisplayRole) {
            // 获取 title 和 artist 数据
            QString title = baseData.toString();
            QString artist = QSqlTableModel::data(this->index(index.row(), TableColumns::ArtistColumn), Qt::DisplayRole).toString();
            return QString("<div style='line-height: 1.1;'>"
                           "<p style='margin:0; font-family:Microsoft YaHei; font-size:13px; color:#000000;'>%1</p>"
                           "<p style='margin:0; font-family:Microsoft YaHei; font-size:11px; color:#505050;'>%2</p>")
                .arg(title, artist);
        }
        if (role == Qt::DecorationRole) {
            int songId = QSqlTableModel::data(this->index(index.row(), TableColumns::IdColumn), Qt::DisplayRole).toInt();
            if (m_coverCache.contains(songId)) {
                return m_coverCache[songId];
            } else {
                QString coverPath = QSqlTableModel::data(this->index(index.row(), TableColumns::CoverColumn), Qt::DisplayRole).toString();
                QPixmap cover = ImageUtils::getRoundedPixmap(coverPath, 40, 40);
                m_coverCache[songId] = cover;
                return cover;
            }
        }
    }

    // 针对 duration 列的处理
    if (index.column() == TableColumns::DurationColumn && role == Qt::DisplayRole)
    {
        int duration = baseData.toInt();
        return QString("%1:%2").arg(duration / 60, 2, 10, QLatin1Char('0')).arg(duration % 60, 2, 10, QLatin1Char('0'));
    }

    // 针对 checkState 列的处理
    if (index.column() == TableColumns::CheckStateColumn && role == Qt::CheckStateRole)
    {
        return checkStateMap[index.row()];
    }

    return baseData;
}

bool SongTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() < 0 || index.row() >= rowCount())
    {
        qWarning() << "Invalid index.";
        return false;
    }

    int row = index.row();
    int column = index.column();

    if (role == Qt::BackgroundRole)
    {
        if (!value.canConvert<QBrush>()) {
            qWarning() << "Invalid value for BackgroundRole. Expected QBrush.";
            return false;
        }

        m_rowBackground[row] = value.value<QBrush>().color();
        emit dataChanged(index, index, {Qt::BackgroundRole});
        return true;
    }

    if (column == TableColumns::CheckStateColumn && role == Qt::CheckStateRole)
    {
        Qt::CheckState checkState = static_cast<Qt::CheckState>(value.toInt());
        if (checkStateMap[row] == checkState)
            return true;

        checkStateMap[row] = checkState;
        updateCheckState(row, checkState);
        emit dataChanged(index, index, {Qt::CheckStateRole});
        return true;
    }

    // 检测是否是 favorite 列，并且 role 是 Qt::EditRole
    if (column == TableColumns::FavoriteColumn && role == Qt::EditRole) {
        emit favoriteChanged(QSqlTableModel::data(this->index(row, TableColumns::IdColumn), Qt::DisplayRole).toInt(), value.toInt());
        if (m_currentKind == PlaylistKind::Favorite
            && QSqlTableModel::setData(index, value, role)){
        select();
        return false;
        }
    }

    return QSqlTableModel::setData(index, value, role);
}

Qt::ItemFlags SongTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if (index.column() != TableColumns::FavoriteColumn)
    {
        return flags;
    }

    return flags | Qt::ItemIsEditable;
}

QString SongTableModel::selectStatement() const {
    QString baseQuery = "SELECT song.* FROM song";

    // 如果当前 filter 是 history 的查询
    if (filter().contains("id IN (SELECT song_id FROM history)")) {
        baseQuery += " JOIN history ON song.id = history.song_id";
        baseQuery += " WHERE " + filter();
        baseQuery += " ORDER BY history.created_at DESC";
    } else if (!filter().isEmpty()) {
        baseQuery += " WHERE " + filter();
    }

    return baseQuery;
}

bool SongTableModel::select() {
    bool success = QSqlTableModel::select();
    if (success) {
        int rowCount = QSqlTableModel::rowCount();

        checkStateMap.clear();
        checkedCount = 0;
        emit checkStateChanged(Qt::Unchecked);
        checkStateMap.resize(rowCount, Qt::Unchecked);

        m_rowBackground.clear();
        // 偶数奇数行背景色
        for (int i = 0; i < rowCount; ++i) {
            m_rowBackground.append(i % 2 ? QColor(243, 243, 243) : QColor(249, 249, 249));
        }
    }
    return success;
}

void SongTableModel::updateCheckState(int row, Qt::CheckState checkState)
{
    checkStateMap[row] = checkState;
    if (checkState == Qt::Checked)
        ++checkedCount;
    else
        --checkedCount;

    if (notAllCheckedEdit)
    {
        emit checkStateChanged(
            (checkedCount == rowCount()) ? Qt::Checked :
                (checkedCount == 0) ? Qt::Unchecked :
                Qt::PartiallyChecked);
    }
}
