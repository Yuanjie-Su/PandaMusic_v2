#include "database.h"
#include "taglibhelper/taglibhelper.h"

#include <QDebug>
#include <QGlobalStatic>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDir>
#include <QFileDialog>

// 创建一个全局静态对象，保证全局唯一、线程安全
// 延迟初始化，程序结束时自动释放
Q_GLOBAL_STATIC(Database, database)

Database::Database() {}

Database::~Database() {}

Database *Database::instance() {
    return database;
}

bool Database::init(const QString &path) {
    // 数据库已经建立连接
    if (!m_name.isEmpty()) {
        qWarning() << "database initialized";
        return true;
    }

    // 创建数据库连接
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    if (m_db.open()) {
        // 设置为数据库文件的路径，避免重复初始化
        m_name = path;

        // 启用外键约束
        QSqlQuery query(m_db);
        if (!query.exec("PRAGMA foreign_keys = ON;")) {
            qWarning() << "Failed to enable foreign keys:" << query.lastError().text();
        }

        return true;
    }

    // 数据库连接失败
    return false;
}

bool Database::insertNameIntoCategory(const QString &name, const QString &cover) {
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO category (name, cover) VALUES (:name, :cover)");
    query.bindValue(":name", name);
    query.bindValue(":cover", cover);
    if (!query.exec()) {
        qCritical() << query.lastError().text();
        return false;
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
        return false;
    }
    return true;
}

bool Database::removeCategory(const QString &categoryName) {
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM category WHERE name = :categoryName");
    query.bindValue(":categoryName", categoryName);
    if (!query.exec()) qCritical() << "category" << query.lastError().text();

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
        return false;
    }
    return true;
}

void Database::updateCoverOnCategory(const QString &categoryName, const QString &coverPath)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE category SET cover = :cover WHERE name = :name");
    query.bindValue(":cover", coverPath);
    query.bindValue(":name", categoryName);
    if (!query.exec()) qCritical() << query.lastError().text();
}

bool Database::updateCategory(QString &newCategoryName, QString &oldCategoryName)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE category SET name = :newCategoryName WHERE name = :oldCategoryName");
    query.bindValue(":newCategoryName", newCategoryName);
    query.bindValue(":oldCategoryName", oldCategoryName);
    bool ret = query.exec();
    if (!ret) qCritical() << query.lastError().text();
    return ret;
}

QVariantList Database::selectFromCategory() {
    QSqlQuery query(m_db);
    query.prepare("SELECT name, cover FROM category");
    if (!query.exec()) {
        qCritical() << query.lastError();
        return QVariantList();
    }

    QVariantList list;
    while (query.next()) {
        QVariantMap map;
        map.insert("name", query.value("name"));
        map.insert("cover", query.value("cover"));
        list.append(map);
    }
    return list;
}

QList<QString> Database::selectNameFromCategory() {
    QSqlQuery query(m_db);
    query.prepare("SELECT name FROM category");
    if (!query.exec()) {
        qCritical() << query.lastError();
        return QList<QString>();
    }

    QList<QString> list;
    while (query.next()) {
        list.append(query.value("name").toString());
    }
    return list;
}

QVariantList Database::selectFromHistory()
{
    QSqlQuery query(m_db);
    QString sql = "SELECT song.id, song.album, song.artist, "
                  "song.duration, song.title, song.favorite, song.cover "
                  "FROM song "
                  "INNER JOIN history ON song.id = history.song_id "
                  "ORDER BY history.created_at DESC";

    if (!query.exec(sql)) {
        qCritical() << query.lastError();
        return QVariantList();
    }

    QVariantList list;
    while (query.next()) {
        QVariantMap map;
        map.insert("id", query.value("id"));
        map.insert("album", query.value("album"));
        map.insert("artist", query.value("artist"));
        map.insert("duration", query.value("duration"));
        map.insert("title", query.value("title"));
        map.insert("favorite", query.value("favorite"));
        map.insert("cover", query.value("cover"));
        list.append(map);
    }
    return list;
}

QVector<int> Database::selectSongIdFromPlaylist()
{
    QSqlQuery query(m_db);
    query.prepare("SELECT song_id FROM playlist");
    if (!query.exec()) {
        qCritical() << query.lastError();
        return QVector<int>();
    }

    QVector<int> list;
    while (query.next()) {
        list.append(query.value("song_id").toInt());
    }
    return list;
}

