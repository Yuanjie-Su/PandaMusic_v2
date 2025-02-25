#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./database/database.h"
#include "volumecontrolwidget.h"
#include "playmodecontrolwidget.h"
#include "songtable/songtableview.h"
#include "songtable/songtablemodel.h"
#include "categorylistwidget.h"
#include "playlistwidget.h"
#include "utils/imageutils.h"
#include "utils/constants.h"
#include "myMenu/moremenu.h"
#include "myMenu/batchaddtomenu.h"
#include "trotatedlabel.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化布局
    initLayout();
    // 初始化当前播放歌曲详情
    initCurrentSongDetails();
    // 初始化搜索框
    initSearchLineEdit();
    // 初始化"我的音乐"列表
    initMyMusicList();
    // 初始化"player"模块
    initPlayerModule();

    connect(CATEGORY_LISTWIDGET, &CategoryListWidget::listSelected,
            this, &MainWindow::do_listSelected);
    connect(CATEGORY_LISTWIDGET, &CategoryListWidget::exitBatchProcess,
            this, &MainWindow::do_exitBatchProcess);
    connect(SONG_TABLEMODEL, &SongTableModel::favoriteChanged,
            this, &MainWindow::do_favoriteChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 主界面播放按钮
void MainWindow::on_btnPlay_clicked()
{
    if (PLAYER->isPlaying()) {
        PLAYER->pause();
    } else {
        PLAYER->play();
    }
}

void MainWindow::do_playbackStateChanged(QMediaPlayer::PlaybackState state)
{
    // 更新播放按钮图标
    QIcon icon;
    if (state == QMediaPlayer::PlayingState) {
        icon.addFile(Paths::PauseIcon);
        ui->btnPlay->setIcon(icon);
        ui->btnPlay->setToolTip("暂停");
        if (ui->lyricsWidget->isVisible())
            ui->lyricsWidget->coverDisk()->trogglePlay(true);
    } else {
        icon.addFile(Paths::PlayIcon);
        ui->btnPlay->setIcon(icon);
        ui->btnPlay->setToolTip("播放");
        if (ui->lyricsWidget->isVisible())
            ui->lyricsWidget->coverDisk()->trogglePlay(false);
    }
}

void MainWindow::do_positionChanged(qint64 pos)
{
    updateLabelPosition(pos);

    updateLyrics(pos);

    if (!ui->sliderPosition->isSliderDown()) // 鼠标未正在拖动滑块
        ui->sliderPosition->setSliderPosition(pos);
}

void MainWindow::do_durationChanged(qint64 duration)
{
    ui->sliderPosition->setMaximum(duration);
    m_duration = duration;
    int seconds = duration / 1000;
    ui->labelDuration->setText(QString::number(seconds / 60) +
                               ":" + QString::number(seconds % 60));
}

void MainWindow::do_songIdChanged(int songId)
{
    if (SONG_TABLEMODEL->currentPlaylistKind() == PlaylistKind::History) {
        SONG_TABLEMODEL->select();
    }

    QVariantMap songDetailsMap = DB->getSongDisplayDetails(songId);
    if (songDetailsMap.isEmpty())
        return;

    QString songTitle = songDetailsMap["title"].toString();
    QString songArtist = songDetailsMap["artist"].toString();

    // 设置"歌名-歌手显示"
    ui->labelTitle->setText(
        QString("<span style='margin:0; font-family:Microsoft YaHei; font-size:13px; color:#111111;'>%1-</span> "
                "<span style='margin:0; font-family:Microsoft YaHei; font-size:11px; color:#505050;'>%2</span>")
            .arg(songTitle, songArtist)
        );
    ui->labelListTitle->setToolTip(songDetailsMap["title"].toString());

    // 设置"喜欢"按钮
    int favoriteLabel = songDetailsMap["favorite"].toInt();
    QString iconPath = favoriteLabel ? Paths::LikeIcon : Paths::UnlikeIcon;
    QString tooltip = favoriteLabel ? "取消喜欢" : "喜欢";
    ui->btnFavoriteOne->setIcon(QIcon(iconPath));
    ui->btnFavoriteOne->setToolTip(tooltip);
    ui->btnFavoriteOne->setProperty("songId", songId);
    ui->btnFavoriteOne->setProperty("favorite", favoriteLabel);

    // 提取歌词
    parseLrcFile(songDetailsMap["lyric"].toString());
    ui->lyricsWidget->setLyrics(m_lyricMap, songTitle, songArtist);
    m_currentLyricKey = -1;
    m_currentLyricEnd = -1;
    m_currentSeconds = -1;

    if (!ui->btnFavoriteOne->isEnabled()) {
        ui->btnFavoriteOne->setEnabled(true);
        ui->btnMoreOne->setEnabled(true);
    }
}

void MainWindow::do_metaDataChanged(const QVariantMap &songDetailsMap)
{
    // 设置封面
    QIcon btnCoverIcon = ui->btnCover->icon();
    QImage coverImage = songDetailsMap["coverImage"].value<QImage>();
    QPixmap cover;
    if (coverImage.isNull()) {
        cover = QPixmap(Paths::DefaultCover);
        ui->lyricsWidget->coverDisk()->setCenterPixmap(cover);
        cover = ImageUtils::getRoundedPixmap(cover);
    } else {
        ui->lyricsWidget->coverDisk()->setCenterPixmap(QPixmap::fromImage(coverImage));
        cover = ImageUtils::getRoundedPixmap(coverImage);
    }

    btnCoverIcon.addPixmap(cover, QIcon::Normal, QIcon::Off);
    btnCoverIcon.addPixmap(cover, QIcon::Active, QIcon::Off);
    ui->btnCover->setIcon(btnCoverIcon);
}

void MainWindow::parseLrcFile(const QString &filePath)
{
    m_lyricMap.clear();
    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            // 提取时间戳和歌词,使用 static 声明正则表达式对象
            static const QRegularExpression regex(R"(\[(\d{2}):(\d{2})(?:\.(\d{2}))?\](.*))");
            QRegularExpressionMatch match = regex.match(line);
            if (match.hasMatch()) {
                int minutes = match.captured(1).toInt();
                int seconds = match.captured(2).toInt();
                QString lyric = match.captured(4);
                int timestamp = minutes * 60 * 1000 + seconds * 1000;  // 转换为毫秒
                m_lyricMap.insert(timestamp, lyric);
            }
        }
    }
}

