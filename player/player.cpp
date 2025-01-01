#include "player.h"
#include "database\database.h"

#include <QDebug>
#include <QGlobalStatic>
#include <QMediaMetaData>
#include <QRandomGenerator>
#include <QImage>

Q_GLOBAL_STATIC(Player, player)

Player::Player(QObject *parent) : QObject{parent} {
    m_output = new QAudioOutput(this);
    m_player = new QMediaPlayer(this);
    m_player->setAudioOutput(m_output);

    connect(m_player, &QMediaPlayer::mediaStatusChanged,
            this, &Player::do_mediaStatusChanged);

    connect(m_player, &QMediaPlayer::sourceChanged,
            this, &Player::do_sourceChanged);

    connect(m_player, &QMediaPlayer::metaDataChanged,
            this, &Player::do_metaDataChanged);
}

Player *Player::instance() { return player; }

void Player::addSong(int songId)
{
    if (m_songIdVector.contains(songId))
        return;

    DB->insertSongIntoPlaylist(songId);
    m_songIdVector.append(songId);
}

void Player::addSong(const QVector<int> &songIdVector)
{
    for (int songId : songIdVector) {
        if (!m_songIdVector.contains(songId)) {
            m_songIdVector.append(songId);
            DB->insertSongIntoPlaylist(songId);
        }
    }
}

void Player::initPlaylist(const QVector<int> &songIdVector)
{
    m_songIdVector = songIdVector;
}

void Player::removeSong(int songId)
{
    DB->deleteSongFromPlaylist(songId);
    int currentSongId
        = m_currentIndex == -1 ? -1 : m_songIdVector[m_currentIndex];
    int nextSongId
        = m_nextIndex == -1 ? -1 : m_songIdVector[m_nextIndex];
    int index = m_songIdVector.indexOf(songId);
    if (index != -1) {
        m_songIdVector.removeAt(index);
        if (m_songIdVector.isEmpty()) {
            m_player->stop();
            m_currentIndex = -1;
            m_nextIndex = -1;
            emit playListIsEmpty();
        } else {
            int currentIndex =  m_songIdVector.indexOf(currentSongId);
            if (currentIndex == -1) {
                int nextIndex = m_songIdVector.indexOf(nextSongId);
                m_currentIndex = nextIndex == -1 ? 0 : nextIndex;
                playByIndex(m_currentIndex);
                m_nextIndex = -1;
            } else {
                int nextIndex = m_songIdVector.indexOf(nextSongId);
                if (nextIndex != -1)
                    m_nextIndex = nextIndex;
            }
        }
    }
}

void Player::removeSongs(const QVector<int> &songIdVector)
{
    DB->deleteSongsFromPlaylist(songIdVector);
    int currentSongId
        = m_currentIndex == -1 ? -1 : m_songIdVector[m_currentIndex];
    int nextSongId
        = m_nextIndex == -1 ? -1 : m_songIdVector[m_nextIndex];
    for (int songId : songIdVector) {
        int index = m_songIdVector.indexOf(songId);
        if (index != -1) {
            m_songIdVector.removeAt(index);
        }
    }
    if (m_songIdVector.isEmpty()) {
        m_player->stop();
        m_currentIndex = -1;
        m_nextIndex = -1;
        emit playListIsEmpty();
    } else {
        int currentIndex =  m_songIdVector.indexOf(currentSongId);
        if (currentIndex == -1) {
            int nextIndex = m_songIdVector.indexOf(nextSongId);
            m_currentIndex = nextIndex == -1 ? 0 : nextIndex;
            playByIndex(m_currentIndex);
            m_nextIndex = -1;
        } else {
            int nextIndex = m_songIdVector.indexOf(nextSongId);
            if (nextIndex != -1)
                m_nextIndex = nextIndex;
        }
    }
}

bool Player::isPlaying() {
    return m_player->playbackState() ==
           QMediaPlayer::PlayingState;
}

bool Player::isInPlaylist(int songId)
{
    return m_songIdVector.contains(songId);
}

bool Player::play() {
    if (m_player->mediaStatus() == QMediaPlayer::NoMedia) {
        if (m_songIdVector.size()) {
            if (m_nextIndex != -1)
                m_nextIndex = -1;

            m_currentIndex = 0;
            playByIndex(m_currentIndex);
            return true;
        }
    } else {
        m_player->play();
        return true;
    }
    return false;
}

