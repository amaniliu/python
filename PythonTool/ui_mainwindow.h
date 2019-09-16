/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *btn_open;
    QToolButton *btn_import;
    QToolButton *btn_export;
    QComboBox *comboBox_gap;
    QSpacerItem *horizontalSpacer_4;
    QGraphicsView *graphicsView;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *btn_l_ll;
    QToolButton *btn_l_dd;
    QToolButton *btn_l_l;
    QToolButton *btn_r_u;
    QToolButton *btn_l_d;
    QToolButton *btn_r_ll;
    QToolButton *btn_r_dd;
    QToolButton *btn_r_r;
    QToolButton *btn_r_uu;
    QToolButton *btn_r_l;
    QToolButton *btn_l_r;
    QToolButton *btn_l_rr;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *btn_l_u;
    QToolButton *btn_l_uu;
    QToolButton *btn_r_d;
    QToolButton *btn_r_rr;
    QSpacerItem *horizontalSpacer_3;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *lineEdit1;
    QToolButton *btn_dir_black;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLineEdit *lineEdit2;
    QToolButton *btn_path_white;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_7;
    QToolButton *btn_export_correct;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(723, 519);
        horizontalLayout = new QHBoxLayout(MainWindow);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(MainWindow);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btn_open = new QToolButton(groupBox);
        btn_open->setObjectName(QString::fromUtf8("btn_open"));

        horizontalLayout_2->addWidget(btn_open);

        btn_import = new QToolButton(groupBox);
        btn_import->setObjectName(QString::fromUtf8("btn_import"));

        horizontalLayout_2->addWidget(btn_import);

        btn_export = new QToolButton(groupBox);
        btn_export->setObjectName(QString::fromUtf8("btn_export"));

        horizontalLayout_2->addWidget(btn_export);

        comboBox_gap = new QComboBox(groupBox);
        comboBox_gap->setObjectName(QString::fromUtf8("comboBox_gap"));

        horizontalLayout_2->addWidget(comboBox_gap);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addWidget(groupBox);

        graphicsView = new QGraphicsView(tab);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

        btn_l_ll = new QToolButton(tab);
        btn_l_ll->setObjectName(QString::fromUtf8("btn_l_ll"));

        gridLayout->addWidget(btn_l_ll, 3, 1, 1, 1);

        btn_l_dd = new QToolButton(tab);
        btn_l_dd->setObjectName(QString::fromUtf8("btn_l_dd"));

        gridLayout->addWidget(btn_l_dd, 5, 3, 1, 1);

        btn_l_l = new QToolButton(tab);
        btn_l_l->setObjectName(QString::fromUtf8("btn_l_l"));

        gridLayout->addWidget(btn_l_l, 3, 2, 1, 1);

        btn_r_u = new QToolButton(tab);
        btn_r_u->setObjectName(QString::fromUtf8("btn_r_u"));

        gridLayout->addWidget(btn_r_u, 2, 9, 1, 1);

        btn_l_d = new QToolButton(tab);
        btn_l_d->setObjectName(QString::fromUtf8("btn_l_d"));

        gridLayout->addWidget(btn_l_d, 4, 3, 1, 1);

        btn_r_ll = new QToolButton(tab);
        btn_r_ll->setObjectName(QString::fromUtf8("btn_r_ll"));

        gridLayout->addWidget(btn_r_ll, 3, 7, 1, 1);

        btn_r_dd = new QToolButton(tab);
        btn_r_dd->setObjectName(QString::fromUtf8("btn_r_dd"));

        gridLayout->addWidget(btn_r_dd, 5, 9, 1, 1);

        btn_r_r = new QToolButton(tab);
        btn_r_r->setObjectName(QString::fromUtf8("btn_r_r"));

        gridLayout->addWidget(btn_r_r, 3, 10, 1, 1);

        btn_r_uu = new QToolButton(tab);
        btn_r_uu->setObjectName(QString::fromUtf8("btn_r_uu"));

        gridLayout->addWidget(btn_r_uu, 1, 9, 1, 1);

        btn_r_l = new QToolButton(tab);
        btn_r_l->setObjectName(QString::fromUtf8("btn_r_l"));

        gridLayout->addWidget(btn_r_l, 3, 8, 1, 1);

        btn_l_r = new QToolButton(tab);
        btn_l_r->setObjectName(QString::fromUtf8("btn_l_r"));

        gridLayout->addWidget(btn_l_r, 3, 4, 1, 1);

        btn_l_rr = new QToolButton(tab);
        btn_l_rr->setObjectName(QString::fromUtf8("btn_l_rr"));

        gridLayout->addWidget(btn_l_rr, 3, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 6, 1, 1);

        btn_l_u = new QToolButton(tab);
        btn_l_u->setObjectName(QString::fromUtf8("btn_l_u"));

        gridLayout->addWidget(btn_l_u, 2, 3, 1, 1);

        btn_l_uu = new QToolButton(tab);
        btn_l_uu->setObjectName(QString::fromUtf8("btn_l_uu"));

        gridLayout->addWidget(btn_l_uu, 1, 3, 1, 1);

        btn_r_d = new QToolButton(tab);
        btn_r_d->setObjectName(QString::fromUtf8("btn_r_d"));

        gridLayout->addWidget(btn_r_d, 4, 9, 1, 1);

        btn_r_rr = new QToolButton(tab);
        btn_r_rr->setObjectName(QString::fromUtf8("btn_r_rr"));

        gridLayout->addWidget(btn_r_rr, 3, 11, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 12, 1, 1);


        verticalLayout->addLayout(gridLayout);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        lineEdit1 = new QLineEdit(groupBox_2);
        lineEdit1->setObjectName(QString::fromUtf8("lineEdit1"));
        lineEdit1->setReadOnly(true);

        horizontalLayout_4->addWidget(lineEdit1);

        btn_dir_black = new QToolButton(groupBox_2);
        btn_dir_black->setObjectName(QString::fromUtf8("btn_dir_black"));

        horizontalLayout_4->addWidget(btn_dir_black);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        lineEdit2 = new QLineEdit(groupBox_2);
        lineEdit2->setObjectName(QString::fromUtf8("lineEdit2"));
        lineEdit2->setReadOnly(true);

        horizontalLayout_5->addWidget(lineEdit2);

        btn_path_white = new QToolButton(groupBox_2);
        btn_path_white->setObjectName(QString::fromUtf8("btn_path_white"));

        horizontalLayout_5->addWidget(btn_path_white);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_6->addWidget(checkBox);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        btn_export_correct = new QToolButton(groupBox_2);
        btn_export_correct->setObjectName(QString::fromUtf8("btn_export_correct"));

        horizontalLayout_6->addWidget(btn_export_correct);


        verticalLayout_3->addLayout(horizontalLayout_6);


        verticalLayout_2->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256(Settings)", nullptr));
        btn_open->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\345\233\276\347\211\207\n"