QVariantList Database::selectFromPlaylist()
{
    QSqlQuery query(m_db);
    QString sql = "SELECT song.id, song.album, song.artist, "
                  "song.duration, song.title, song.favorite, song.cover "
                  "FROM song "
                  "INNER JOIN playlist ON song.id = playlist.song_id ";

    if (!query.exec(sql)) {
        qCritical() << query.lastError();
        return QVariantList();
    }

    QVariantList list;
    while (query.next()) {
        QVariantMap map;
        map.insert("id", query.value("id"));
        map.insert("album", query.value("album"));
        map.insert("artist", query.value("artist"));
        map.insert("duration", query.value("duration"));
        map.insert("title", query.value("title"));
        map.insert("favorite", query.value("favorite"));
        map.insert("cover", query.value("cover"));
        list.append(map);
    }
    return list;
}

QVariantList Database::selectFromSongCategory(const QString &name)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT song.id, song.title, song.album, song.artist, "
                  "song.favorite, song.duration, song.cover "
                  "FROM song "
                  "INNER JOIN songCategoryRelationship ON song.id = songCategoryRelationship.song_id "
                  "WHERE songCategoryRelationship.category_name = :categoryName");
    query.bindValue(":categoryName", name);
    if (!query.exec()) {
        qCritical() << query.lastError();
        return QVariantList();
    }

    QVariantList list;
    while (query.next()) {
        QVariantMap map;
        map.insert("id", query.value("id"));
        map.insert("album", query.value("album"));
        map.insert("artist", query.value("artist"));
        map.insert("duration", query.value("duration"));
        map.insert("title", query.value("title"));
        map.insert("favorite", query.value("favorite"));
        map.insert("cover", query.value("cover"));
        list.append(map);
    }
    return list;
}

bool Database::insertSongIntoCategory(const QString &categoryName, int songId)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO songCategoryRelationship (song_id, category_name) "
                  "VALUES (:songId, :categoryName)");
    query.bindValue(":songId", songId);
    query.bindValue(":categoryName", categoryName);
    if (!query.exec()) {
        qCritical() << "SQL Error in insertSongToCategory function: " << query.lastError().text();
        return false;
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
        return false;
    }
    return true;
}

void Database::insertSongIntoCategory(const QString &categoryName, QVector<int> songIdVector)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
    }

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO songCategoryRelationship (song_id, category_name) "
                  "VALUES (:songId, :categoryName)");
    for (const auto& songId : songIdVector) {
        query.bindValue(":songId", songId);
        query.bindValue(":categoryName", categoryName);
        if (!query.exec()) {
            qCritical() << "SQL Error in insertSongToCategory function: " << query.lastError().text();
        }
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
    }
}

bool Database::isSongInCategory(const QString &categoryName, int songId)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT song_id FROM songCategoryRelationship "
                  "WHERE category_name = :categoryName "
                  "AND song_id = :songId");
    query.bindValue(":categoryName", categoryName);
    query.bindValue(":songId", songId);
    if (query.exec() && query.next()) {
        return true;
    } else {
        // qCritical() << "SQL Error in 'isSongInCategory'" << query.lastError().text();
        return false;
    }
}

bool Database::isCategoryContainSong(QString &categoryName)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT song_id FROM songCategoryRelationship "
                  "WHERE category_name = :categoryName ");
    query.bindValue(":categoryName", categoryName);
    if (query.exec() && query.next()) {
        return true;
    } else {
        // qCritical() << "SQL Error in 'isSongInCategory'" << query.lastError().text();
        return false;
    }
}

int Database::songFavoriteLabel(int songId)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT favorite FROM song "
                  "WHERE id = :songId ");
    query.bindValue(":songId", songId);
    if (query.exec()) {
        if (query.next()) {
            return query.value("favorite").toInt();
        } else {
            qCritical() << "Not exist songId in song" << query.lastError().text();
            return -1;
        }
    } else {
        qCritical() << "SQL Error in function songFavoriteLabel()" << query.lastError().text();
        return -1;
    }
}

