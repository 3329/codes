#ifndef QDIALOG_LOGIN_H
#define QDIALOG_LOGIN_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton> 
class QLoginDlg : public QDialog{
private:
	QLabel 			*lblUser;
	QLineEdit 	*edtUser;
	QPushButton	*btnLogin;
public:
	QLoginDlg(QWidget *parent=0);	
	~QLoginDlg();
};
#endif
