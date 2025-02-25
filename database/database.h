#pragma once

#include <QSqlDatabase>

/**
 * @class Database
 * @brief 数据库管理类，提供数据库连接初始化和基本操作功能。
 *
 * 该类使用单例模式，确保全局只有一个数据库连接实例。
 * 支持多线程环境下的线程安全操作。
 */

#define DB Database::instance()

class Database {
public:
    Database();
    virtual ~Database();

    /**
     * @brief 获取单例实例。
     * @return 返回 Database 的单例实例。
     */
    static Database *instance();

    /**
     * @brief 初始化数据库连接。
     * @param path 数据库文件路径。
     * @return 初始化成功返回 true，否则返回 false。
     */
    bool init(const QString &path);

    /**
     * @brief 获取数据库连接对象。
     * @return 返回数据库连接对象。
     */
    QSqlDatabase &db() { return m_db; }

    bool removeCategory(const QString &categoryName);
    void updateCoverOnCategory(const QString &categoryName, const QString &coverPath);
    bool updateCategory(QString &newCategoryName, QString &oldCategoryName);

    bool isSongInCategory(const QString &name, int songId);
    bool isCategoryContainSong(QString &categoryName);
    int songFavoriteLabel(int songId);

    bool insertNameIntoCategory(const QString &name, const QString &cover);
    bool insertSongIntoCategory(const QString &categoryName, int songId);
    void insertSongIntoCategory(const QString &categoryName, QVector<int> songIdVector);
    bool insertSongIntoHistory(int songId);
    void insertSongIntoHistory(const QVector<int> &songIdVector);
    bool insertSongIntoPlaylist(int songId);
    void insertSongsIntoPlaylist(const QVector<int> &songIdVector);

    void deleteSongFromSong(int songId);
    void deleteSongFromSong(QVector<int> songIdVector);
    void deleteSongFromPlaylist(int songId);
    void deleteSongsFromPlaylist(const QVector<int> &songIdVector);
    void deleteSongFromHistory(int songId);
    void deleteSongsFromHistory(const QVector<int> &songIdVector);
    void deleteSongFromCategory(const QString &categoryName, int songId);
    void deleteSongFromCategory(const QString &categoryName, QVector<int> songIdVector);

    QString getSongPath(int songId);
    QString getSongLyricPath(int songId);
    QString getSongCoverPath(int songId);
    QVariantMap getSongDetails(int songId);
    QVariantMap getSongDisplayDetails(int songId);

    bool resetPlaylist(QList<int> &songIdlist);

    QVariantList selectFromSong();
    QVariantMap selectFromSong(int songId);
    QVariantList selectFavoritedSongs();
    QVariantList selectFromCategory();
    QList<QString> selectNameFromCategory();
    QVariantList selectFromHistory();
    QVector<int> selectSongIdFromPlaylist();
    QVariantList selectFromPlaylist();
    QVariantList selectFromSongCategory(const QString &name);

    // 导入歌曲
    bool insertSongsIntoSong();

    void updateFavoriteOnSong(int songID, int favorite);
    void updateFavoriteOnSong(QVector<int> songIdVector, int favorite);

private:
    QSqlDatabase m_db; // 数据库连接对象
    QString m_name; // 数据库名称(数据库文件绝对路径)
};