bool Database::insertSongIntoHistory(int songId)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO history (song_id) "
                  "VALUES (:songId)");
    query.bindValue(":songId", songId);
    if (!query.exec()) {
        qDebug() << "Error inserting song_id into history" << query.lastError();
        return false;
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
        return false;
    }
    return true;
}

void Database::insertSongIntoHistory(const QVector<int> &songIdVector)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
    }

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO history (song_id) "
                  "VALUES (:songId)");
    for (const auto& songId : songIdVector) {
        query.bindValue(":songId", songId);
        if (!query.exec()) {
            qDebug() << "Error inserting song_id into history" << query.lastError();
        }
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
    }
}

bool Database::insertSongIntoPlaylist(int songId)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO playlist (song_id) "
                  "VALUES (:songId)");
    query.bindValue(":songId", songId);
    if (!query.exec()) {
        qDebug() << "Error inserting song_id into history" << query.lastError();
        return false;
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
        return false;
    }
    return true;
}

void Database::insertSongsIntoPlaylist(const QVector<int> &songIdVector)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
    }

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO playlist (song_id) "
                  "VALUES (:songId)");
    for (const auto& songId : songIdVector) {
        query.bindValue(":songId", songId);
        if (!query.exec()) {
            qDebug() << "Error inserting song_id into history" << query.lastError();
        }
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
    }
}

void Database::deleteSongFromSong(int songId)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
    }

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM song WHERE id = :songId");
    query.bindValue(":songId", songId);
    if (!query.exec()) {
        qDebug() << "Error deleting id from song" << query.lastError();
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
    }
}

void Database::deleteSongFromSong(QVector<int> songIdVector)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
    }

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM song WHERE id = :songId");
    for (const auto& songId : songIdVector) {
        query.bindValue(":songId", songId);
        if (!query.exec()) {
            qDebug() << "Error deleting id from song" << query.lastError();
        }
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
    }
}

void Database::deleteSongFromPlaylist(int songId)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
    }

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM playlist WHERE song_id = :songId");
    query.bindValue(":songId", songId);
    if (!query.exec()) {
        qDebug() << "Error deleting song_id from playlist" << query.lastError();
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
    }
}

void Database::deleteSongsFromPlaylist(const QVector<int> &songIdVector)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
    }

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM playlist WHERE song_id = :songId");
    for (const auto& songId : songIdVector) {
        query.bindValue(":songId", songId);
        if (!query.exec()) {
            qDebug() << "Error deleting song_id from playlist" << query.lastError();
        }
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
    }
}

void Database::deleteSongFromHistory(int songId)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
    }

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM history WHERE song_id = :songId");
    query.bindValue(":songId", songId);
    if (!query.exec()) {
        qDebug() << "Error deleting song_id from history" << query.lastError();
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
    }
}

void Database::deleteSongsFromHistory(const QVector<int> &songIdVector)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
    }

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM history WHERE song_id = :songId");
    for (const auto& songId : songIdVector) {
        query.bindValue(":songId", songId);
        if (!query.exec()) {
            qDebug() << "Error deleting song_id from history" << query.lastError();
        }
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
    }
}

void Database::deleteSongFromCategory(const QString &categoryName, int songId)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
    }

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM songCategoryRelationship"
                  " WHERE song_id = :songId"
                  " AND category_name = :categoryName");
    query.bindValue(":songId", songId);
    query.bindValue(":categoryName", categoryName);
    if (!query.exec()) {
        qCritical() << "SQL Error in insertSongToCategory function: " << query.lastError().text();
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
    }
}

void Database::deleteSongFromCategory(const QString &categoryName, QVector<int> songIdVector)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
    }

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM songCategoryRelationship"
                  " WHERE song_id = :songId"
                  " AND category_name = :categoryName");
    for (const auto& songId : songIdVector) {
        query.bindValue(":songId", songId);
        query.bindValue(":categoryName", categoryName);
        if (!query.exec()) {
            qCritical() << "SQL Error in insertSongToCategory function: " << query.lastError().text();
        }
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical() << "rollback failed: " << m_db.lastError().text();
    }
}

QString Database::getSongPath(int songId)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT path FROM song WHERE id = :songId");
    query.bindValue(":songId", songId);
    if (query.exec() && query.next()) {
        return query.value("path").toString();
    } else {
        qCritical() << "Failed to get song path: " << query.lastError().text();
        return QString();
    }
}

