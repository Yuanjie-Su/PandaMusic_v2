#include "musiclibrary.h"

MusicLibrary::MusicLibrary(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
}

void MusicLibrary::searchSong(const QString &text)
{
    QString apiUrl = QString("http://mobilecdn.kugou.com/api/v3/search/song?format=json&keyword=%1&page=1").arg(text);
    QNetworkRequest request(apiUrl);
    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() { onSearchFinished(reply); });
}

void MusicLibrary::onSearchFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();
        QJsonArray results = jsonObj["data"].toObject()["info"].toArray();
        qDebug() << "Number of results: " << results.size();
        // 输出每一条的歌曲信息:歌名/歌手/专辑/时长
        QVector<QVariantMap> songNames;
        for (int i = 0; i < results.size(); ++i) {
            QJsonObject song = results.at(i).toObject();
            QVariantMap songInfo;
            songInfo["songname_original"] = song["songname_original"].toString();
            songInfo["singername"] = song["singername"].toString();
            songInfo["album_name"] = song["album_name"].toString();
            songInfo["duration"] = song["duration"].toInt();
            qDebug() << songInfo;
            // songNames.append(songInfo);
        }
        // emit searchCompleted(results);
    } else {
        qDebug() << reply->errorString();
    }
    reply->deleteLater();
}

// void MusicLibrary::downloadSong(const QString &url, const QString &filePath)
// {
//     QNetworkRequest request(url);
//     QNetworkReply *reply = networkManager->get(request);
//     connect(reply, &QNetworkReply::downloadProgress, this, &MusicLibrary::downloadProgress);
//     connect(reply, &QNetworkReply::finished, this, [this, reply, filePath]() { onDownloadFinished(reply, filePath); });
// }

// void MusicLibrary::downloadLyrics(const QString &url, const QString &filePath)
// {
//     QNetworkRequest request(url);
//     QNetworkReply *reply = networkManager->get(request);
//     connect(reply, &QNetworkReply::finished, this, [this, reply, filePath]() { onDownloadFinished(reply, filePath); });
// }

// void MusicLibrary::onDownloadFinished(QNetworkReply *reply, const QString &filePath)
// {
//     if (reply->error() == QNetworkReply::NoError) {
//         QFile file(filePath);
//         if (file.open(QIODevice::WriteOnly)) {
//             file.write(reply->readAll());
//             file.close();
//             emit downloadFinished(filePath);
//         } else {
//             emit errorOccurred("Failed to open file for writing.");
//         }
//     } else {
//         emit errorOccurred(reply->errorString());
//     }
//     reply->deleteLater();
// }
