/********************************************************************************
** Form generated from reading ui file 'login.ui'
**
** Created: Fri Nov 19 17:12:01 2010
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef LOGIN_H
#define LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *lbluser;
    QLabel *lblpass;
    QLineEdit *edtuser;
    QLineEdit *edtpass;
    QPushButton *btnlogin;
    QPushButton *btncancel;

    void setupUi(QDialog *LoginDialog)
    {
    if (LoginDialog->objectName().isEmpty())
        LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
    LoginDialog->resize(400, 262);
    lbluser = new QLabel(LoginDialog);
    lbluser->setObjectName(QString::fromUtf8("lbluser"));
    lbluser->setGeometry(QRect(70, 50, 86, 22));
    QFont font;
    font.setPointSize(14);
    font.setBold(true);
    font.setWeight(75);
    lbluser->setFont(font);
    lblpass = new QLabel(LoginDialog);
    lblpass->setObjectName(QString::fromUtf8("lblpass"));
    lblpass->setGeometry(QRect(70, 100, 85, 22));
    lblpass->setFont(font);
    edtuser = new QLineEdit(LoginDialog);
    edtuser->setObjectName(QString::fromUtf8("edtuser"));
    edtuser->setGeometry(QRect(160, 50, 181, 28));
    edtpass = new QLineEdit(LoginDialog);
    edtpass->setObjectName(QString::fromUtf8("edtpass"));
    edtpass->setGeometry(QRect(160, 100, 181, 28));
    btnlogin = new QPushButton(LoginDialog);
    btnlogin->setObjectName(QString::fromUtf8("btnlogin"));
    btnlogin->setGeometry(QRect(70, 170, 110, 32));
    btncancel = new QPushButton(LoginDialog);
    btncancel->setObjectName(QString::fromUtf8("btncancel"));
    btncancel->setGeometry(QRect(230, 170, 110, 32));

    retranslateUi(LoginDialog);

    QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
    LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    lbluser->setText(QApplication::translate("LoginDialog", "\347\224\250\346\210\267\357\274\232", 0, QApplication::UnicodeUTF8));
    lblpass->setText(QApplication::translate("LoginDialog", "\345\217\243\344\273\244\357\274\232", 0, QApplication::UnicodeUTF8));
    btnlogin->setText(QApplication::translate("LoginDialog", "\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
    btncancel->setText(QApplication::translate("LoginDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(LoginDialog);
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LOGIN_H
