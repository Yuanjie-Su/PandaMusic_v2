#ifndef HEADERWITHCHECKBOX_H
#define HEADERWITHCHECKBOX_H

#include <QHeaderView>

class HeaderWithCheckbox : public QHeaderView {
    Q_OBJECT

public:
    explicit HeaderWithCheckbox(Qt::Orientation orientation, QWidget *parent = nullptr);

    void setColumnNames(const QVector<QString> &columnNames);
    void setCheckEdit(bool edit) { m_checkStateEdit = edit; }
    void setCheckState(Qt::CheckState checkState);

    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

    void mousePressEvent(QMouseEvent *event) override;

signals:
    void checkBoxToggled(Qt::CheckState checkState);

private:
    QVector<QString> m_columnNames;
    bool m_checkStateEdit = false;
    QString m_pathCheckedIcon = ":/icons/images/checked.png";
    QString m_pathUncheckedIcon = ":/icons/images/unchecked.png";
    QString m_pathPartiallyCheckedIcon = ":/icons/images/partially_checked.png";
    int m_checkColumn = 1;
    Qt::CheckState m_checkState;
};

#endif // HEADERWITHCHECKBOX_H