void MainWindow::updateLabelPosition(qint64 pos)
{
    // 更新当前播放时间显示
    int seconds = pos / 1000;
    if (seconds != m_currentSeconds) {
        m_currentSeconds = seconds;
        ui->labelPosition->setText(QString("%1:%2")
                                       .arg(seconds / 60, 2, 10, QChar('0')) // 分钟，两位数，前导补零
                                       .arg(seconds % 60, 2, 10, QChar('0'))); // 秒钟，两位数，前导补零
    }
}

void MainWindow::actionSearch(const QString &text)
{
    if (text.isEmpty())
        return;

    do_exitBatchProcess();

    if (CATEGORY_LISTWIDGET->selectionModel()->hasSelection()) {
        CATEGORY_LISTWIDGET->m_currentRow = -1;
        CATEGORY_LISTWIDGET->clearSelection();
    }

    if (LISTWIDGET_MYMUSIC->selectionModel()->hasSelection()) {
        LISTWIDGET_MYMUSIC->setCurrentRow(-1);
        LISTWIDGET_MYMUSIC->clearSelection();
    }

    SONG_TABLEMODEL->updateTable(text, PlaylistKind::SearchList);

    ui->labelListTitle->setText("搜索结果");
}

void MainWindow::on_btnMoreOne_clicked()
{
    int songId = ui->btnFavoriteOne->property("songId").toInt();
    int favorite = ui->btnFavoriteOne->property("favorite").toInt();
    std::unique_ptr<MoreMenu> moreMenu(new MoreMenu(this, songId, favorite, PlaylistKind::PlayQueue, ui->labelPlaylist->toolTip()));
    moreMenu->exec(QCursor::pos());
}

void MainWindow::on_btnFavoriteOne_clicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        int songId = ui->btnFavoriteOne->property("songId").toInt();
        int favorite = 1 - ui->btnFavoriteOne->property("favorite").toInt();
        SONG_TABLEMODEL->changeFavorite(favorite, songId);
    }
}

