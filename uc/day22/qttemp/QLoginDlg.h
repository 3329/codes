#ifndef QDIALOG_LOGIN_H
#define QDIALOG_LOGIN_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton> 
class QLoginDlg : public QDialog{
Q_OBJECT
private:
	QLabel 			*lblUser;
	QLineEdit 	*edtUser;
	QPushButton	*btnLogin;
public:
	QLoginDlg(QWidget *parent=0);	
	~QLoginDlg();
public slots:
	void showMessage();	
};
#endif
