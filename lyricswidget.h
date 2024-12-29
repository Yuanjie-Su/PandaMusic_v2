#ifndef LYRICSWIDGET_H
#define LYRICSWIDGET_H

#include "trotatedlabel.h"

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QTimer>

class LyricsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LyricsWidget(QWidget *parent = nullptr);

    void updateLyrics(int key); // 更新高亮歌词
    void setLyrics(const QMap<int, QString> &lyrics
                   , const QString &title
                   , const QString &artist);
    TRotatedLabel *coverDisk() const { return m_coverDisk; }

private:
    TRotatedLabel *m_coverDisk;  // 模拟唱片的控件
    QListWidget *m_lyricsList;  // 显示歌词的列表
    QLabel *m_titleArtist;  // 显示歌名歌手的标签

    QVector<int> m_lyricTimeVector;  // 歌词时间戳
};

#endif // LYRICSWIDGET_H
