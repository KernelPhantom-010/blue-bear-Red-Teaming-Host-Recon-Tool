/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QTableWidget *tableWidget;
    QWidget *tab_2;
    QTreeWidget *tableWidget_2;
    QWidget *tab_3;
    QTreeWidget *treeWidget;
    QWidget *tab_4;
    QTabWidget *tabWidget_2;
    QWidget *tab_7;
    QTreeWidget *treeWidget_2;
    QWidget *tab_8;
    QPlainTextEdit *plainTextEdit;
    QWidget *tab_9;
    QTreeWidget *treeWidget_3;
    QWidget *tab_10;
    QTreeWidget *treeWidget_4;
    QWidget *tab_5;
    QWidget *tab_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(838, 425);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 10, 861, 711));
        tab = new QWidget();
        tab->setObjectName("tab");
        label = new QLabel(tab);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 121, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        font.setBold(true);
        label->setFont(font);
        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(0, 4, __qtablewidgetitem16);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 50, 791, 291));
        tableWidget->setFont(font);
        tableWidget->setLineWidth(5);
        tableWidget->setMidLineWidth(0);
        tableWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(130);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setStretchLastSection(false);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tableWidget_2 = new QTreeWidget(tab_2);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(10, 10, 801, 331));
        tableWidget_2->setColumnCount(3);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        treeWidget = new QTreeWidget(tab_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("Process"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setGeometry(QRect(10, 10, 811, 331));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tabWidget_2 = new QTabWidget(tab_4);
        tabWidget_2->setObjectName("tabWidget_2");
        tabWidget_2->setGeometry(QRect(0, 10, 821, 341));
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        treeWidget_2 = new QTreeWidget(tab_7);
        treeWidget_2->setObjectName("treeWidget_2");
        treeWidget_2->setGeometry(QRect(10, 10, 801, 291));
        tabWidget_2->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        plainTextEdit = new QPlainTextEdit(tab_8);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(10, 10, 801, 291));
        tabWidget_2->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName("tab_9");
        treeWidget_3 = new QTreeWidget(tab_9);
        treeWidget_3->setObjectName("treeWidget_3");
        treeWidget_3->setGeometry(QRect(10, 10, 801, 291));
        tabWidget_2->addTab(tab_9, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName("tab_10");
        treeWidget_4 = new QTreeWidget(tab_10);
        treeWidget_4->setObjectName("treeWidget_4");
        treeWidget_4->setGeometry(QRect(0, 0, 811, 301));
        tabWidget_2->addTab(tab_10, QString());
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        tabWidget->addTab(tab_6, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 838, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);
        tabWidget_2->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Blue Bear", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Host Information", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Hostname", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Windows Version/Build", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Architecture", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Domain/Workgroup", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Users Found", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "System Uptime", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(0, 1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "gf", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(0, 2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "gf", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(0, 3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "No Domain Found!", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(0, 4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Host", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = tableWidget_2->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("MainWindow", "Modules/DLL's", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "PID", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Process ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Process Discovery", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->headerItem();
        ___qtreewidgetitem1->setText(5, QCoreApplication::translate("MainWindow", "Integrity Level", nullptr));
        ___qtreewidgetitem1->setText(4, QCoreApplication::translate("MainWindow", "Token-Owner", nullptr));
        ___qtreewidgetitem1->setText(3, QCoreApplication::translate("MainWindow", "SeDebugPrivilege?", nullptr));
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("MainWindow", "SeImpersonatePrivilege?", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("MainWindow", "PID", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Token Discovery", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget_2->headerItem();
        ___qtreewidgetitem2->setText(6, QCoreApplication::translate("MainWindow", "PID", nullptr));
        ___qtreewidgetitem2->setText(5, QCoreApplication::translate("MainWindow", "Process", nullptr));
        ___qtreewidgetitem2->setText(4, QCoreApplication::translate("MainWindow", "State", nullptr));
        ___qtreewidgetitem2->setText(3, QCoreApplication::translate("MainWindow", "Remote Port", nullptr));
        ___qtreewidgetitem2->setText(2, QCoreApplication::translate("MainWindow", "Remote IP", nullptr));
        ___qtreewidgetitem2->setText(1, QCoreApplication::translate("MainWindow", "Local Port", nullptr));
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("MainWindow", "Local IP", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_7), QCoreApplication::translate("MainWindow", "Active Connections catched", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_8), QCoreApplication::translate("MainWindow", "DNS-Cache", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = treeWidget_3->headerItem();
        ___qtreewidgetitem3->setText(3, QCoreApplication::translate("MainWindow", "Metric", nullptr));
        ___qtreewidgetitem3->setText(2, QCoreApplication::translate("MainWindow", "Gateway", nullptr));
        ___qtreewidgetitem3->setText(1, QCoreApplication::translate("MainWindow", "Prefix", nullptr));
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("MainWindow", "Destination ", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_9), QCoreApplication::translate("MainWindow", "Subnet Scraping", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidget_4->headerItem();
        ___qtreewidgetitem4->setText(3, QCoreApplication::translate("MainWindow", "Addresses", nullptr));
        ___qtreewidgetitem4->setText(2, QCoreApplication::translate("MainWindow", "OperStatus", nullptr));
        ___qtreewidgetitem4->setText(1, QCoreApplication::translate("MainWindow", "Description", nullptr));
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("MainWindow", "Adapter Name", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_10), QCoreApplication::translate("MainWindow", "Interfaces", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Network Discovery", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Service Discovery", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Persistence", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
