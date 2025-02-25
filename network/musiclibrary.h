#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

class MusicLibrary : public QObject
{
    Q_OBJECT

public:
    explicit MusicLibrary(QObject *parent = nullptr);

    void searchSong(const QString &text);
    // void downloadSong(const QString &url, const QString &filePath);
    // void downloadLyrics(const QString &url, const QString &filePath);

signals:
    void searchCompleted(const QJsonArray &results);
    // void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    // void downloadFinished(const QString &filePath);

private slots:
    void onSearchFinished(QNetworkReply *reply);
    // void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    // void onDownloadFinished(QNetworkReply *reply, const QString &filePath);

private:
    QNetworkAccessManager *networkManager;
};

#endif // MUSICLIBRARY_H
