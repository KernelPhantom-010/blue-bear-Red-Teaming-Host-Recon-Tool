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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_main;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_tab1;
    QLabel *label;
    QTableWidget *tableWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_tab2;
    QTreeWidget *tableWidget_2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_tab3;
    QTreeWidget *treeWidget;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_tab4;
    QTabWidget *tabWidget_2;
    QWidget *tab_7;
    QVBoxLayout *verticalLayout_tab7;
    QTreeWidget *treeWidget_2;
    QWidget *tab_8;
    QVBoxLayout *verticalLayout_tab8;
    QPlainTextEdit *plainTextEdit;
    QWidget *tab_9;
    QVBoxLayout *verticalLayout_tab9;
    QTreeWidget *treeWidget_3;
    QWidget *tab_10;
    QVBoxLayout *verticalLayout_tab10;
    QTreeWidget *treeWidget_4;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_tab5;
    QTreeWidget *treeWidget_5;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_tab6;
    QTreeWidget *treeWidget_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1206, 723);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_main = new QVBoxLayout(centralwidget);
        verticalLayout_main->setObjectName("verticalLayout_main");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout_tab1 = new QVBoxLayout(tab);
        verticalLayout_tab1->setObjectName("verticalLayout_tab1");
        label = new QLabel(tab);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        font.setBold(true);
        label->setFont(font);

        verticalLayout_tab1->addWidget(label);

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
        tableWidget->setFont(font);
        tableWidget->setLineWidth(5);
        tableWidget->setMidLineWidth(0);
        tableWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(130);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setStretchLastSection(false);

        verticalLayout_tab1->addWidget(tableWidget);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_tab2 = new QVBoxLayout(tab_2);
        verticalLayout_tab2->setObjectName("verticalLayout_tab2");
        tableWidget_2 = new QTreeWidget(tab_2);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setColumnCount(3);

        verticalLayout_tab2->addWidget(tableWidget_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        verticalLayout_tab3 = new QVBoxLayout(tab_3);
        verticalLayout_tab3->setObjectName("verticalLayout_tab3");
        treeWidget = new QTreeWidget(tab_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("Process"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");

        verticalLayout_tab3->addWidget(treeWidget);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        verticalLayout_tab4 = new QVBoxLayout(tab_4);
        verticalLayout_tab4->setObjectName("verticalLayout_tab4");
        tabWidget_2 = new QTabWidget(tab_4);
        tabWidget_2->setObjectName("tabWidget_2");
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        verticalLayout_tab7 = new QVBoxLayout(tab_7);
        verticalLayout_tab7->setObjectName("verticalLayout_tab7");
        treeWidget_2 = new QTreeWidget(tab_7);
        treeWidget_2->setObjectName("treeWidget_2");

        verticalLayout_tab7->addWidget(treeWidget_2);

        tabWidget_2->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        verticalLayout_tab8 = new QVBoxLayout(tab_8);
        verticalLayout_tab8->setObjectName("verticalLayout_tab8");
        plainTextEdit = new QPlainTextEdit(tab_8);
        plainTextEdit->setObjectName("plainTextEdit");

        verticalLayout_tab8->addWidget(plainTextEdit);

        tabWidget_2->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName("tab_9");
        verticalLayout_tab9 = new QVBoxLayout(tab_9);
        verticalLayout_tab9->setObjectName("verticalLayout_tab9");
        treeWidget_3 = new QTreeWidget(tab_9);
        treeWidget_3->setObjectName("treeWidget_3");

        verticalLayout_tab9->addWidget(treeWidget_3);

        tabWidget_2->addTab(tab_9, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName("tab_10");
        verticalLayout_tab10 = new QVBoxLayout(tab_10);
        verticalLayout_tab10->setObjectName("verticalLayout_tab10");
        treeWidget_4 = new QTreeWidget(tab_10);
        treeWidget_4->setObjectName("treeWidget_4");

        verticalLayout_tab10->addWidget(treeWidget_4);

        tabWidget_2->addTab(tab_10, QString());

        verticalLayout_tab4->addWidget(tabWidget_2);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        verticalLayout_tab5 = new QVBoxLayout(tab_5);
        verticalLayout_tab5->setObjectName("verticalLayout_tab5");
        treeWidget_5 = new QTreeWidget(tab_5);
        treeWidget_5->setObjectName("treeWidget_5");

        verticalLayout_tab5->addWidget(treeWidget_5);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        verticalLayout_tab6 = new QVBoxLayout(tab_6);
        verticalLayout_tab6->setObjectName("verticalLayout_tab6");
        treeWidget_6 = new QTreeWidget(tab_6);
        treeWidget_6->setObjectName("treeWidget_6");

        verticalLayout_tab6->addWidget(treeWidget_6);

        tabWidget->addTab(tab_6, QString());

        verticalLayout_main->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1206, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(5);
        tabWidget_2->setCurrentIndex(0);


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
        QTreeWidgetItem *___qtreewidgetitem5 = treeWidget_5->headerItem();
        ___qtreewidgetitem5->setText(6, QCoreApplication::translate("MainWindow", "Description", nullptr));
        ___qtreewidgetitem5->setText(5, QCoreApplication::translate("MainWindow", "Account", nullptr));
        ___qtreewidgetitem5->setText(4, QCoreApplication::translate("MainWindow", "Binary Path", nullptr));
        ___qtreewidgetitem5->setText(3, QCoreApplication::translate("MainWindow", "StartType", nullptr));
        ___qtreewidgetitem5->setText(2, QCoreApplication::translate("MainWindow", "Type", nullptr));
        ___qtreewidgetitem5->setText(1, QCoreApplication::translate("MainWindow", "Status", nullptr));
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("MainWindow", "Name / DisplayName", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Service Discovery", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = treeWidget_6->headerItem();
        ___qtreewidgetitem6->setText(4, QCoreApplication::translate("MainWindow", "WMI Event Subscriptions", nullptr));
        ___qtreewidgetitem6->setText(3, QCoreApplication::translate("MainWindow", "Startup Folder", nullptr));
        ___qtreewidgetitem6->setText(2, QCoreApplication::translate("MainWindow", "Scheduled Tasks", nullptr));
        ___qtreewidgetitem6->setText(1, QCoreApplication::translate("MainWindow", "Run-Keys (current User)", nullptr));
        ___qtreewidgetitem6->setText(0, QCoreApplication::translate("MainWindow", "Run-Keys (all Users)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Persistence", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
