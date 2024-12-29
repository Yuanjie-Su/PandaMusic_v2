#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include "utils/constants.h"

#include <QListWidget>

#define PLAY_LISTWIDGET PlayListWidget::instance()

class PlayListWidget : public QListWidget
{
    Q_OBJECT
public:
    // 禁止拷贝与赋值
    PlayListWidget(const PlayListWidget &) = delete;
    PlayListWidget& operator=(const PlayListWidget &) = delete;
    // 获取单例实例
    static PlayListWidget* instance(QWidget *parent = nullptr);
    PlaylistKind currentPlaylistKind() const { return m_currentKind; }

signals:
    emit void listSelected(const QString &listName);

private slots:
    void do_currentRowChanged(int row);

private:
    explicit PlayListWidget(QWidget *parent = nullptr);

    static PlayListWidget *m_instance;  // 单例实例

    PlaylistKind m_currentKind = PlaylistKind::PlayQueue;

    QString m_pathUnlikeIcon = ":/icons/images/unlike.png";
    QString m_pathPlaylist = ":/icons/images/playlist.png";
    QString m_pathHistory = ":/icons/images/history.png";
    QString m_pathLocalDownload = ":/icons/images/download.png";
};

#endif // PLAYLISTWIDGET_H