void Player::play(int songId) {
    int index = m_songIdVector.indexOf(songId);
    if (index == -1) {
        m_songIdVector.append(songId);
        DB->insertSongIntoPlaylist(songId);
        index = m_songIdVector.size() - 1;
    }
    m_currentIndex = index;
    playByIndex(m_currentIndex);
}

void Player::play(const QVector<int> &songIdVector)
{
    if (!m_songIdVector.isEmpty())
        DB->deleteSongsFromPlaylist(m_songIdVector);

    m_songIdVector = songIdVector;
    DB->insertSongsIntoPlaylist(songIdVector);
    m_currentIndex = 0;
    playByIndex(m_currentIndex);
}

void Player::playByIndex(int index)
{
    if (index < 0 || index >= m_songIdVector.size()) {
        qCritical() << "Invalid index";
        return;
    }

    QString path = DB->getSongPath(m_songIdVector[index]);
    if (path.isEmpty()) {
        qCritical() << "Song path is empty for song ID:" << m_songIdVector[index];
        return;
    }

    QUrl url = QUrl::fromLocalFile(path);
    if (!url.isValid() || url.isEmpty()) {
        qCritical() << "Invalid URL for song path:" << path;
        return;
    }

    m_player->setSource(url);
    m_player->play();
}

void Player::playNext(int songId)
{
    int index = m_songIdVector.indexOf(songId);
    if (index == -1) {
        m_songIdVector.append(songId);
        index = m_songIdVector.size() - 1;
    }
    m_nextIndex = index;
}

void Player::pause()
{
    m_player->pause();
}

void Player::stop()
{
    m_player->stop();
}

void Player::updateIndex(int direction)
{
    int size = m_songIdVector.size();
    switch (m_playBackMode) {
    case LoopSingle:
        break;
    case Random:
        m_currentIndex =
            (m_currentIndex + QRandomGenerator::global()->bounded(size)) % size;
        break;
    default:
        m_currentIndex += direction;
        if (m_currentIndex < 0) m_currentIndex = size - 1;
        m_currentIndex %= size;
        break;
    }
}

void Player::previous() {
    updateIndex(-1);
    playByIndex(m_currentIndex);
}

void Player::next() {
    if (m_nextIndex != -1) {
        m_currentIndex = m_nextIndex;
        m_nextIndex = -1;
    } else {
        updateIndex(1);
    }

    playByIndex(m_currentIndex);
}

void Player::setPosition(int value)
{
    m_player->setPosition(value);
}

void Player::do_volumeChanged(float volume)
{
    m_output->setVolume(volume);
}

void Player::do_mutedChanged(bool muted)
{
    m_output->setMuted(muted);
}

void Player::do_playModeChanged(PlayBackMode playBackMode)
{
    m_playBackMode = playBackMode;
}

void Player::do_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        if (m_nextIndex != -1) {
            m_currentIndex = m_nextIndex;
            m_nextIndex = -1;
        } else {
            updateIndex(1);
            if (m_playBackMode == PlayBackMode::Sequential && m_currentIndex == 0) {
                m_currentIndex = m_songIdVector.size() - 1;
                return;
            }
        }
        playByIndex(m_currentIndex);
    }
}

void Player::do_sourceChanged(const QUrl &media)
{
    Q_UNUSED(media);
    int songId = m_songIdVector[m_currentIndex];
    DB->insertSongIntoHistory(songId);
    emit songIdChanged(songId);
}

void Player::do_metaDataChanged()
{
    QVariantMap songDetails;
    QMediaMetaData metaData = m_player->metaData();
    // songDetails["songId"] = m_songIdVector[m_cureentIndex];
    // songDetails["title"] = metaData.value(QMediaMetaData::Title).toString();
    // songDetails["artist"] = metaData.value(QMediaMetaData::Author).toString();
    QVariant cover = metaData.value(QMediaMetaData::ThumbnailImage);
    if (cover.isValid()) {
        songDetails["coverImage"] = cover.value<QImage>();
    } else {
        songDetails["coverImage"] = QImage();
    }
    emit metaDataChanged(songDetails);
}
