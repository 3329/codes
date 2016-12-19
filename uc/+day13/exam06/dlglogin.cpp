#include "dlglogin.h"

DlgLogin::DlgLogin(QDialog*parent)
	:QDialog(parent)
{
	ui=new Ui_LoginDialog;
	ui->setupUi(this);
}

DlgLogin::~DlgLogin()
{
	delete ui;
}
