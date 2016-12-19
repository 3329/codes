/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Tue Nov 23 22:56:10 2010
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *action_1;
    QAction *action_9;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(800, 600);
    action = new QAction(MainWindow);
    action->setObjectName(QString::fromUtf8("action"));
    action_2 = new QAction(MainWindow);
    action_2->setObjectName(QString::fromUtf8("action_2"));
    action_5 = new QAction(MainWindow);
    action_5->setObjectName(QString::fromUtf8("action_5"));
    action_6 = new QAction(MainWindow);
    action_6->setObjectName(QString::fromUtf8("action_6"));
    action_7 = new QAction(MainWindow);
    action_7->setObjectName(QString::fromUtf8("action_7"));
    action_1 = new QAction(MainWindow);
    action_1->setObjectName(QString::fromUtf8("action_1"));
    action_9 = new QAction(MainWindow);
    action_9->setObjectName(QString::fromUtf8("action_9"));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    verticalLayoutWidget = new QWidget(centralwidget);
    verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(60, 60, 381, 291));
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    textEdit = new QTextEdit(verticalLayoutWidget);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));

    verticalLayout->addWidget(textEdit);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    lineEdit = new QLineEdit(verticalLayoutWidget);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    horizontalLayout->addWidget(lineEdit);

    pushButton = new QPushButton(verticalLayoutWidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    horizontalLayout->addWidget(pushButton);


    verticalLayout->addLayout(horizontalLayout);

    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 25));
    menu = new QMenu(menubar);
    menu->setObjectName(QString::fromUtf8("menu"));
    menu_2 = new QMenu(menubar);
    menu_2->setObjectName(QString::fromUtf8("menu_2"));
    menu_3 = new QMenu(menubar);
    menu_3->setObjectName(QString::fromUtf8("menu_3"));
    menu_4 = new QMenu(menu_3);
    menu_4->setObjectName(QString::fromUtf8("menu_4"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);
    toolBar = new QToolBar(MainWindow);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

    menubar->addAction(menu->menuAction());
    menubar->addAction(menu_2->menuAction());
    menubar->addAction(menu_3->menuAction());
    menu->addAction(action);
    menu->addAction(action_2);
    menu->addSeparator();
    menu->addAction(action_5);
    menu_2->addAction(action_6);
    menu_2->addAction(action_7);
    menu_3->addAction(menu_4->menuAction());
    menu_4->addAction(action_9);
    menu_4->addAction(action_1);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    action->setText(QApplication::translate("MainWindow", "new", 0, QApplication::UnicodeUTF8));
    action_2->setText(QApplication::translate("MainWindow", "open", 0, QApplication::UnicodeUTF8));
    action_5->setText(QApplication::translate("MainWindow", "exit", 0, QApplication::UnicodeUTF8));
    action_6->setText(QApplication::translate("MainWindow", "copy", 0, QApplication::UnicodeUTF8));
    action_7->setText(QApplication::translate("MainWindow", "paste", 0, QApplication::UnicodeUTF8));
    action_1->setText(QApplication::translate("MainWindow", "mark2", 0, QApplication::UnicodeUTF8));
    action_9->setText(QApplication::translate("MainWindow", "mark1", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("MainWindow", "PushButton", 0, QApplication::UnicodeUTF8));
    menu->setTitle(QApplication::translate("MainWindow", "file", 0, QApplication::UnicodeUTF8));
    menu_2->setTitle(QApplication::translate("MainWindow", "edit", 0, QApplication::UnicodeUTF8));
    menu_3->setTitle(QApplication::translate("MainWindow", "about", 0, QApplication::UnicodeUTF8));
    menu_4->setTitle(QApplication::translate("MainWindow", "note", 0, QApplication::UnicodeUTF8));
    toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UIMAINWINDOW_H
