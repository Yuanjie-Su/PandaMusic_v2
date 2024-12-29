#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

#define PLAYER Player::instance()

class QAudioOutput;
class QMediaPlayer;
class Playlist;
class Player : public QObject {
    Q_OBJECT

public:
    explicit Player(QObject *parent = nullptr);

    enum PlayBackMode {
        Sequential = 0,
        LoopSequential,
        LoopSingle,
        Random,
    };

    static Player *instance();

    QMediaPlayer *mediaPlayer() { return m_player; }
    QAudioOutput *audioOutput() { return m_output; }
    PlayBackMode playBackMode() { return m_playBackMode; }

    void addSong(int);
    void initPlaylist(const QVector<int> &);
    void removeSong(int);
    bool isPlaying();
    bool isInPlaylist(int);

    bool play();
    void play(int);
    void play(const QVector<int> &);
    void playByIndex(int);
    void playNext(int);
    void pause();
    void stop();

private:
    void setCurrentPlay(QVariantMap &);
    void updateIndex(int);

signals:
    void songIdChanged(int);
    void playListIsEmpty();

public slots:
    void previous();
    void next();
    void setPosition(int);
    void do_volumeChanged(float);
    void do_mutedChanged(bool);
    void do_playModeChanged(PlayBackMode);

private slots:
    void do_mediaStatusChanged(QMediaPlayer::MediaStatus);
    void do_sourceChanged(const QUrl &);

private:
    QAudioOutput *m_output = nullptr;
    QMediaPlayer *m_player = nullptr;

    PlayBackMode m_playBackMode = Sequential;
    QVector<int> m_songIdVector;
    int m_cureentIndex = -1;
    int m_nextIndex = -1;
};
