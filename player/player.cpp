#include "player.h"
#include "database\database.h"

#include <QDebug>
#include <QGlobalStatic>
#include <QMediaMetaData>
#include <QRandomGenerator>

Q_GLOBAL_STATIC(Player, player)

Player::Player(QObject *parent) : QObject{parent} {
    m_output = new QAudioOutput(this);
    m_player = new QMediaPlayer(this);
    m_player->setAudioOutput(m_output);

    connect(m_player, &QMediaPlayer::mediaStatusChanged,
            this, &Player::do_mediaStatusChanged);

    connect(m_player, &QMediaPlayer::sourceChanged,
            this, &Player::do_sourceChanged);
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
    DB->deleteSongFromHistory(songId);
    int index = m_songIdVector.indexOf(songId);
    if (index != -1) {
        m_songIdVector.removeAt(index);
        if (m_songIdVector.isEmpty()) {
            m_player->stop();
            m_cureentIndex = -1;
            m_nextIndex = -1;
            emit playListIsEmpty();
            return;
        }

        // 更新索引
        if (index < m_cureentIndex) {
            --m_cureentIndex;
        } else if (index == m_cureentIndex) {
            if (m_cureentIndex >= m_songIdVector.size()) {
                m_cureentIndex = m_songIdVector.size() - 1;
            }
            playByIndex(m_cureentIndex);
        }

        // 更新下一首歌曲的索引
        if (index == m_nextIndex || m_nextIndex >= m_songIdVector.size()) {
            m_nextIndex = -1;
        } else if (index < m_nextIndex) {
            --m_nextIndex;
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

            m_cureentIndex = 0;
            playByIndex(m_cureentIndex);
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
    m_cureentIndex = index;
    playByIndex(m_cureentIndex);
}

void Player::play(const QVector<int> &songIdVector)
{
    if (!m_songIdVector.isEmpty())
        DB->deleteSongsFromPlaylist(m_songIdVector);

    m_songIdVector = songIdVector;
    DB->insertSongsIntoPlaylist(songIdVector);
    m_cureentIndex = 0;
    playByIndex(m_cureentIndex);
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
        m_cureentIndex =
            (m_cureentIndex + QRandomGenerator::global()->bounded(size)) % size;
        break;
    default:
        m_cureentIndex += direction;
        if (m_cureentIndex < 0) m_cureentIndex = size - 1;
        m_cureentIndex %= size;
        break;
    }
}

void Player::previous() {
    updateIndex(-1);
    playByIndex(m_cureentIndex);
}

void Player::next() {
    if (m_nextIndex != -1) {
        m_cureentIndex = m_nextIndex;
        m_nextIndex = -1;
    } else {
        updateIndex(1);
    }

    playByIndex(m_cureentIndex);
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
            m_cureentIndex = m_nextIndex;
            m_nextIndex = -1;
        } else {
            updateIndex(1);
            if (m_playBackMode == PlayBackMode::Sequential && m_cureentIndex == 0) {
                m_cureentIndex = m_songIdVector.size() - 1;
                return;
            }
        }
        playByIndex(m_cureentIndex);
    }
}

void Player::do_sourceChanged(const QUrl &media)
{
    Q_UNUSED(media);
    int songId = m_songIdVector[m_cureentIndex];
    DB->insertSongIntoHistory(songId);
    emit songIdChanged(songId);
}
