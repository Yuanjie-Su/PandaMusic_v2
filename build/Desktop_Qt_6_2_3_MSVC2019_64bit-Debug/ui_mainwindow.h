/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <coverpushbutton.h>
#include "lyricswidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widgetList;
    QLabel *labelPlaylist;
    QLabel *labelPandamusic;
    QLabel *labelCategory;
    QPushButton *btnNewCategory;
    QFrame *frameTable;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labelListTitle;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnBatchPlay;
    QPushButton *btnBatchProcess;
    QPushButton *btnImport;
    QPushButton *btnBatchAddTo;
    QPushButton *btnRemoveBatch;
    QPushButton *btnExitBatch;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *lineEditSearch;
    LyricsWidget *lyricsWidget;
    QWidget *widgetPlayControl;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    CoverPushButton *btnCover;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelTitle;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnFavoriteOne;
    QPushButton *btnComent;
    QPushButton *btnMoreOne;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnPlayMode;
    QPushButton *btnPrevious;
    QPushButton *btnPlay;
    QPushButton *btnNext;
    QPushButton *btnVolume;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelPosition;
    QSlider *sliderPosition;
    QLabel *labelDuration;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnLyric;
    QPushButton *btnBanlance;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1050, 680);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1050, 680));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/windowTitle_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widgetTop = new QWidget(centralwidget);
        widgetTop->setObjectName(QString::fromUtf8("widgetTop"));
        horizontalLayout_2 = new QHBoxLayout(widgetTop);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        widgetList = new QWidget(widgetTop);
        widgetList->setObjectName(QString::fromUtf8("widgetList"));
        labelPlaylist = new QLabel(widgetList);
        labelPlaylist->setObjectName(QString::fromUtf8("labelPlaylist"));
        labelPlaylist->setGeometry(QRect(40, 100, 48, 16));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelPlaylist->sizePolicy().hasHeightForWidth());
        labelPlaylist->setSizePolicy(sizePolicy1);
        labelPlaylist->setStyleSheet(QString::fromUtf8("QLabel#labelPlaylist\n"
" { \n"
"        font-family: Microsoft YaHei; \n"
"        font-size: 12px;\n"
"        color: rgb(80, 80, 80); \n"
"        }"));
        labelPandamusic = new QLabel(widgetList);
        labelPandamusic->setObjectName(QString::fromUtf8("labelPandamusic"));
        labelPandamusic->setGeometry(QRect(30, 70, 120, 30));
        sizePolicy1.setHeightForWidth(labelPandamusic->sizePolicy().hasHeightForWidth());
        labelPandamusic->setSizePolicy(sizePolicy1);
        labelPandamusic->setMinimumSize(QSize(120, 30));
        labelPandamusic->setMaximumSize(QSize(120, 30));
        QFont font;
        font.setStyleStrategy(QFont::PreferAntialias);
        labelPandamusic->setFont(font);
        labelPandamusic->setScaledContents(true);
        labelCategory = new QLabel(widgetList);
        labelCategory->setObjectName(QString::fromUtf8("labelCategory"));
        labelCategory->setGeometry(QRect(31, 133, 48, 16));
        sizePolicy1.setHeightForWidth(labelCategory->sizePolicy().hasHeightForWidth());
        labelCategory->setSizePolicy(sizePolicy1);
        labelCategory->setStyleSheet(QString::fromUtf8("QLabel#labelCategory{ \n"
"        font-family: Microsoft YaHei; \n"
"        font-size: 12px;\n"
"        color: rgb(80, 80, 80); \n"
"        }"));
        btnNewCategory = new QPushButton(widgetList);
        btnNewCategory->setObjectName(QString::fromUtf8("btnNewCategory"));
        btnNewCategory->setGeometry(QRect(89, 133, 16, 16));
        sizePolicy1.setHeightForWidth(btnNewCategory->sizePolicy().hasHeightForWidth());
        btnNewCategory->setSizePolicy(sizePolicy1);
        btnNewCategory->setMinimumSize(QSize(16, 16));
        btnNewCategory->setMaximumSize(QSize(16, 16));
        btnNewCategory->setCursor(QCursor(Qt::PointingHandCursor));
        btnNewCategory->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/images/newCategory.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnNewCategory->setIcon(icon1);
        btnNewCategory->setIconSize(QSize(12, 12));

        horizontalLayout_2->addWidget(widgetList);

        frameTable = new QFrame(widgetTop);
        frameTable->setObjectName(QString::fromUtf8("frameTable"));
        frameTable->setStyleSheet(QString::fromUtf8("QFrame#frameTable{background-color: rgb(249, 249, 249);}"));
        verticalLayout_5 = new QVBoxLayout(frameTable);
        verticalLayout_5->setSpacing(11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(22, -1, -1, 0);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        labelListTitle = new QLabel(frameTable);
        labelListTitle->setObjectName(QString::fromUtf8("labelListTitle"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelListTitle->sizePolicy().hasHeightForWidth());
        labelListTitle->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(24);
        font1.setBold(true);
        labelListTitle->setFont(font1);

        horizontalLayout_10->addWidget(labelListTitle);


        verticalLayout_5->addLayout(horizontalLayout_10);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnBatchPlay = new QPushButton(frameTable);
        btnBatchPlay->setObjectName(QString::fromUtf8("btnBatchPlay"));
        QFont font2;
        font2.setPointSize(10);
        btnBatchPlay->setFont(font2);
        btnBatchPlay->setCursor(QCursor(Qt::PointingHandCursor));
        btnBatchPlay->setStyleSheet(QString::fromUtf8("QPushButton#btnBatchPlay {\n"
"background-color: rgb(230,230,230);\n"
"border: none;\n"
"border-radius:16px;\n"
"\n"
"padding-top: 8px;\n"
"padding-bottom:8px;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/images/play_one.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnBatchPlay->setIcon(icon2);
        btnBatchPlay->setFlat(false);

        horizontalLayout_3->addWidget(btnBatchPlay);

        btnBatchProcess = new QPushButton(frameTable);
        btnBatchProcess->setObjectName(QString::fromUtf8("btnBatchProcess"));
        btnBatchProcess->setFont(font2);
        btnBatchProcess->setCursor(QCursor(Qt::PointingHandCursor));
        btnBatchProcess->setStyleSheet(QString::fromUtf8("QPushButton#btnBatchProcess {\n"
"background-color: rgb(230,230,230);\n"
"border: none;\n"
"border-radius:16px;\n"
"\n"
" padding-top: 8px;\n"
"padding-bottom:8px;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/images/batchprocess.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnBatchProcess->setIcon(icon3);

        horizontalLayout_3->addWidget(btnBatchProcess);

        btnImport = new QPushButton(frameTable);
        btnImport->setObjectName(QString::fromUtf8("btnImport"));
        btnImport->setCursor(QCursor(Qt::PointingHandCursor));
        btnImport->setStyleSheet(QString::fromUtf8("QPushButton#btnImport {\n"
"background-color: rgb(230,230,230);\n"
"border: none;\n"
"border-radius:16px;\n"
"\n"
" padding-top: 8px;\n"
"padding-bottom:8px;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/images/import.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnImport->setIcon(icon4);

        horizontalLayout_3->addWidget(btnImport);

        btnBatchAddTo = new QPushButton(frameTable);
        btnBatchAddTo->setObjectName(QString::fromUtf8("btnBatchAddTo"));
        btnBatchAddTo->setStyleSheet(QString::fromUtf8("QPushButton#btnBatchAddTo {\n"
"background-color: rgb(230,230,230);\n"
"border: none;\n"
"border-radius:16px;\n"
"\n"
" padding-top: 8px;\n"
"padding-bottom:8px;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
"}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/images/addToButton.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnBatchAddTo->setIcon(icon5);

        horizontalLayout_3->addWidget(btnBatchAddTo);

        btnRemoveBatch = new QPushButton(frameTable);
        btnRemoveBatch->setObjectName(QString::fromUtf8("btnRemoveBatch"));
        btnRemoveBatch->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"background-color: rgb(230,230,230);\n"
"border: none;\n"
"border-radius:16px;\n"
"\n"
" padding-top: 8px;\n"
"padding-bottom:8px;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
"}"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/images/trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRemoveBatch->setIcon(icon6);

        horizontalLayout_3->addWidget(btnRemoveBatch);

        btnExitBatch = new QPushButton(frameTable);
        btnExitBatch->setObjectName(QString::fromUtf8("btnExitBatch"));
        btnExitBatch->setFont(font2);
        btnExitBatch->setCursor(QCursor(Qt::PointingHandCursor));
        btnExitBatch->setStyleSheet(QString::fromUtf8("QPushButton#btnExitBatch {\n"
"background-color: rgb(230,230,230);\n"
"border: none;\n"
"border-radius:16px;\n"
" padding-top: 8px;\n"
"padding-bottom:8px;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
"}"));

        horizontalLayout_3->addWidget(btnExitBatch);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        lineEditSearch = new QLineEdit(frameTable);
        lineEditSearch->setObjectName(QString::fromUtf8("lineEditSearch"));
        sizePolicy1.setHeightForWidth(lineEditSearch->sizePolicy().hasHeightForWidth());
        lineEditSearch->setSizePolicy(sizePolicy1);
        lineEditSearch->setMinimumSize(QSize(120, 0));
        lineEditSearch->setMaximumSize(QSize(120, 16777215));
        lineEditSearch->setStyleSheet(QString::fromUtf8("QLineEdit#lineEditSearch {\n"
"           background-color: rgb(230,230,230);\n"
"border: none;\n"
"border-radius:16px;\n"
" padding-top: 8px;\n"
"padding-bottom:8px;\n"
"padding-left: 10px;\n"
"padding-right:20px;\n"
"            }"));
        lineEditSearch->setFrame(false);
        lineEditSearch->setCursorMoveStyle(Qt::LogicalMoveStyle);
        lineEditSearch->setClearButtonEnabled(false);

        horizontalLayout_3->addWidget(lineEditSearch);


        verticalLayout_5->addLayout(horizontalLayout_3);


        horizontalLayout_2->addWidget(frameTable);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addWidget(widgetTop);

        lyricsWidget = new LyricsWidget(centralwidget);
        lyricsWidget->setObjectName(QString::fromUtf8("lyricsWidget"));

        verticalLayout->addWidget(lyricsWidget);

        widgetPlayControl = new QWidget(centralwidget);
        widgetPlayControl->setObjectName(QString::fromUtf8("widgetPlayControl"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widgetPlayControl->sizePolicy().hasHeightForWidth());
        widgetPlayControl->setSizePolicy(sizePolicy3);
        widgetPlayControl->setMinimumSize(QSize(1050, 80));
        widgetPlayControl->setMaximumSize(QSize(16777215, 80));
        widgetPlayControl->setStyleSheet(QString::fromUtf8("QWidget {\n"
" border-top: 1px solid rgba(80, 80, 80, 0.3);\n"
" border-left: none;\n"
" border-right: none;\n"
" border-bottom: none;\n"
"border-top-left-radius: 0px; \n"
"  border-top-right-radius: 0px;\n"
"   border-bottom-left-radius: 10px;\n"
"    border-bottom-right-radius: 10px;\n"
" }"));
        horizontalLayout_6 = new QHBoxLayout(widgetPlayControl);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(14, 11, 14, 11);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        btnCover = new CoverPushButton(widgetPlayControl);
        btnCover->setObjectName(QString::fromUtf8("btnCover"));
        sizePolicy1.setHeightForWidth(btnCover->sizePolicy().hasHeightForWidth());
        btnCover->setSizePolicy(sizePolicy1);
        btnCover->setMinimumSize(QSize(56, 56));
        btnCover->setMaximumSize(QSize(56, 56));
        btnCover->setCursor(QCursor(Qt::PointingHandCursor));
        btnCover->setStyleSheet(QString::fromUtf8("border:none;"));
        btnCover->setIconSize(QSize(56, 56));
        btnCover->setCheckable(true);

        horizontalLayout_4->addWidget(btnCover);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 4, -1, 4);
        labelTitle = new QLabel(widgetPlayControl);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        sizePolicy1.setHeightForWidth(labelTitle->sizePolicy().hasHeightForWidth());
        labelTitle->setSizePolicy(sizePolicy1);
        labelTitle->setMinimumSize(QSize(200, 20));
        labelTitle->setMaximumSize(QSize(210, 20));
        labelTitle->setStyleSheet(QString::fromUtf8("border:none;"));

        verticalLayout_2->addWidget(labelTitle);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 0);
        btnFavoriteOne = new QPushButton(widgetPlayControl);
        btnFavoriteOne->setObjectName(QString::fromUtf8("btnFavoriteOne"));
        sizePolicy1.setHeightForWidth(btnFavoriteOne->sizePolicy().hasHeightForWidth());
        btnFavoriteOne->setSizePolicy(sizePolicy1);
        btnFavoriteOne->setMaximumSize(QSize(25, 25));
        btnFavoriteOne->setCursor(QCursor(Qt::PointingHandCursor));
        btnFavoriteOne->setStyleSheet(QString::fromUtf8("border: none;"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/images/unlike.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnFavoriteOne->setIcon(icon7);
        btnFavoriteOne->setIconSize(QSize(20, 20));

        horizontalLayout_5->addWidget(btnFavoriteOne);

        btnComent = new QPushButton(widgetPlayControl);
        btnComent->setObjectName(QString::fromUtf8("btnComent"));
        sizePolicy1.setHeightForWidth(btnComent->sizePolicy().hasHeightForWidth());
        btnComent->setSizePolicy(sizePolicy1);
        btnComent->setMaximumSize(QSize(25, 25));
        btnComent->setStyleSheet(QString::fromUtf8("border: none;"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/images/coment.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnComent->setIcon(icon8);
        btnComent->setIconSize(QSize(20, 20));

        horizontalLayout_5->addWidget(btnComent);

        btnMoreOne = new QPushButton(widgetPlayControl);
        btnMoreOne->setObjectName(QString::fromUtf8("btnMoreOne"));
        sizePolicy1.setHeightForWidth(btnMoreOne->sizePolicy().hasHeightForWidth());
        btnMoreOne->setSizePolicy(sizePolicy1);
        btnMoreOne->setMaximumSize(QSize(25, 25));
        btnMoreOne->setCursor(QCursor(Qt::PointingHandCursor));
        btnMoreOne->setStyleSheet(QString::fromUtf8("border: none;"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/images/more.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMoreOne->setIcon(icon9);
        btnMoreOne->setIconSize(QSize(16, 16));

        horizontalLayout_5->addWidget(btnMoreOne);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_5);


        horizontalLayout_4->addLayout(verticalLayout_2);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnPlayMode = new QPushButton(widgetPlayControl);
        btnPlayMode->setObjectName(QString::fromUtf8("btnPlayMode"));
        sizePolicy1.setHeightForWidth(btnPlayMode->sizePolicy().hasHeightForWidth());
        btnPlayMode->setSizePolicy(sizePolicy1);
        btnPlayMode->setMinimumSize(QSize(40, 40));
        btnPlayMode->setMaximumSize(QSize(40, 40));
        btnPlayMode->setCursor(QCursor(Qt::PointingHandCursor));
        btnPlayMode->setStyleSheet(QString::fromUtf8("border: none;"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/images/sequential.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPlayMode->setIcon(icon10);
        btnPlayMode->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(btnPlayMode);

        btnPrevious = new QPushButton(widgetPlayControl);
        btnPrevious->setObjectName(QString::fromUtf8("btnPrevious"));
        btnPrevious->setEnabled(true);
        sizePolicy1.setHeightForWidth(btnPrevious->sizePolicy().hasHeightForWidth());
        btnPrevious->setSizePolicy(sizePolicy1);
        btnPrevious->setMinimumSize(QSize(40, 40));
        btnPrevious->setMaximumSize(QSize(40, 40));
        btnPrevious->setCursor(QCursor(Qt::PointingHandCursor));
        btnPrevious->setStyleSheet(QString::fromUtf8("border: none;"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/images/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPrevious->setIcon(icon11);
        btnPrevious->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(btnPrevious);

        btnPlay = new QPushButton(widgetPlayControl);
        btnPlay->setObjectName(QString::fromUtf8("btnPlay"));
        btnPlay->setEnabled(true);
        sizePolicy1.setHeightForWidth(btnPlay->sizePolicy().hasHeightForWidth());
        btnPlay->setSizePolicy(sizePolicy1);
        btnPlay->setMinimumSize(QSize(40, 40));
        btnPlay->setMaximumSize(QSize(40, 40));
        btnPlay->setCursor(QCursor(Qt::PointingHandCursor));
        btnPlay->setStyleSheet(QString::fromUtf8("border: none;"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icons/images/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPlay->setIcon(icon12);
        btnPlay->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(btnPlay);

        btnNext = new QPushButton(widgetPlayControl);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));
        btnNext->setEnabled(true);
        sizePolicy1.setHeightForWidth(btnNext->sizePolicy().hasHeightForWidth());
        btnNext->setSizePolicy(sizePolicy1);
        btnNext->setMinimumSize(QSize(40, 40));
        btnNext->setMaximumSize(QSize(40, 40));
        btnNext->setCursor(QCursor(Qt::PointingHandCursor));
        btnNext->setStyleSheet(QString::fromUtf8("border: none;"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icons/images/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnNext->setIcon(icon13);
        btnNext->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(btnNext);

        btnVolume = new QPushButton(widgetPlayControl);
        btnVolume->setObjectName(QString::fromUtf8("btnVolume"));
        sizePolicy1.setHeightForWidth(btnVolume->sizePolicy().hasHeightForWidth());
        btnVolume->setSizePolicy(sizePolicy1);
        btnVolume->setMinimumSize(QSize(40, 40));
        btnVolume->setMaximumSize(QSize(40, 40));
        btnVolume->setCursor(QCursor(Qt::PointingHandCursor));
        btnVolume->setStyleSheet(QString::fromUtf8("border: none;"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/icons/images/volume.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnVolume->setIcon(icon14);
        btnVolume->setIconSize(QSize(20, 20));
        btnVolume->setFlat(true);

        horizontalLayout->addWidget(btnVolume);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        labelPosition = new QLabel(widgetPlayControl);
        labelPosition->setObjectName(QString::fromUtf8("labelPosition"));
        sizePolicy2.setHeightForWidth(labelPosition->sizePolicy().hasHeightForWidth());
        labelPosition->setSizePolicy(sizePolicy2);
        QFont font3;
        font3.setPointSize(8);
        labelPosition->setFont(font3);
        labelPosition->setStyleSheet(QString::fromUtf8("color: rgb(80, 80, 80);\n"
"border:none;"));

        horizontalLayout_8->addWidget(labelPosition);

        sliderPosition = new QSlider(widgetPlayControl);
        sliderPosition->setObjectName(QString::fromUtf8("sliderPosition"));
        sizePolicy3.setHeightForWidth(sliderPosition->sizePolicy().hasHeightForWidth());
        sliderPosition->setSizePolicy(sizePolicy3);
        sliderPosition->setMinimumSize(QSize(0, 0));
        sliderPosition->setMaximumSize(QSize(16777215, 16777215));
        sliderPosition->setCursor(QCursor(Qt::ArrowCursor));
        sliderPosition->setStyleSheet(QString::fromUtf8("QSlider {\n"
" border: none;\n"
"}\n"
"QSlider::groove:horizontal {\n"
"	height: 2px;  /* \350\275\250\351\201\223\351\253\230\345\272\246 */\n"
" 	border-radius:1px; \n"
"	background: rgb(219,219,219);\n"
"}\n"
"QSlider::handle:horizontal {\n"
"	background-color: rgb(64,64,64);\n"
"    width: 8px;  /* \346\273\221\345\235\227\345\256\275\345\272\246 */\n"
"    border-radius: 4px;  /* \345\234\206\345\275\242\346\273\221\345\235\227 */\n"
"	margin:-3px 0px -3px 0;\n"
"}\n"
"QSlider::sub-page:horizontal {\n"
"background-color: rgb(64,64,64);\n"
"}"));
        sliderPosition->setMaximum(1000);
        sliderPosition->setTracking(false);
        sliderPosition->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(sliderPosition);

        labelDuration = new QLabel(widgetPlayControl);
        labelDuration->setObjectName(QString::fromUtf8("labelDuration"));
        sizePolicy2.setHeightForWidth(labelDuration->sizePolicy().hasHeightForWidth());
        labelDuration->setSizePolicy(sizePolicy2);
        labelDuration->setFont(font3);
        labelDuration->setStyleSheet(QString::fromUtf8("border:none;\n"
"\n"
"color: rgb(80, 80, 80);"));

        horizontalLayout_8->addWidget(labelDuration);


        verticalLayout_4->addLayout(horizontalLayout_8);


        horizontalLayout_6->addLayout(verticalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(20);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, 0, 20, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        btnLyric = new QPushButton(widgetPlayControl);
        btnLyric->setObjectName(QString::fromUtf8("btnLyric"));
        sizePolicy1.setHeightForWidth(btnLyric->sizePolicy().hasHeightForWidth());
        btnLyric->setSizePolicy(sizePolicy1);
        btnLyric->setMinimumSize(QSize(32, 32));
        btnLyric->setMaximumSize(QSize(32, 32));
        btnLyric->setCursor(QCursor(Qt::PointingHandCursor));
        btnLyric->setStyleSheet(QString::fromUtf8("border: none;"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/icons/images/lyric.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnLyric->setIcon(icon15);
        btnLyric->setIconSize(QSize(24, 24));

        horizontalLayout_7->addWidget(btnLyric);

        btnBanlance = new QPushButton(widgetPlayControl);
        btnBanlance->setObjectName(QString::fromUtf8("btnBanlance"));
        sizePolicy1.setHeightForWidth(btnBanlance->sizePolicy().hasHeightForWidth());
        btnBanlance->setSizePolicy(sizePolicy1);
        btnBanlance->setMinimumSize(QSize(32, 32));
        btnBanlance->setMaximumSize(QSize(32, 32));
        btnBanlance->setCursor(QCursor(Qt::PointingHandCursor));
        btnBanlance->setStyleSheet(QString::fromUtf8("border: none;"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/icons/images/balance.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnBanlance->setIcon(icon16);
        btnBanlance->setIconSize(QSize(24, 24));

        horizontalLayout_7->addWidget(btnBanlance);


        horizontalLayout_6->addLayout(horizontalLayout_7);

        horizontalLayout_6->setStretch(0, 2);
        horizontalLayout_6->setStretch(1, 3);
        horizontalLayout_6->setStretch(2, 2);

        verticalLayout->addWidget(widgetPlayControl);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PandaMusic", nullptr));
        labelPlaylist->setText(QCoreApplication::translate("MainWindow", "\346\210\221\347\232\204\351\237\263\344\271\220", nullptr));
        labelPandamusic->setText(QCoreApplication::translate("MainWindow", "pandamusic", nullptr));
        labelCategory->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\273\272\346\255\214\345\215\225", nullptr));
#if QT_CONFIG(tooltip)
        btnNewCategory->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\346\255\214\345\215\225", nullptr));
#endif // QT_CONFIG(tooltip)
        btnNewCategory->setText(QString());
        labelListTitle->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\351\230\237\345\210\227", nullptr));
#if QT_CONFIG(tooltip)
        btnBatchPlay->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276", nullptr));
#endif // QT_CONFIG(tooltip)
        btnBatchPlay->setText(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276", nullptr));
#if QT_CONFIG(tooltip)
        btnBatchProcess->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\271\351\207\217\346\223\215\344\275\234", nullptr));
#endif // QT_CONFIG(tooltip)
        btnBatchProcess->setText(QCoreApplication::translate("MainWindow", "\346\211\271\351\207\217\346\223\215\344\275\234", nullptr));
        btnImport->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\346\255\214\346\233\262", nullptr));
        btnBatchAddTo->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\210\260", nullptr));
        btnRemoveBatch->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
#if QT_CONFIG(tooltip)
        btnExitBatch->setToolTip(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\346\211\271\351\207\217\346\223\215\344\275\234", nullptr));
#endif // QT_CONFIG(tooltip)
        btnExitBatch->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\346\211\271\351\207\217\346\223\215\344\275\234", nullptr));
        lineEditSearch->setInputMask(QString());
        lineEditSearch->setPlaceholderText(QString());
        btnCover->setText(QString());
        labelTitle->setText(QCoreApplication::translate("MainWindow", "\346\255\214\345\220\215", nullptr));
        btnFavoriteOne->setText(QString());
        btnComent->setText(QString());
        btnMoreOne->setText(QString());
#if QT_CONFIG(tooltip)
        btnPlayMode->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\346\250\241\345\274\217", nullptr));
#endif // QT_CONFIG(tooltip)
        btnPlayMode->setText(QString());
#if QT_CONFIG(tooltip)
        btnPrevious->setToolTip(QCoreApplication::translate("MainWindow", "\345\211\215\344\270\200\346\233\262", nullptr));
#endif // QT_CONFIG(tooltip)
        btnPrevious->setText(QString());
#if QT_CONFIG(tooltip)
        btnPlay->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276", nullptr));
#endif // QT_CONFIG(tooltip)
        btnPlay->setText(QString());
#if QT_CONFIG(tooltip)
        btnNext->setToolTip(QCoreApplication::translate("MainWindow", "\345\220\216\344\270\200\346\233\262", nullptr));
#endif // QT_CONFIG(tooltip)
        btnNext->setText(QString());
#if QT_CONFIG(tooltip)
        btnVolume->setToolTip(QCoreApplication::translate("MainWindow", "\351\237\263\351\207\217", nullptr));
#endif // QT_CONFIG(tooltip)
        btnVolume->setText(QString());
        labelPosition->setText(QCoreApplication::translate("MainWindow", "0:0", nullptr));
        labelDuration->setText(QCoreApplication::translate("MainWindow", "0:0", nullptr));
#if QT_CONFIG(tooltip)
        btnLyric->setToolTip(QCoreApplication::translate("MainWindow", "\346\255\214\350\257\215", nullptr));
#endif // QT_CONFIG(tooltip)
        btnLyric->setText(QString());
#if QT_CONFIG(tooltip)
        btnBanlance->setToolTip(QCoreApplication::translate("MainWindow", "\351\237\263\346\225\210", nullptr));
#endif // QT_CONFIG(tooltip)
        btnBanlance->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
