#ifndef MY_LOGINDLG_H
#define MY_LOGINDLG_H
#include <QDialog>
#include "login.h"
class DlgLogin : public QDialog
{
private:
	Ui_LoginDialog *ui;
public:
	DlgLogin(QDialog*parent=NULL);
	~DlgLogin();	
};
#endif
