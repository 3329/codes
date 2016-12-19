/********************************************************************************
** Form generated from reading ui file 'jfq.ui'
**
** Created: Fri Apr 29 19:12:11 2011
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef JFQ_H
#define JFQ_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_JFQDlg
{
public:
    QLineEdit *edtAdded;
    QLineEdit *edtAdd;
    QLabel *lblAdd;
    QPushButton *btnEqual;
    QLabel *lblResult;

    void setupUi(QDialog *JFQDlg)
    {
    if (JFQDlg->objectName().isEmpty())
        JFQDlg->setObjectName(QString::fromUtf8("JFQDlg"));
    JFQDlg->resize(480, 88);
    edtAdded = new QLineEdit(JFQDlg);
    edtAdded->setObjectName(QString::fromUtf8("edtAdded"));
    edtAdded->setGeometry(QRect(11, 28, 123, 31));
    edtAdd = new QLineEdit(JFQDlg);
    edtAdd->setObjectName(QString::fromUtf8("edtAdd"));
    edtAdd->setGeometry(QRect(170, 30, 113, 30));
    lblAdd = new QLabel(JFQDlg);
    lblAdd->setObjectName(QString::fromUtf8("lblAdd"));
    lblAdd->setGeometry(QRect(140, 30, 21, 22));
    QFont font;
    font.setPointSize(14);
    font.setBold(true);
    font.setWeight(75);
    lblAdd->setFont(font);
    lblAdd->setAlignment(Qt::AlignCenter);
    btnEqual = new QPushButton(JFQDlg);
    btnEqual->setObjectName(QString::fromUtf8("btnEqual"));
    btnEqual->setGeometry(QRect(290, 30, 31, 32));
    btnEqual->setFont(font);
    btnEqual->setFlat(true);
    lblResult = new QLabel(JFQDlg);
    lblResult->setObjectName(QString::fromUtf8("lblResult"));
    lblResult->setGeometry(QRect(330, 30, 131, 31));
    lblResult->setFrameShape(QFrame::Box);
    lblResult->setFrameShadow(QFrame::Raised);

    retranslateUi(JFQDlg);

    QMetaObject::connectSlotsByName(JFQDlg);
    } // setupUi

    void retranslateUi(QDialog *JFQDlg)
    {
    JFQDlg->setWindowTitle(QApplication::translate("JFQDlg", "QT\350\256\241\347\256\227\345\231\250", 0, QApplication::UnicodeUTF8));
    lblAdd->setText(QApplication::translate("JFQDlg", "+", 0, QApplication::UnicodeUTF8));
    btnEqual->setText(QApplication::translate("JFQDlg", "=", 0, QApplication::UnicodeUTF8));
    lblResult->setText(QApplication::translate("JFQDlg", "\347\273\223\346\236\234", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(JFQDlg);
    } // retranslateUi

};

namespace Ui {
    class JFQDlg: public Ui_JFQDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // JFQ_H
