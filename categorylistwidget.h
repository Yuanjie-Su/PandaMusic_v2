#ifndef CATEGORYLISTWIDGET_H
#define CATEGORYLISTWIDGET_H

#include <QListWidget>

#define CATEGORY_ListWIDGET CategoryListWidget::instance()

class CategoryListWidget : public QListWidget
{
    Q_OBJECT
public:
    // 禁止拷贝与赋值
    CategoryListWidget(const CategoryListWidget &) = delete;
    CategoryListWidget& operator=(const CategoryListWidget &) = delete;
    static CategoryListWidget* instance(QWidget *parent = nullptr);

    void createNewCategoryName(int songId = -1);

    int m_currentRow = -1; // 上一次选中行

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void listSelected(const QString &listName);

private slots:
    void do_itemClicked(QListWidgetItem *item);
    void do_ItemEditFinished(QWidget *editor
                             , QAbstractItemDelegate::EndEditHint hint);

private:
    explicit CategoryListWidget(QWidget *parent = nullptr);

    void initList();
    void insertCategory();
    QString getNewCategoryName();
    void editCategoryName(int row);
    void updateCover(int row, const QString &coverPath);
    void updateCover(int row, const QPixmap &cover);

private:
    static CategoryListWidget *m_instance;  // 单例实例

    int m_columnCategoryWidgth = 130;
    QSet<QString> m_categoryNameSet;
    QString m_tempCategoryName;
    QString m_tempCoverPath;
    int m_tempSongId = -1;
    int m_editRow = -1;
    bool m_isNewNameEditing = false;
};

#endif // CATEGORYLISTWIDGET_H
