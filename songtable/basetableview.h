#ifndef BASETABLEVIEW_H
#define BASETABLEVIEW_H

#include <QTableView>
#include <QColor>

class BaseTableView : public QTableView
{
    Q_OBJECT
public:
    explicit BaseTableView(QWidget *parent = nullptr);

    void setSelectedColor(const QColor &color) { m_colorSelected = color; }
    void setUnSelectedColor(const QColor &color) { m_colorUnselected = color; }
    void setUnSelectedOddColor(const QColor &color) { m_colorUnselectedOdd = color; }

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void updateRowBackground(int row, const QColor &color);
    void restoreOldRowBackground();

private:
    int m_oldEnteredRow = -1;  // 上一次鼠标悬停的行号
    int m_oldSelectedRow = -1; // 上一次选中的行号
    QColor m_colorSelected = QColor(221, 221, 221);
    QColor m_colorUnselected = QColor(249, 249, 249);
    QColor m_colorUnselectedOdd = QColor(243, 243, 243);
};

#endif // BASETABLEVIEW_H
