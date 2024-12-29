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
#include "myMenu/moremenu.h"
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

    // 播放列表
    QVBoxLayout *vLayoutPlaylist = new QVBoxLayout();
    vLayoutPlaylist->setSpacing(11);
    ui->labelPandamusic->setPixmap(QPixmap(":/cover/images/pandamusic_label.png")
                                       .scaledToWidth(120, Qt::SmoothTransformation));
    vLayoutPlaylist->addSpacing(10);
    vLayoutPlaylist->addWidget(ui->labelPandamusic);
    vLayoutPlaylist->addSpacing(20);
    vLayoutPlaylist->addWidget(ui->labelPlaylist);
    vLayoutPlaylist->addWidget(PlayListWidget::instance(this));

    // 自建歌单列表
    QHBoxLayout *hLayoutCategory = new QHBoxLayout();
    hLayoutCategory->addWidget(ui->labelCategory);
    hLayoutCategory->addSpacing(10);
    hLayoutCategory->addWidget(ui->btnNewCategory);
    hLayoutCategory->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hLayoutCategory->setContentsMargins(0, 0, 0, 0);

    vLayoutPlaylist->addLayout(hLayoutCategory);
    vLayoutPlaylist->addWidget(CategoryListWidget::instance(this), 1);
    ui->widgetList->setLayout(vLayoutPlaylist);

    // 歌曲具体信息表格
    ui->frameTable->layout()->addWidget(SongTableView::instance(this));
    PLAY_LISTWIDGET->setCurrentRow(1);

    // 初始化播放列表
    PLAYER->initPlaylist(DB->selectSongIdFromPlaylist());

    // 退出批量操作、批量删除不可见
    ui->btnImport->setVisible(false);
    ui->btnExitBatch->setVisible(false);
    ui->btnRemoveBatch->setVisible(false);

    // 歌词界面不可见
    ui->lyricsWidget->setVisible(false);

    // 设置显示歌曲封面的labelCover
    QIcon btnCoverIcon;
    btnCoverIcon.addFile(":/icons/images/lyric_hide.png", QSize(), QIcon::Normal, QIcon::On);
    QPixmap pixmapCover = ImageUtils::getRoundedPixmap(m_pathCover, 56, 56);
    btnCoverIcon.addPixmap(pixmapCover, QIcon::Active, QIcon::Off);
    btnCoverIcon.addPixmap(pixmapCover, QIcon::Normal, QIcon::Off);
    ui->btnCover->setIcon(btnCoverIcon);
    ui->btnCover->setToolTip("显示歌曲详情页");
    // 设置歌词界面
    ui->lyricsWidget->coverDisk()->setCenterPixmap(m_pathCover);
    ui->lyricsWidget->setLyrics(
        {
            {0, ""},
            {1, ""},
            {2, "Panda音乐 听我想听"}
        },
        QString(),
        QString()
        );
    // 显示当前播放歌曲信息
    QString htmlString = "<span style='margin:0; font-family:Microsoft YaHei; font-size:13px; color:#111111;'>Panda音乐-</span> "
                         "<span style='margin:0; font-family:Microsoft YaHei; font-size:11px; color:#505050;'>听我想听</span>";
    ui->labelTitle->setText(htmlString);


    connect(ui->btnPrevious, &QPushButton::clicked,
            PLAYER, &Player::previous);
    connect(ui->btnNext, &QPushButton::clicked,
            PLAYER, &Player::next);
    connect(PLAYER->mediaPlayer(), &QMediaPlayer::durationChanged,
            this, &MainWindow::do_durationChanged);
    connect(ui->sliderPosition, &QSlider::valueChanged, this, [this] (int value) {
        disconnect(PLAYER->mediaPlayer(), &QMediaPlayer::positionChanged,
                   this, &MainWindow::do_positionChanged);
        updateLabelPosition(value);
        updateLyrics(value);
        PLAYER->setPosition(value);
        connect(PLAYER->mediaPlayer(), &QMediaPlayer::positionChanged,
                this, &MainWindow::do_positionChanged);
    });
    connect(PLAYER->mediaPlayer(), &QMediaPlayer::playbackStateChanged,
            this, &MainWindow::do_playbackStateChanged);
    connect(PLAYER->mediaPlayer(), &QMediaPlayer::positionChanged,
            this, &MainWindow::do_positionChanged);
    connect(PLAYER, &Player::songIdChanged,
            this, &MainWindow::do_songIdChanged);
    // connect(SONG_TABLEWIDGET, &SongTableWidget::favoriteChanged
    //         , this, &MainWindow::do_favoriteChanged);
    connect(CATEGORY_ListWIDGET, &CategoryListWidget::listSelected,
            this, &MainWindow::do_listSelected);
    connect(PLAY_LISTWIDGET, &PlayListWidget::listSelected,
            this, &MainWindow::do_listSelected);
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
    QIcon icon;
    if (state == QMediaPlayer::PlayingState) {
        icon.addFile(m_pathPauseIcon);
        ui->btnPlay->setIcon(icon);
        ui->btnPlay->setToolTip("暂停");
        if (ui->lyricsWidget->isVisible())
            ui->lyricsWidget->coverDisk()->trogglePlay(true);
    } else {
        icon.addFile(m_pathPlayIcon);
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
    QVariantMap songDetailsMap = DB->getSongDisplayDetails(songId);
    QString songTitle = songDetailsMap["title"].toString();
    QString songArtist = songDetailsMap["artist"].toString();

    // 设置"歌名-歌手显示"
    ui->labelTitle->setText(
        QString("<span style='margin:0; font-family:Microsoft YaHei; font-size:13px; color:#111111;'>%1-</span> "
                "<span style='margin:0; font-family:Microsoft YaHei; font-size:11px; color:#505050;'>%2</span>")
            .arg(songTitle, songArtist)
        );
    ui->labelListTitle->setToolTip(songDetailsMap["title"].toString());

    // 设置封面
    QIcon btnCoverIcon = ui->btnCover->icon();
    QPixmap cover = ImageUtils::getRoundedPixmap(songDetailsMap["cover"].toString(), 56, 56);
    if (cover.isNull()) {
        cover = ImageUtils::getRoundedPixmap(m_pathCover, 56, 56);
    }
    btnCoverIcon.addPixmap(cover, QIcon::Normal, QIcon::Off);
    btnCoverIcon.addPixmap(cover, QIcon::Active, QIcon::Off);
    ui->btnCover->setIcon(btnCoverIcon);

    // 设置"喜欢"按钮
    int favoriteLabel = songDetailsMap["favorite"].toInt();
    if (favoriteLabel != -1) {
        QString iconPath = favoriteLabel ? m_pathLikeIcon : m_pathUnlikeIcon;
        QString tooltip = favoriteLabel ? "取消喜欢" : "喜欢";
        ui->btnFavoriteOne->setIcon(QIcon(iconPath));
        ui->btnFavoriteOne->setToolTip(tooltip);
        ui->btnFavoriteOne->setProperty("songId", songId);
        ui->btnFavoriteOne->setProperty("favorite", favoriteLabel);
    }

    // 提取歌词
    parseLrcFile(songDetailsMap["lyric"].toString());
    ui->lyricsWidget->setLyrics(m_lyricMap, songTitle, songArtist);
    ui->lyricsWidget->coverDisk()->setCenterPixmap(DB->getSongCoverPath(songId));
    m_currentLyricKey = -1;
    m_currentLyricEnd = -1;
    m_currentSeconds = -1;
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
    int seconds = pos / 1000;
    if (seconds != m_currentSeconds) {
        m_currentSeconds = seconds;
        ui->labelPosition->setText(QString("%1:%2")
                                       .arg(seconds / 60, 2, 10, QChar('0')) // 分钟，两位数，前导补零
                                       .arg(seconds % 60, 2, 10, QChar('0'))); // 秒钟，两位数，前导补零
    }
}

