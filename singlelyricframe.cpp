#include "singlelyricframe.h"


SingleLyricFrame::SingleLyricFrame(QWidget *parent) : QFrame(parent) {
    setStyleSheet("background-color: rgba(60,60,60, 0);"
                  "border-radius: 8px;");
}

void SingleLyricFrame::enterEvent(QEnterEvent *event) {
    setStyleSheet("background-color: rgba(60,60,60, 150);"
                  "border-radius: 8px;");
    emit btnVisable(true);
    QFrame::enterEvent(event);
}

void SingleLyricFrame::leaveEvent(QEvent *event) {
    setStyleSheet("background-color: rgba(60,60,60, 0);"
                  "border-radius: 8px;");
    emit btnVisable(false);
    QFrame::leaveEvent(event);
}
