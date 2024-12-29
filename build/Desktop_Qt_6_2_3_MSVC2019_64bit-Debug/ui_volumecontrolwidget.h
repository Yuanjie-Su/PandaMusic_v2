/********************************************************************************
** Form generated from reading UI file 'volumecontrolwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLUMECONTROLWIDGET_H
#define UI_VOLUMECONTROLWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VolumeControlWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QSlider *verticalSliderVolume;
    QLabel *labelVolume;
    QPushButton *btnVolume;

    void setupUi(QWidget *VolumeControlWidget)
    {
        if (VolumeControlWidget->objectName().isEmpty())
            VolumeControlWidget->setObjectName(QString::fromUtf8("VolumeControlWidget"));
        VolumeControlWidget->resize(82, 222);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VolumeControlWidget->sizePolicy().hasHeightForWidth());
        VolumeControlWidget->setSizePolicy(sizePolicy);
        VolumeControlWidget->setMinimumSize(QSize(0, 0));
        VolumeControlWidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(VolumeControlWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame = new QFrame(VolumeControlWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(60, 200));
        frame->setMaximumSize(QSize(60, 200));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 253, 253);\n"
"border-radius: 10px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 15, -1, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSliderVolume = new QSlider(frame);
        verticalSliderVolume->setObjectName(QString::fromUtf8("verticalSliderVolume"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(verticalSliderVolume->sizePolicy().hasHeightForWidth());
        verticalSliderVolume->setSizePolicy(sizePolicy2);
        verticalSliderVolume->setMinimumSize(QSize(40, 0));
        verticalSliderVolume->setMaximumSize(QSize(40, 16777215));
        verticalSliderVolume->setStyleSheet(QString::fromUtf8("QSlider::groove:vertical {\n"
"    background: rgb(219,219,219);       /* \346\273\221\345\212\250\346\235\241\346\247\275\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    width: 3px;                /* \346\247\275\347\232\204\345\256\275\345\272\246 */\n"
"}\n"
"\n"
"QSlider::handle:vertical {\n"
"    background: rgb(26,217,110);       /* \346\273\221\345\235\227\347\232\204\351\242\234\350\211\262 */\n"
"    height: 10px;              /* \346\273\221\345\235\227\347\232\204\351\253\230\345\272\246 */\n"
"    margin:  0px -4px 0px -4px;            /* \346\273\221\345\235\227\350\266\205\345\207\272\346\247\275\347\232\204\350\276\271\350\267\235 */\n"
"    border-radius: 5px;        /* \346\273\221\345\235\227\347\232\204\345\234\206\350\247\222 */\n"
"}\n"
"\n"
"QSlider::sub-page:vertical {\n"
"   background-color:rgb(219,219,219)\n"
"}\n"
"\n"
"QSlider::add-page:vertical {\n"
"    background-color:rgb(26,217,110);\n"
"}"));
        verticalSliderVolume->setMaximum(100);
        verticalSliderVolume->setValue(50);
        verticalSliderVolume->setOrientation(Qt::Vertical);

        verticalLayout->addWidget(verticalSliderVolume);

        labelVolume = new QLabel(frame);
        labelVolume->setObjectName(QString::fromUtf8("labelVolume"));
        sizePolicy1.setHeightForWidth(labelVolume->sizePolicy().hasHeightForWidth());
        labelVolume->setSizePolicy(sizePolicy1);
        labelVolume->setMinimumSize(QSize(40, 20));
        labelVolume->setMaximumSize(QSize(37, 16777215));
        QFont font;
        font.setPointSize(11);
        font.setBold(false);
        font.setKerning(true);
        labelVolume->setFont(font);
        labelVolume->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelVolume);

        btnVolume = new QPushButton(frame);
        btnVolume->setObjectName(QString::fromUtf8("btnVolume"));
        sizePolicy1.setHeightForWidth(btnVolume->sizePolicy().hasHeightForWidth());
        btnVolume->setSizePolicy(sizePolicy1);
        btnVolume->setMinimumSize(QSize(40, 30));
        btnVolume->setMaximumSize(QSize(40, 35));
        btnVolume->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/volume.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnVolume->setIcon(icon);
        btnVolume->setIconSize(QSize(20, 20));
        btnVolume->setCheckable(true);

        verticalLayout->addWidget(btnVolume);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(frame);


        retranslateUi(VolumeControlWidget);

        QMetaObject::connectSlotsByName(VolumeControlWidget);
    } // setupUi

    void retranslateUi(QWidget *VolumeControlWidget)
    {
        VolumeControlWidget->setWindowTitle(QCoreApplication::translate("VolumeControlWidget", "Form", nullptr));
        labelVolume->setText(QString());
#if QT_CONFIG(tooltip)
        btnVolume->setToolTip(QCoreApplication::translate("VolumeControlWidget", "\351\237\263\351\207\217", nullptr));
#endif // QT_CONFIG(tooltip)
        btnVolume->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VolumeControlWidget: public Ui_VolumeControlWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLUMECONTROLWIDGET_H
