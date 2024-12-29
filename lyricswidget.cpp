#include "LyricsWidget.h"

#include <QScrollBar>

LyricsWidget::LyricsWidget(QWidget *parent)
    : QWidget(parent)
{
    m_coverDisk = new TRotatedLabel(this);
    m_coverDisk->setMinimumSize(300, 300);
    m_coverDisk->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_titleArtist = new QLabel(this);
    m_titleArtist->setTextFormat(Qt::RichText);
    m_titleArtist->setFixedHeight(60);
    m_titleArtist->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_titleArtist->setStyleSheet("padding-left: 5px;");

    m_lyricsList = new QListWidget(this);
    m_lyricsList->setStyleSheet(
        "QListWidget { "
        "background: transparent;"
        "border: none; "
        "font-family: Microsoft YaHei;"
        "font-size: 13pt;"
        "font-weight: 650;"
        "color: rgb(80,80,80);"
        "}"
        "QListWidget::item:selected { "
        "background: transparent; "
        "color: #00F268; "
        "}"
        "QListWidget::item:hover {"
        "    background: transparent;"  // 禁用背景色变更
        "    color: inherit;"  // 保持字体颜色不变
        "}"
        );
    m_lyricsList->setVerticalScrollMode(QListWidget::ScrollPerPixel);
    m_lyricsList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  // 隐藏竖向滚动条
    m_lyricsList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  // 隐藏横向滚动条
    m_lyricsList->setFocusPolicy(Qt::NoFocus); // 禁止焦点
    m_lyricsList->setEnabled(false); // 禁用用户交互
    m_lyricsList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_lyricsList->setSpacing(4);

    // vLayoutCover 布局，用于封面
    QVBoxLayout* vLayoutCover = new QVBoxLayout;
    vLayoutCover->addStretch(1);
    vLayoutCover->addWidget(m_coverDisk,2);
    vLayoutCover->addStretch(1);

    // vLayoutLyrics 布局，用于歌词和标题
    QVBoxLayout* vLayoutLyrics = new QVBoxLayout;
    vLayoutLyrics->addStretch(1);
    vLayoutLyrics->addWidget(m_titleArtist);
    vLayoutLyrics->addWidget(m_lyricsList, 4);
    vLayoutLyrics->addStretch(1);

    // hLayout 布局，水平排列封面和歌词
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addStretch(2);
    hLayout->addLayout(vLayoutCover, 4);
    hLayout->addStretch(1);
    hLayout->addLayout(vLayoutLyrics,5);
    hLayout->addStretch(1);

    // 设置主布局
    this->setLayout(hLayout);
}

void LyricsWidget::setLyrics(const QMap<int, QString> &lyrics, const QString &title, const QString &artist)
{
    // 设置标题和歌手
    m_titleArtist->setText(
        QString("<div style='line-height: 1.2;'>"
                "<p style='margin:0; font-family:Microsoft YaHei; font-size:13pt; font-weight:650; color:#000000;'>%1</p>"
                "<p style='margin:0; font-family:Microsoft YaHei; font-size:12px; color:#505050;'>%2</p>")
            .arg(title, artist)
        );

    // 设置歌词
    m_lyricsList->clear();
    m_lyricTimeVector.clear();

    if (lyrics.isEmpty())
    {
        QListWidgetItem *item = new QListWidgetItem("暂无歌词");
        m_lyricsList->addItem(item);
        return;
    }

    for (auto it = lyrics.begin(); it != lyrics.end(); ++it)
    {
        QListWidgetItem *item = new QListWidgetItem(it.value());
        m_lyricsList->addItem(item);

        m_lyricTimeVector.push_back(it.key());
    }
    // 添加10个空白行，使得歌词居中显示
    for (int i = 0; i < 10; ++i)
    {
        QListWidgetItem *item = new QListWidgetItem("");
        m_lyricsList->addItem(item);
    }
}

void LyricsWidget::updateLyrics(int key)
{
    int index = m_lyricTimeVector.indexOf(key);
    if (index == -1)
        return;

    m_lyricsList->setCurrentRow(index);

    // 保持在第5行
    m_lyricsList->scrollToItem(m_lyricsList->item(qMax(0, index - 4))
                               , QAbstractItemView::PositionAtTop);
}