void MainWindow::on_btnBatchPlay_clicked()
{
    SONG_TABLEMODEL->batchPlay(ui->btnBatchProcess->isVisible());
}

void MainWindow::on_btnRemoveBatch_clicked()
{
    SONG_TABLEMODEL->removeSelected(ui->labelListTitle->toolTip());
}

void MainWindow::do_listSelected(const QString &listName)
{
    // 更新当前播放列表名称

    // 最多显示6个字符
    if (listName.size() > 6) {
        QString temp = listName.left(6);
        temp.append("...");
        ui->labelListTitle->setText(temp);
    } else {
        ui->labelListTitle->setText(listName);
    }
    ui->labelListTitle->setToolTip(listName);
}

void MainWindow::do_favoriteChanged(int songId, int favorite)
{
    if (ui->btnFavoriteOne->property("songId").toInt() == songId) {
        if (favorite) {
            ui->btnFavoriteOne->setIcon(QIcon(Paths::LikeIcon));
        } else {
            ui->btnFavoriteOne->setIcon(QIcon(Paths::UnlikeIcon));
        }
        ui->btnFavoriteOne->setProperty("favorite", favorite);
    }
}

void MainWindow::do_exitBatchProcess()
{
    if (ui->btnExitBatch->isVisible()) {
        ui->btnBatchProcess->setVisible(true);
        ui->btnExitBatch->setVisible(false);
        ui->btnRemoveBatch->setVisible(false);
        ui->btnBatchAddTo->setVisible(false);
        SONG_TABLEVIEW->exitBatchProcess();
    }
}

void MainWindow::on_btnBatchProcess_clicked()
{
    if (SONG_TABLEVIEW->enterBatchProcess()) {
        ui->btnBatchProcess->setVisible(false);
        ui->btnExitBatch->setVisible(true);
        ui->btnRemoveBatch->setVisible(true);
        ui->btnBatchAddTo->setVisible(true);
    }
}

void MainWindow::on_btnVolume_clicked()
{
    // 当前音量值
    float rawVolume = PLAYER->audioOutput()->volume();
    rawVolume = qBound(0.0f, rawVolume, 1.0f); // 限制在合法范围内
    int volume = qRound(rawVolume * 100.0f); // 转换为 0-100 范围的整数

    // 音量控制界面
    VolumeControlWidget *volumeControlWidget =
        new VolumeControlWidget(nullptr, volume, PLAYER->audioOutput()->isMuted());

    connect(volumeControlWidget, &VolumeControlWidget::volumeChanged,
            PLAYER, &Player::do_volumeChanged);
    connect(volumeControlWidget, &VolumeControlWidget::mutedChanged,
            PLAYER, &Player::do_mutedChanged);
    connect(volumeControlWidget, &VolumeControlWidget::mutedChanged,
            this, &MainWindow::do_mutedChanged);

    // 设置音量控制界面显示位置
    QPoint globalPos = ui->btnVolume->mapToGlobal(QPoint(0, 0));
    int x = globalPos.x() - (volumeControlWidget->width() - ui->btnVolume->width()) / 2;
    int y = globalPos.y() - volumeControlWidget->height() - 2;
    volumeControlWidget->move(x, y);
    volumeControlWidget->show();
}

void MainWindow::do_mutedChanged(bool muted)
{
    // 更新音量按钮图标
    QIcon icon;
    if (muted) {
        icon.addFile(Paths::MuteIcon);
        ui->btnVolume->setIcon(icon);
    } else {
        icon.addFile(Paths::VolumeIcon);
        ui->btnVolume->setIcon(icon);
    }
}

void MainWindow::on_btnPlayMode_clicked()
{
    // 播放模式控制界面
    PlayModeControlWidget *playModeControlWidget = new PlayModeControlWidget(nullptr, PLAYER->playBackMode());
    connect(playModeControlWidget, &PlayModeControlWidget::playBackModeChanged,
            PLAYER, &Player::do_playModeChanged);
    connect(playModeControlWidget, &PlayModeControlWidget::playBackModeChanged,
            this, &MainWindow::do_playModeChanged);

    // 设置播放模式控制界面显示位置
    QPoint globalPos = ui->btnPlayMode->mapToGlobal(QPoint(0, 0));
    int x = globalPos.x() - (playModeControlWidget->width() - ui->btnPlayMode->width()) / 2;
    int y = globalPos.y() - playModeControlWidget->height() - 2;
    playModeControlWidget->move(x, y);
    playModeControlWidget->show();
}