void MainWindow::on_btnMoreOne_clicked()
{
    int songId = ui->btnFavoriteOne->property("songId").toInt();
    int favorite = ui->btnFavoriteOne->property("favorite").toInt();
    std::unique_ptr<MoreMenu> moreMenu(new MoreMenu(this, songId, favorite));
    moreMenu->exec(QCursor::pos());
}

void MainWindow::on_btnFavoriteOne_clicked()
{
    // QPushButton *button = qobject_cast<QPushButton *>(sender());
    // if (button) {
    //     int songId = ui->btnFavoriteOne->property("songId").toInt();
    //     int favorite = 1 - ui->btnFavoriteOne->property("favorite").toInt();
    //     SONG_TABLEWIDGET->changeFavorite(favorite, songId);
    // }
}

void MainWindow::on_btnBatchPlay_clicked()
{
    SONG_TABLEMODEL->batchPlay(ui->btnBatchProcess->isVisible());
}

void MainWindow::on_btnRemoveBatch_clicked()
{
    SONG_TABLEMODEL->removeSelected(ui->labelListTitle->toolTip(), PLAY_LISTWIDGET->currentPlaylistKind());
}

void MainWindow::do_listSelected(const QString &listName)
{
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
            ui->btnFavoriteOne->setIcon(QIcon(m_pathLikeIcon));
        } else {
            ui->btnFavoriteOne->setIcon(QIcon(m_pathUnlikeIcon));
        }
        ui->btnFavoriteOne->setProperty("favorite", favorite);
    }
}

void MainWindow::on_btnBatchProcess_clicked()
{
    if (SONG_TABLEVIEW->enterBatchProcess()) {
        ui->btnBatchProcess->setVisible(false);
        ui->btnExitBatch->setVisible(true);
        ui->btnRemoveBatch->setVisible(true);
    }
}

