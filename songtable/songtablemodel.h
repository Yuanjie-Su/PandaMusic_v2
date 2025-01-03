#ifndef SONGTABLEMODEL_H
#define SONGTABLEMODEL_H

#include "utils/constants.h"

#include <QSqlTableModel>

#define SONG_TABLEMODEL SongTableModel::instance()

class SongTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    // 删除拷贝构造函数和赋值操作符，确保单例唯一性
    SongTableModel(const SongTableModel &) = delete;
    SongTableModel &operator=(const SongTableModel &) = delete;
    static SongTableModel *instance(QObject *parent = nullptr);

    void setCheckedAll(Qt::CheckState checked);
    void batchPlay(bool allSelected = true);
    void removeSelected(const QString &categoryName = QString());
    void removeSong(int songId, PlaylistKind listKind, const QString &categoryName = QString());
    QVector<int> selectedSongIds();
    void resetCheckState();
    void changeFavorite(int favorite, int songId);
    void updateTable(const QString &listName = QString(), PlaylistKind kind = PlaylistKind::PlayQueue);
    PlaylistKind currentPlaylistKind() const { return m_currentKind; }

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QString selectStatement() const override;

public slots:
    bool select() override;

signals:
    void checkStateChanged(Qt::CheckState checkState);
    void favoriteChanged(int songId, int favorite);

private:
    // 构造函数设为私有，禁止外部直接实例化
    explicit SongTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    ~SongTableModel() = default;
    static SongTableModel *m_instance;

    PlaylistKind m_currentKind = PlaylistKind::PlayQueue;

    bool notAllCheckedEdit = true;
    int checkedCount = 0;
    QVector<Qt::CheckState> checkStateMap;

    // 每行的背景色
    QVector<QColor> m_rowBackground;

    QMap<int, QPixmap> m_coverCache;

    void updateCheckState(int row, Qt::CheckState checkState);
};

#endif // SONGTABLEMODEL_H