void MainWindow::do_playModeChanged(Player::PlayBackMode playBackMode)
{
    // 更新播放模式按钮图标
    QIcon icon;
    switch (playBackMode) {
    case Player::Sequential: {
        icon.addFile(Paths::SequentialIcon);
        break;
    }
    case Player::LoopSequential: {
        icon.addFile(Paths::LoopSequentialIcon);
        break;
    }
    case Player::LoopSingle: {
        icon.addFile(Paths::LoopSingleIcon);
        break;
    }
    case Player::Random: {
        icon.addFile(Paths::RandomIcon);
        break;
    }
    }
    ui->btnPlayMode->setIcon(icon);
}

void MainWindow::on_btnNewCategory_clicked()
{
    CATEGORY_LISTWIDGET->createNewCategoryName();
}

void MainWindow::on_btnLyric_clicked()
{
    if (m_singleLyricWidget) { // 关闭单句歌词窗口
        delete m_singleLyricWidget;
        m_singleLyricWidget = nullptr;
        m_lyricMap.clear();
        m_currentLyricKey = -1;
        m_currentLyricEnd = -1;
        return;
    } else { // 打开单句歌词窗口
        m_singleLyricWidget = new SingleLyricWidget();

        // 设置歌词窗口位置到 MainWindow 所在屏幕的底部
        QScreen *screen = QGuiApplication::screenAt(this->mapToGlobal(QPoint(0, 0)));
        if (screen) {
            QRect screenGeometry = screen->geometry();
            int widgetX = screenGeometry.x()
                          + (screenGeometry.width() - m_singleLyricWidget->width()) / 2;
            int widgetY = screenGeometry.y()
                          + screenGeometry.height() - m_singleLyricWidget->height() - 20;
            m_singleLyricWidget->move(widgetX, widgetY);
        }

        m_singleLyricWidget->setLyricText(m_lyricMap.isEmpty() ? "当前歌曲无歌词文件" : m_lyricMap[m_currentLyricKey]);

        m_singleLyricWidget->show();

        connect(m_singleLyricWidget, &SingleLyricWidget::widgetClosed, this, [this] () {
            delete m_singleLyricWidget;
            m_singleLyricWidget = nullptr;
        });
    }
}

void MainWindow::updateLyrics(qint64 pos)
{
    if (m_lyricMap.isEmpty() || (pos >= m_currentLyricKey && pos < m_currentLyricEnd))
        return;

    nextLyricText(pos); // 更新当前歌词位置
    if (m_singleLyricWidget) {
        // 更新单句歌词显示窗口
        m_singleLyricWidget->setLyricText(m_lyricMap[m_currentLyricKey]);
    }
    if (ui->lyricsWidget->isVisible()) {
        // 更新歌曲详情界面中的歌词
        ui->lyricsWidget->updateLyrics(m_currentLyricKey);
    }
}

void MainWindow::nextLyricText(qint64 position)
{
    // 更新当前歌词位置
    auto it = m_lyricMap.upperBound(position);
    if (it == m_lyricMap.end()) {
        m_currentLyricEnd = m_duration;
    } else {
        m_currentLyricEnd = it.key();
    }
    m_currentLyricKey = (--it).key();
}

void MainWindow::on_btnCover_clicked(bool checked)
{
    if (checked) { // 显示歌曲详情界面
        ui->widgetTop->setVisible(!checked);
        ui->lyricsWidget->setVisible(checked);
        ui->lyricsWidget->updateLyrics(m_currentLyricKey);
        bool isPlaying = PLAYER->isPlaying();
        ui->lyricsWidget->coverDisk()->setPoleState(isPlaying);
        ui->lyricsWidget->coverDisk()->trogglePlay(isPlaying);
        ui->btnCover->setToolTip("关闭歌曲详情页");
    } else { // 隐藏歌曲详情界面
        ui->lyricsWidget->setVisible(checked);
        ui->widgetTop->setVisible(!checked);
        // 停止歌曲详情界面中黑胶唱片的动画
        ui->lyricsWidget->coverDisk()->trogglePlay(false);
        ui->btnCover->setToolTip("显示歌曲详情页");
    }
}

