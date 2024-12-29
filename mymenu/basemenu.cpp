#include "basemenu.h"

#include <QGraphicsDropShadowEffect>

BaseMenu::BaseMenu(QWidget *parent)
    : QMenu(parent)
{
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setCursor(Qt::PointingHandCursor);
    // 设置阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(Qt::gray);
    shadow->setBlurRadius(10);
    this->setGraphicsEffect(shadow);

    this->setStyleSheet("QMenu {"
                        "	background-color:rgb(253,253,253);"
                        "	border-radius:10px;"
                        "	padding:10px 0px 10px 0px;"
                        "	margin: 10px;"
                        "}"
                        "QMenu::separator{"
                        "height:1px;"
                        "background:#bbbbbb;"
                        "}"
                        "QMenu::item {"
                        " padding-top:10px;"
                        " padding-bottom:10px;"
                        " padding-left: 12px;"
                        " padding-right:12px;"
                        "}"
                        "QMenu::item:selected {"
                        "color: black;"
                        "background-color: rgb(221,221,221);" // 鼠标悬停背景
                        "}"
                        "QMenu::item:selected:disabled {"
                        "background-color: transparent;"
                        "color: gray;"
                        "}"
                        "QMenu::icon{  padding-left:12px; }"
                        );
}