"(Open File)", nullptr));
        btn_import->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\347\216\260\346\234\211\350\247\204\345\210\231\n"
"(Import Existing Rule)", nullptr));
        btn_export->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\350\247\204\345\210\231\n"
"(Export Rule)", nullptr));
        btn_l_ll->setText(QCoreApplication::translate("MainWindow", "\343\200\212", nullptr));
        btn_l_dd->setText(QCoreApplication::translate("MainWindow", "\357\270\276", nullptr));
        btn_l_l->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        btn_r_u->setText(QCoreApplication::translate("MainWindow", "\357\270\277", nullptr));
        btn_l_d->setText(QCoreApplication::translate("MainWindow", "\357\271\200", nullptr));
        btn_r_ll->setText(QCoreApplication::translate("MainWindow", "\343\200\212", nullptr));
        btn_r_dd->setText(QCoreApplication::translate("MainWindow", "\357\270\276", nullptr));
        btn_r_r->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        btn_r_uu->setText(QCoreApplication::translate("MainWindow", "\357\270\275", nullptr));
        btn_r_l->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        btn_l_r->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        btn_l_rr->setText(QCoreApplication::translate("MainWindow", "\343\200\213", nullptr));
        btn_l_u->setText(QCoreApplication::translate("MainWindow", "\357\270\277", nullptr));
        btn_l_uu->setText(QCoreApplication::translate("MainWindow", "\357\270\275", nullptr));
        btn_r_d->setText(QCoreApplication::translate("MainWindow", "\357\271\200", nullptr));
        btn_r_rr->setText(QCoreApplication::translate("MainWindow", "\343\200\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\346\213\274\346\216\245(Stitch)", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256(Settings)", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\351\273\221\345\233\276(Black Image)", nullptr));
        btn_dir_black->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\231\275\345\233\276(White Image)", nullptr));
        btn_path_white->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\346\266\210\351\231\244\351\273\221\350\276\271(Clear Black Borders)", nullptr));
        btn_export_correct->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\240\241\346\255\243\346\225\260\346\215\256\n"
"(Export)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\346\240\241\346\255\243(Correct)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
