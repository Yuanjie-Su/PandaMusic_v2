/********************************************************************************
** Form generated from reading UI file 'playmodecontrolwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYMODECONTROLWIDGET_H
#define UI_PLAYMODECONTROLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayModeControlWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;

    void setupUi(QWidget *PlayModeControlWidget)
    {
        if (PlayModeControlWidget->objectName().isEmpty())
            PlayModeControlWidget->setObjectName(QString::fromUtf8("PlayModeControlWidget"));
        PlayModeControlWidget->resize(140, 170);
        PlayModeControlWidget->setCursor(QCursor(Qt::PointingHandCursor));
        verticalLayout_2 = new QVBoxLayout(PlayModeControlWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        frame = new QFrame(PlayModeControlWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 253, 253);\n"
"border-radius: 10px;       "));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        listWidget = new QListWidget(frame);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setAutoScroll(true);
        listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidget->setItemAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(listWidget);


        verticalLayout_2->addWidget(frame);


        retranslateUi(PlayModeControlWidget);

        QMetaObject::connectSlotsByName(PlayModeControlWidget);
    } // setupUi

    void retranslateUi(QWidget *PlayModeControlWidget)
    {
        PlayModeControlWidget->setWindowTitle(QCoreApplication::translate("PlayModeControlWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayModeControlWidget: public Ui_PlayModeControlWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYMODECONTROLWIDGET_H
