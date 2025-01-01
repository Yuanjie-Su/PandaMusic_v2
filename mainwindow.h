#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player/player.h"
#include "singlelyricwidget.h"

#include <QMainWindow>
#include <QMediaPlayer>
#include <QListWidgetItem>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString m_pathLikeIcon = ":/icons/images/like.png";
    QString m_pathUnlikeIcon = ":/icons/images/unlike.png";
    QString m_pathPlayIcon = ":/icons/images/play.png";
    QString m_pathMoreIcon = ":/icons/images/more.png";
    QString m_pathAddIcon = ":/icons/images/add.png";
    QString m_pathPauseIcon = ":/icons/images/pause.png";
    QString m_pathCover = ":/cover/images/panda-listening-music.jpg";
    QString m_pathNewCategoryIcon = ":/icons/images/newCategory.png";
    QString m_pathHistory = ":/icons/images/history.png";
    QString m_pathLocalDownload = ":/icons/images/download.png";
    QString m_pathPlaylist = ":/icons/images/playlist.png";

public slots:
    void do_playbackStateChanged(QMediaPlayer::PlaybackState);
    void do_positionChanged(qint64 pos);
    void do_durationChanged(qint64 duration);
    void do_songIdChanged(int songId);
    void do_metaDataChanged(const QVariantMap &songDetailsMap);
    void on_btnBatchPlay_clicked();
    void do_listSelected(const QString &listName);
    void do_favoriteChanged(int songId, int favorite);
    void do_exitBatchProcess();

private slots:
    void on_btnBatchProcess_clicked();
    void on_btnExitBatch_clicked();
    void on_btnBatchAddTo_clicked();
    void on_btnRemoveBatch_clicked();

    void on_btnFavoriteOne_clicked();
    void on_btnMoreOne_clicked();

    void on_btnPlay_clicked();
    void on_btnVolume_clicked();
    void do_mutedChanged(bool muted);
    void on_btnPlayMode_clicked();
    void do_playModeChanged(Player::PlayBackMode playBackMode);

    void on_btnNewCategory_clicked();

    void on_btnLyric_clicked();
    void on_btnCover_clicked(bool checked);

    void on_btnImport_clicked();

private:
    Ui::MainWindow *ui;

    SingleLyricWidget *m_singleLyricWidget = nullptr; // 歌词窗口
    QMap<int, QString> m_lyricMap; // 歌词
    // 当前歌词戳
    int m_currentLyricKey = -1;
    // 当前歌词结束时间
    int m_currentLyricEnd = -1;
    // 当前歌曲的总时长
    qint64 m_duration = 1000;
    // 当前时间点(秒)
    int m_currentSeconds = -1;
    void updateLyrics(qint64 pos);
    void nextLyricText(qint64 position);
    // 从歌词文件中解析歌词
    void parseLrcFile(const QString &filePath);
    // 更新进度条当前时间显示
    void updateLabelPosition(qint64 pos);
    void actionSearch(const QString &text);

};

#endif // MAINWINDOW_H
