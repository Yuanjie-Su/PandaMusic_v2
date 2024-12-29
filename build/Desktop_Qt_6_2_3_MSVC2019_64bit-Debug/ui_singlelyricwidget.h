/********************************************************************************
** Form generated from reading UI file 'singlelyricwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLELYRICWIDGET_H
#define UI_SINGLELYRICWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <singlelyricframe.h>
#include "singlelyriclabel.h"

QT_BEGIN_NAMESPACE

class Ui_LyricWidget
{
public:
    QHBoxLayout *horizontalLayout_4;
    SingleLyricFrame *frameLyric;
    QVBoxLayout *verticalLayout;
    QFrame *frameControl;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnPrevios;
    QPushButton *btnPlay;
    QPushButton *btnNext;
    QPushButton *btnClose;
    QSpacerItem *horizontalSpacer;
    SingleLyricLabel *labelLyric;

    void setupUi(QWidget *LyricWidget)
    {
        if (LyricWidget->objectName().isEmpty())
            LyricWidget->setObjectName(QString::fromUtf8("LyricWidget"));
        LyricWidget->resize(550, 110);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LyricWidget->sizePolicy().hasHeightForWidth());
        LyricWidget->setSizePolicy(sizePolicy);
        horizontalLayout_4 = new QHBoxLayout(LyricWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(7, 7, 7, 7);
        frameLyric = new SingleLyricFrame(LyricWidget);
        frameLyric->setObjectName(QString::fromUtf8("frameLyric"));
        frameLyric->setStyleSheet(QString::fromUtf8(""));
        frameLyric->setFrameShape(QFrame::StyledPanel);
        frameLyric->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frameLyric);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frameControl = new QFrame(frameLyric);
        frameControl->setObjectName(QString::fromUtf8("frameControl"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frameControl->sizePolicy().hasHeightForWidth());
        frameControl->setSizePolicy(sizePolicy1);
        frameControl->setMinimumSize(QSize(0, 45));
        frameControl->setMaximumSize(QSize(16777215, 45));
        frameControl->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        frameControl->setFrameShape(QFrame::StyledPanel);
        frameControl->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frameControl);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(24);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnPrevios = new QPushButton(frameControl);
        btnPrevios->setObjectName(QString::fromUtf8("btnPrevios"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnPrevios->sizePolicy().hasHeightForWidth());
        btnPrevios->setSizePolicy(sizePolicy2);
        btnPrevios->setMinimumSize(QSize(21, 21));
        btnPrevios->setMaximumSize(QSize(21, 21));
        btnPrevios->setCursor(QCursor(Qt::PointingHandCursor));
        btnPrevios->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/previous_lyric.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPrevios->setIcon(icon);

        horizontalLayout->addWidget(btnPrevios);

        btnPlay = new QPushButton(frameControl);
        btnPlay->setObjectName(QString::fromUtf8("btnPlay"));
        btnPlay->setMinimumSize(QSize(21, 21));
        btnPlay->setMaximumSize(QSize(21, 21));
        btnPlay->setCursor(QCursor(Qt::PointingHandCursor));
        btnPlay->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/images/play_lyric.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPlay->setIcon(icon1);

        horizontalLayout->addWidget(btnPlay);

        btnNext = new QPushButton(frameControl);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));
        btnNext->setMinimumSize(QSize(21, 21));
        btnNext->setMaximumSize(QSize(21, 21));
        btnNext->setCursor(QCursor(Qt::PointingHandCursor));
        btnNext->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/images/next_lyric.png.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnNext->setIcon(icon2);

        horizontalLayout->addWidget(btnNext);


        horizontalLayout_3->addLayout(horizontalLayout);

        btnClose = new QPushButton(frameControl);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setMinimumSize(QSize(21, 21));
        btnClose->setMaximumSize(QSize(21, 21));
        btnClose->setCursor(QCursor(Qt::PointingHandCursor));
        btnClose->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/images/close_lyric.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon3);
        btnClose->setIconSize(QSize(14, 14));

        horizontalLayout_3->addWidget(btnClose);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        horizontalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(frameControl);

        labelLyric = new SingleLyricLabel(frameLyric);
        labelLyric->setObjectName(QString::fromUtf8("labelLyric"));
        QFont font;
        font.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font.setPointSize(24);
        font.setBold(true);
        font.setStyleStrategy(QFont::PreferAntialias);
        labelLyric->setFont(font);
        labelLyric->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        labelLyric->setTextFormat(Qt::AutoText);
        labelLyric->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelLyric);


        horizontalLayout_4->addWidget(frameLyric);


        retranslateUi(LyricWidget);

        QMetaObject::connectSlotsByName(LyricWidget);
    } // setupUi

    void retranslateUi(QWidget *LyricWidget)
    {
        LyricWidget->setWindowTitle(QCoreApplication::translate("LyricWidget", "Form", nullptr));
#if QT_CONFIG(tooltip)
        btnPrevios->setToolTip(QCoreApplication::translate("LyricWidget", "\344\270\212\344\270\200\351\246\226", nullptr));
#endif // QT_CONFIG(tooltip)
        btnPrevios->setText(QString());
#if QT_CONFIG(tooltip)
        btnPlay->setToolTip(QCoreApplication::translate("LyricWidget", "\346\222\255\346\224\276", nullptr));
#endif // QT_CONFIG(tooltip)
        btnPlay->setText(QString());
#if QT_CONFIG(tooltip)
        btnNext->setToolTip(QCoreApplication::translate("LyricWidget", "\344\270\213\344\270\200\351\246\226", nullptr));
#endif // QT_CONFIG(tooltip)
        btnNext->setText(QString());
#if QT_CONFIG(tooltip)
        btnClose->setToolTip(QCoreApplication::translate("LyricWidget", "\345\205\263\351\227\255", nullptr));
#endif // QT_CONFIG(tooltip)
        btnClose->setText(QString());
        labelLyric->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LyricWidget: public Ui_LyricWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLELYRICWIDGET_H
