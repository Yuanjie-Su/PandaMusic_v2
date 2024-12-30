#pragma once

#include <QSqlDatabase>
#include <memory>

#define DB Database::instance()

class QMutex;
class Database {
public:
    Database();
    virtual ~Database();
    static Database *instance();
    bool init(const QString &path);
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

    bool insertSongsIntoSong();

    void updateFavoriteOnSong(int songID, int favorite);
    void updateFavoriteOnSong(QVector<int> songIdVector, int favorite);


private:
    QString currentDateTime();

private:
    QSqlDatabase m_db;
    std::unique_ptr<QMutex> m_mutex;
    QString m_name;
};