QString Database::getSongLyricPath(int songId)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT lyric FROM song WHERE id = :songId");
    query.bindValue(":songId", songId);
    if (query.exec() && query.next()) {
        return query.value("lyric").toString();
    } else {
        qCritical() << "Failed to get song lyric path: " << query.lastError().text();
        return QString();
    }
}

QString Database::getSongCoverPath(int songId)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT cover FROM song WHERE id = :songId");
    query.bindValue(":songId", songId);
    if (query.exec() && query.next()) {
        return query.value("cover").toString();
    } else {
        qCritical() << "Failed to get song cover path: " << query.lastError().text();
        return QString();
    }
}

QVariantMap Database::getSongDetails(int songId)
{
    // title, artist, album
    QSqlQuery query(m_db);
    query.prepare("SELECT title, artist, album FROM song WHERE id = :songId");
    query.bindValue(":songId", songId);
    QVariantMap map;
    if (query.exec() && query.next()) {
        map.insert("title", query.value("title"));
        map.insert("artist", query.value("artist"));
        map.insert("album", query.value("album"));
        return map;
    } else {
        qCritical() << "Failed to get song details: " << query.lastError().text();
        return QVariantMap();
    }
}

QVariantMap Database::getSongDisplayDetails(int songId)
{
    // title, artist,lyric, favorite, cover
    QSqlQuery query(m_db);
    query.prepare("SELECT title, artist, favorite, lyric, cover FROM song WHERE id = :songId");
    query.bindValue(":songId", songId);
    QVariantMap map;
    if (query.exec() && query.next()) {
        map.insert("title", query.value("title"));
        map.insert("artist", query.value("artist"));
        map.insert("favorite", query.value("favorite"));
        map.insert("lyric", query.value("lyric"));
        map.insert("cover", query.value("cover"));
        return map;
    } else {
        qCritical() << "Failed to get song details: " << query.lastError().text();
        return QVariantMap();
    }
}


bool Database::resetPlaylist(QList<int> &songIdlist)
{
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
        return false;
    }

    // delete playlist record
    QSqlQuery query(m_db);
    if (!query.prepare("DELETE FROM playlist")) {
        qDebug() << "Error preparing query:" << query.lastError();
        return false;
    };
    if (!query.exec()) {
        qCritical() << "Error deleting playlist data:" << query.lastError().text();
        return false;
    }

    // 插入新的歌曲数据
    query.prepare("INSERT INTO playlist (song_id) VALUES (:songId)");
    for (const auto& songId : songIdlist) {
        query.bindValue(":songId", songId);
        if (!query.exec()) {
            qDebug() << "Error inserting song:" << query.lastError();
            return false;
        }
    }

    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) qCritical()
                << "rollback failed: " << m_db.lastError().text();
        return false;
    }
    return true;
}

bool Database::insertSongsIntoSong() {
    QString curPath = QDir::homePath();
    QString dlgTitle = "选择音频文件";
    QString filter = "音频文件(*.mp3 *.wav *.wma *.flac);;所有文件(*.*)";
    QStringList fileList = QFileDialog::getOpenFileNames(nullptr, dlgTitle, curPath, filter);
    if (fileList.isEmpty()) {
        qDebug() << "No files selected.";
        return false;
    }

    // 开启事务
    if (!m_db.transaction()) {
        qCritical() << "transaction failed: " << m_db.lastError().text();
        return  false;
    }

    QSqlQuery query(m_db);
    int newRecordCount = 0; // 新插入的记录数

    // 遍历文件列表
    for (const QString &filePath : fileList) {
        // 获取歌曲文件的元信息
        QVariantMap map = TagLibHelper::getPropertyList(filePath, TagLibHelper::propertyNames());
        if (map.isEmpty()) {
            qCritical() << "Failed to get song properties for file:" << filePath;
            continue;
        }

        // 获取歌词文件路径
        QFileInfo fileInfo(filePath);
        QDir dir(fileInfo.absolutePath());
        QString lyricFile = dir.filePath(fileInfo.baseName() + ".lrc");
        QFileInfo lrcFileInfo(lyricFile);
        if (!lrcFileInfo.exists()) {
            lyricFile = ""; // 歌词文件不存在, 置为空
        }

        // 准备SQL语句
        query.prepare(
            "INSERT INTO song (title, artist, cover, album, duration, path, lyric) "
            "VALUES (:title, :artist, :cover, :album, :duration, :path, :lyric)");
        query.bindValue(":title", map["title"]);
        query.bindValue(":artist", map["artist"]);
        query.bindValue(":cover", map["cover"]);
        query.bindValue(":album", map["album"]);
        query.bindValue(":duration", map["duration"]);
        query.bindValue(":path", filePath);
        query.bindValue(":lyric", lyricFile);

        // 执行插入操作
        if (query.exec()) {
            if (query.numRowsAffected() > 0) {
                qDebug() << "New record inserted for file:" << filePath;
                ++newRecordCount;
            } else {
                qDebug() << "Record already exists for file:" << filePath;
            }
        } else {
            qDebug() << "Insert failed for file:" << filePath << ", Error:" << query.lastError();
        }
    }

    // 提交事务
    if (!m_db.commit()) {
        qCritical() << "commit failed: " << m_db.lastError().text();
        if (!m_db.rollback()) {
            qCritical() << "rollback failed: " << m_db.lastError().text();
        }
        return false;
    }

    // 返回插入结果
    if (newRecordCount > 0) {
        qDebug() << "Successfully inserted" << newRecordCount << "new records.";
        return true;
    } else {
        qDebug() << "No new records inserted.";
        return false;
    }
}

