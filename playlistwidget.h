#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QListWidget>

#define LISTWIDGET_MYMUSIC ListWidgetMyMusic::instance()

class ListWidgetMyMusic : public QListWidget
{
    Q_OBJECT
public:
    // 禁止拷贝与赋值
    ListWidgetMyMusic(const ListWidgetMyMusic &) = delete;
    ListWidgetMyMusic& operator=(const ListWidgetMyMusic &) = delete;
    // 获取单例实例
    static ListWidgetMyMusic* instance(QWidget *parent = nullptr);

signals:
    void listSelected(const QString &listName);
    void exitBatchProcess();

private slots:
    void do_currentRowChanged(int row);

private:
    explicit ListWidgetMyMusic(QWidget *parent = nullptr);

    // 单例对象
    static ListWidgetMyMusic *m_instance;
};

#endif // PLAYLISTWIDGET_H
