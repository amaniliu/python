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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
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
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QComboBox *comboBox;
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
        toolButton = new QToolButton(groupBox);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        horizontalLayout_2->addWidget(toolButton);

        toolButton_2 = new QToolButton(groupBox);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));

        horizontalLayout_2->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(groupBox);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));

        horizontalLayout_2->addWidget(toolButton_3);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


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

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

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
        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btn_l_ll->setText(QCoreApplication::translate("MainWindow", "<<", nullptr));
        btn_l_dd->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btn_l_l->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        btn_r_u->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btn_l_d->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btn_r_ll->setText(QCoreApplication::translate("MainWindow", "<<", nullptr));
        btn_r_dd->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btn_r_r->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        btn_r_uu->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btn_r_l->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        btn_l_r->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        btn_l_rr->setText(QCoreApplication::translate("MainWindow", ">>", nullptr));
        btn_l_u->setText(QCoreApplication::translate("MainWindow", "d", nullptr));
        btn_l_uu->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btn_r_d->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btn_r_rr->setText(QCoreApplication::translate("MainWindow", ">>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\346\213\274\346\216\245(Stitch)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\346\240\241\346\255\243(Correct)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