void Database::updateFavoriteOnSong(int songID, int favorite)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE song SET favorite = :favorite WHERE id = :id");
    query.bindValue(":favorite", favorite);
    query.bindValue(":id", songID);
    if (!query.exec()) {
        qCritical() << "Failed to update favorite status: " << query.lastError().text();
    }
}

void Database::updateFavoriteOnSong(QVector<int> songIdVector, int favorite)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE song SET favorite = :favorite WHERE id = :id");
    for (const auto& songId : songIdVector) {
        query.bindValue(":favorite", favorite);
        query.bindValue(":id", songId);
        if (!query.exec()) {
            qCritical() << "Failed to update favorite status: " << query.lastError().text();
        }
    }
}


QVariantList Database::selectFromSong() {
    QSqlQuery query(m_db);
    QString sql = "SELECT id, album, artist, duration, title, favorite, cover "
                  "FROM song";
    if (!query.exec(sql)) {
        qCritical() << query.lastError();
        return QVariantList();
    }

    QVariantList list;
    while (query.next()) {
        QVariantMap map;
        map.insert("id", query.value("id"));
        map.insert("album", query.value("album"));
        map.insert("artist", query.value("artist"));
        map.insert("duration", query.value("duration"));
        map.insert("title", query.value("title"));
        map.insert("favorite", query.value("favorite"));
        map.insert("cover", query.value("cover"));
        list.append(map);
    }
    return list;
}

QVariantMap Database::selectFromSong(int songId)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT id, album, artist, duration, title, favorite, cover "
                  "FROM song "
                  "WHERE id = :songId");
    query.bindValue(":songId", songId);
    if (!query.exec()) {
        qCritical() << query.lastError();
        return QVariantMap();
    }

    if (query.next()) {
        QVariantMap map;
        map.insert("id", query.value("id"));
        map.insert("album", query.value("album"));
        map.insert("artist", query.value("artist"));
        map.insert("duration", query.value("duration"));
        map.insert("title", query.value("title"));
        map.insert("favorite", query.value("favorite"));
        map.insert("cover", query.value("cover"));
        return map;
    } else {
        qCritical() << query.lastError();
        return QVariantMap();
    }
}


QVariantList Database::selectFavoritedSongs() {
    QSqlQuery query(m_db);
    QString sql = QString("SELECT * FROM song WHERE favorite = 1");
    query.prepare(sql);
    if (!query.exec()) {
        qCritical() << query.lastError();
        return QVariantList();
    }

    QVariantList list;
    while (query.next()) {
        QVariantMap map;
        map.insert("id", query.value("id"));
        map.insert("album", query.value("album"));
        map.insert("artist", query.value("artist"));
        map.insert("duration", query.value("duration"));
        map.insert("title", query.value("title"));
        map.insert("favorite", query.value("favorite"));
        map.insert("cover", query.value("cover"));
        list.append(map);
    }
    return list;
}