void MainWindow::on_btnVolume_clicked()
{
    float rawVolume = PLAYER->audioOutput()->volume();
    rawVolume = qBound(0.0f, rawVolume, 1.0f); // 限制在合法范围内
    int volume = qRound(rawVolume * 100.0f);
    VolumeControlWidget *volumeControlWidget =
        new VolumeControlWidget(nullptr, volume, PLAYER->audioOutput()->isMuted());
    connect(volumeControlWidget, &VolumeControlWidget::volumeChanged,
            PLAYER, &Player::do_volumeChanged);
    connect(volumeControlWidget, &VolumeControlWidget::mutedChanged,
            PLAYER, &Player::do_mutedChanged);
    connect(volumeControlWidget, &VolumeControlWidget::mutedChanged,
            this, &MainWindow::do_mutedChanged);

    QPoint globalPos = ui->btnVolume->mapToGlobal(QPoint(0, 0));
    int x = globalPos.x() - (volumeControlWidget->width() - ui->btnVolume->width()) / 2;
    int y = globalPos.y() - volumeControlWidget->height() - 2;

    volumeControlWidget->move(x, y);
    volumeControlWidget->show();
}

void MainWindow::do_mutedChanged(bool muted)
{
    QIcon icon;
    if (muted) {
        icon.addFile(":/icons/images/mute.png");
        ui->btnVolume->setIcon(icon);
    } else {
        icon.addFile(":/icons/images/volume.png");
        ui->btnVolume->setIcon(icon);
    }
}

void MainWindow::on_btnPlayMode_clicked()
{
    PlayModeControlWidget *playModeControlWidget = new PlayModeControlWidget(nullptr, PLAYER->playBackMode());
    connect(playModeControlWidget, &PlayModeControlWidget::playBackModeChanged,
            PLAYER, &Player::do_playModeChanged);
    connect(playModeControlWidget, &PlayModeControlWidget::playBackModeChanged,
            this, &MainWindow::do_playModeChanged);
    QPoint globalPos = ui->btnPlayMode->mapToGlobal(QPoint(0, 0));
    int x = globalPos.x() - (playModeControlWidget->width() - ui->btnPlayMode->width()) / 2;
    int y = globalPos.y() - playModeControlWidget->height() - 2;
    playModeControlWidget->move(x, y);
    playModeControlWidget->show();
}

void MainWindow::do_playModeChanged(Player::PlayBackMode playBackMode)
{
    QIcon icon;
    switch (playBackMode) {
    case Player::Sequential: {
        icon.addFile(":/icons/images/sequential.png");
        break;
    }
    case Player::LoopSequential: {
        icon.addFile(":/icons/images/loopSequential.png");
        break;
    }
    case Player::LoopSingle: {
        icon.addFile(":/icons/images/loopSingle.png");
        break;
    }
    case Player::Random: {
        icon.addFile(":/icons/images/random.png");
        break;
    }
    }
    ui->btnPlayMode->setIcon(icon);
}

void MainWindow::on_btnNewCategory_clicked()
{
    CATEGORY_ListWIDGET->createNewCategoryName();
}

void MainWindow::on_btnLyric_clicked()
{
    if (m_singleLyricWidget) {
        delete m_singleLyricWidget;
        m_singleLyricWidget = nullptr;
        m_lyricMap.clear();
        m_currentLyricKey = -1;
        m_currentLyricEnd = -1;
        return;
    } else {
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
        m_singleLyricWidget->setLyricText(m_lyricMap[m_currentLyricKey]);
    }
    if (ui->lyricsWidget->isVisible()) {
        ui->lyricsWidget->updateLyrics(m_currentLyricKey);
    }
}

void MainWindow::nextLyricText(qint64 position)
{
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
    if (checked) {
        ui->widgetTop->setVisible(!checked);
        ui->lyricsWidget->setVisible(checked);
        ui->lyricsWidget->updateLyrics(m_currentLyricKey);
        bool isPlaying = PLAYER->isPlaying();
        ui->lyricsWidget->coverDisk()->setPoleState(isPlaying);
        ui->lyricsWidget->coverDisk()->trogglePlay(isPlaying);
        ui->btnCover->setToolTip("关闭歌曲详情页");
    } else {
        ui->lyricsWidget->setVisible(checked);
        ui->widgetTop->setVisible(!checked);
        ui->lyricsWidget->coverDisk()->trogglePlay(false);
        ui->btnCover->setToolTip("显示歌曲详情页");
    }
}


void MainWindow::on_btnImport_clicked()
{
    if (DB->insertSongsIntoSong())
        SONG_TABLEMODEL->select();
}


void MainWindow::on_btnExitBatch_clicked()
{
    ui->btnBatchProcess->setVisible(true);
    ui->btnExitBatch->setVisible(false);
    ui->btnRemoveBatch->setVisible(false);
    SONG_TABLEVIEW->exitBatchProcess();
}