void MainWindow::on_btnImport_clicked()
{
    if (DB->insertSongsIntoSong())
        SONG_TABLEMODEL->select();
}

void MainWindow::initLayout()
{
    // 主界面播放列表布局
    QVBoxLayout *vLayoutPlaylist = new QVBoxLayout();
    vLayoutPlaylist->setSpacing(11); // 设置控件间距
    vLayoutPlaylist->addSpacing(10); // 添加上边距
    // "Panda音乐" 图标
    ui->labelPandamusic->setPixmap(
        QPixmap(":/cover/images/pandamusic_label.png")
            .scaledToWidth(120, Qt::SmoothTransformation)
        );
    vLayoutPlaylist->addWidget(ui->labelPandamusic);
    vLayoutPlaylist->addSpacing(20);
    // "我的音乐"标签
    vLayoutPlaylist->addWidget(ui->labelPlaylist);
    // "我的音乐"列表
    vLayoutPlaylist->addWidget(ListWidgetMyMusic::instance(this), 1);

    // "自建歌单"控制按钮布局
    QHBoxLayout *hLayoutCategory = new QHBoxLayout();
    // "自建歌单"标签
    hLayoutCategory->addWidget(ui->labelCategory);
    hLayoutCategory->addSpacing(10);
    // 新建歌单按钮
    hLayoutCategory->addWidget(ui->btnNewCategory);
    hLayoutCategory->addSpacerItem(
        new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum)
        );
    hLayoutCategory->setContentsMargins(0, 0, 0, 0); // 设置外边距
    vLayoutPlaylist->addLayout(hLayoutCategory);
    // "自建歌单"列表
    vLayoutPlaylist->addWidget(CategoryListWidget::instance(this), 1);
    ui->widgetList->setLayout(vLayoutPlaylist);

    // 歌曲具体信息表格
    ui->frameTable->layout()->addWidget(SongTableView::instance(this));

    // 设置部分按钮不可见
    ui->btnImport->setVisible(false); // 导入歌曲
    ui->btnExitBatch->setVisible(false); // 退出批量操作
    ui->btnRemoveBatch->setVisible(false); // 批量移除
    ui->btnBatchAddTo->setVisible(false); // 批量添加到
    // 设置当前播放歌曲相关的按钮不可见
    ui->btnFavoriteOne->setEnabled(false); // 喜欢
    ui->btnMoreOne->setEnabled(false); // 更多
    ui->btnComent->setEnabled(false); // 评论
    // 歌词界面不可见
    ui->lyricsWidget->setVisible(false);
}

void MainWindow::initCurrentSongDetails()
{
    // 封面按钮图标
    QIcon btnCoverIcon;
    // 添加封面按钮不同状态的图标
    // 正常状态，按钮处于“开启”状态
    btnCoverIcon.addFile(
        Paths::LyricHideIcon,
        QSize(), // 默认大小
        QIcon::Normal,
        QIcon::On
        );
    // 激活状态，按钮处于“关闭”状态
    QPixmap pixmapCover = ImageUtils::getRoundedPixmap(
        Paths::DefaultCover, 56, 56
        );
    btnCoverIcon.addPixmap(
        pixmapCover,
        QIcon::Active,
        QIcon::Off
        );
    // 正常状态，按钮处于“关闭”状态
    btnCoverIcon.addPixmap(
        pixmapCover,
        QIcon::Normal,
        QIcon::Off
        );
    ui->btnCover->setIcon(btnCoverIcon);
    ui->btnCover->setToolTip("显示歌曲详情页");

    // 设置"歌名-歌手"标签
    QString htmlString = "<span style='margin:0; font-family:Microsoft YaHei; font-size:13px; color:#111111;'>Panda音乐-</span> "
                         "<span style='margin:0; font-family:Microsoft YaHei; font-size:11px; color:#505050;'>听我想听</span>";
    ui->labelTitle->setText(htmlString);

    // 设置歌曲详情界面
    // 设置黑胶唱片中心图片
    ui->lyricsWidget->
        coverDisk()->
        setCenterPixmap(Paths::DefaultCover);
    // 设置歌曲详情界面歌词
    ui->lyricsWidget->setLyrics(
        {
            {0, ""},
            {1, ""},
            {2, "Panda音乐 听我想听"}
        },
        QString(),
        QString()
        );
}

