#ifndef SONGTABLEVIEW_H
#define SONGTABLEVIEW_H

#include "basetableview.h"
#include "headerwithcheckbox.h"
#include "checkboxdelegate.h"

#define SONG_TABLEVIEW SongTableView::instance()


class SongTableView : public BaseTableView
{
    Q_OBJECT
public:
    // 获取单例实例
    static SongTableView *instance(QWidget *parent = nullptr);
    // 禁止拷贝构造和赋值操作
    SongTableView(const SongTableView &) = delete;
    SongTableView &operator=(const SongTableView &) = delete;

    bool enterBatchProcess();
    void exitBatchProcess();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    // 构造函数设为私有，禁止直接实例化
    explicit SongTableView(QWidget *parent = nullptr);
    ~SongTableView() = default;

    static SongTableView *m_instance; // 静态实例指针

    HeaderWithCheckbox *m_header;
    CheckBoxDelegate *m_checkBoxDelegate;
};

#endif // SONGTABLEVIEW_H
