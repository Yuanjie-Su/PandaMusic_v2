#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player/player.h"
#include "singlelyricwidget.h"

#include <QMainWindow>
#include <QListWidgetItem>

/**
 * @class MainWindow
 * @brief 主界面类，包含播放控制、歌曲信息显示、
 * 歌词显示、播放列表显示等功能。
 */

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void do_playbackStateChanged(QMediaPlayer::PlaybackState);
    void do_positionChanged(qint64 pos);
    void do_durationChanged(qint64 duration);
    void do_songIdChanged(int songId);
    void do_metaDataChanged(const QVariantMap &songDetailsMap);

    // 批量播放按钮
    void on_btnBatchPlay_clicked();

    // 当前选中的歌单发生改变，更新歌单标题
    void do_listSelected(const QString &listName);

    // 当前播放歌曲的"喜欢"状态发生改变
    void do_favoriteChanged(int songId, int favorite);

    // 退出批量操作
    void do_exitBatchProcess();

private slots:
    // 批量操作按钮
    void on_btnBatchProcess_clicked();

    // 退出批量操作按钮
    void on_btnExitBatch_clicked();

    // 批量添加到按钮
    void on_btnBatchAddTo_clicked();

    // 批量移除按钮
    void on_btnRemoveBatch_clicked();

    // 当前播放歌曲详情部分的"喜欢"按钮
    void on_btnFavoriteOne_clicked();

    // 当前播放歌曲详情部分的"更多"按钮
    void on_btnMoreOne_clicked();

    // 播放按钮
    void on_btnPlay_clicked();

    // 音量按钮
    void on_btnVolume_clicked();
    void do_mutedChanged(bool muted);

    // 播放模式按钮
    void on_btnPlayMode_clicked();
    void do_playModeChanged(Player::PlayBackMode playBackMode);

    // 新建歌单按钮
    void on_btnNewCategory_clicked();

    // 单句歌词显示按钮
    void on_btnLyric_clicked();

    // 显示歌曲详情按钮
    void on_btnCover_clicked(bool checked);

    // 导入歌曲按钮
    void on_btnImport_clicked();

private:
    Ui::MainWindow *ui;

    // 初始化界面布局
    void initLayout();

    // 初始化当前歌曲详情
    void initCurrentSongDetails();

    // 初始化搜索框
    void initSearchLineEdit();

    // 初始化"player"模块
    void initPlayerModule();

    // 初始化"我的音乐"列表
    void initMyMusicList();

    // 单句歌词显示窗口
    SingleLyricWidget *m_singleLyricWidget = nullptr;
    // 歌词，key为时间戳，value为歌词文本
    QMap<int, QString> m_lyricMap;
    // 当前歌词戳
    int m_currentLyricKey = -1;
    // 当前歌词结束戳
    int m_currentLyricEnd = -1;
    // 当前歌曲时长
    qint64 m_duration = 1000;
    // 当前歌曲播放时间(秒)
    int m_currentSeconds = -1;
    void updateLyrics(qint64 pos);
    void nextLyricText(qint64 position);
    // 从歌词文件中解析歌词
    void parseLrcFile(const QString &filePath);
    // 更新进度条当前时间显示
    void updateLabelPosition(qint64 pos);

    // 搜索操作
    void actionSearch(const QString &text);
};

#endif // MAINWINDOW_H