void MainWindow::initPlayerModule()
{
    // 播放器加载"播放队列"歌曲
    PLAYER->initPlaylist(DB->selectSongIdFromPlaylist());

    // 前一首、播放、下一首按钮
    connect(ui->btnPrevious, &QPushButton::clicked,
            PLAYER, &Player::previous);
    connect(ui->btnNext, &QPushButton::clicked,
            PLAYER, &Player::next);

    // 时长
    connect(PLAYER->mediaPlayer(), &QMediaPlayer::durationChanged,
            this, &MainWindow::do_durationChanged);
    // 播放进度
    connect(PLAYER->mediaPlayer(), &QMediaPlayer::positionChanged,
            this, &MainWindow::do_positionChanged);
    // 播放进度
    connect(ui->sliderPosition, &QSlider::valueChanged, this, [this] (int value) {
        disconnect(PLAYER->mediaPlayer(), &QMediaPlayer::positionChanged,
                   this, &MainWindow::do_positionChanged);
        updateLabelPosition(value);
        updateLyrics(value);
        PLAYER->setPosition(value);
        connect(PLAYER->mediaPlayer(), &QMediaPlayer::positionChanged,
                this, &MainWindow::do_positionChanged);
    });

    // 播放状态
    connect(PLAYER->mediaPlayer(), &QMediaPlayer::playbackStateChanged,
            this, &MainWindow::do_playbackStateChanged);

    // 当前播放歌曲id发生改变
    connect(PLAYER, &Player::songIdChanged,
            this, &MainWindow::do_songIdChanged);
    // 当前播放歌曲元信息发生改变
    connect(PLAYER, &Player::metaDataChanged,
            this, &MainWindow::do_metaDataChanged);
}

void MainWindow::initMyMusicList()
{
    connect(LISTWIDGET_MYMUSIC, &ListWidgetMyMusic::listSelected,
            this, &MainWindow::do_listSelected);
    connect(LISTWIDGET_MYMUSIC, &ListWidgetMyMusic::exitBatchProcess,
            this, &MainWindow::do_exitBatchProcess);

    // "我的音乐"列表当前选中为"播放队列"
    LISTWIDGET_MYMUSIC->setCurrentRow(1);
}

void MainWindow::initSearchLineEdit()
{
    // 搜索按钮
    QAction *searchAction = new QAction(this);
    searchAction->setToolTip("搜索");
    searchAction->setIcon(QIcon(Paths::SearchIcon));
    // 将搜索按钮添加到搜索框中
    ui->lineEditSearch->addAction(searchAction, QLineEdit::TrailingPosition);

    ui->lineEditSearch->setPlaceholderText("搜索");
    ui->lineEditSearch->setFocusPolicy(Qt::ClickFocus);
    this->setFocusPolicy(Qt::ClickFocus);
    connect(searchAction, &QAction::triggered, this, [this] {
        actionSearch(ui->lineEditSearch->text().trimmed());
    });
    connect(ui->lineEditSearch, &QLineEdit::returnPressed, this, [this] {
        actionSearch(ui->lineEditSearch->text().trimmed());
    });
}

void MainWindow::on_btnExitBatch_clicked()
{
    ui->btnBatchProcess->setVisible(true);
    ui->btnExitBatch->setVisible(false);
    ui->btnRemoveBatch->setVisible(false);
    ui->btnBatchAddTo->setVisible(false);
    SONG_TABLEVIEW->exitBatchProcess();
}

void MainWindow::on_btnBatchAddTo_clicked()
{
    QVector<int> songIdVector = SONG_TABLEMODEL->selectedSongIds();
    std::unique_ptr<BatchAddToMenu> batchAddToMenu(
        new BatchAddToMenu(this
                           , songIdVector
                           , ui->labelListTitle->toolTip()
                           , SONG_TABLEMODEL->currentPlaylistKind())
        );
    batchAddToMenu->exec(QCursor::pos());
}
