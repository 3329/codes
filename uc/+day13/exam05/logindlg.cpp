#include "logindlg.h"
LoginDialog::LoginDialog(QWidget *parent)
	:QDialog(parent)
{
	resize(400,300);
	move((1024-400)/2,(768-300)/2);
	
	lbluser=new QLabel(this);
	lblpass=new QLabel(this);
		
	lbluser->resize(100,30);
	lbluser->move(50,40);
	
	lblpass->resize(100,30);
	lblpass->move(50,100);
	
	lbluser->setText(QObject::tr("用户:"));
	lblpass->setText(QObject::tr("口令:"));
	
	edtuser=new QLineEdit(this);
	edtpass=new QLineEdit(this);
		
	edtuser->resize(200,30);
	edtuser->move(150,40);
	
	edtpass->resize(200,30);
	edtpass->move(150,100);
	
	btnlogin=new QPushButton(this);
	btncancel=new QPushButton(this);
	
	btnlogin->resize(60,30);
	btnlogin->move(90,210);
	
	btncancel->resize(60,30);
	btncancel->move(250,210);
	
	btnlogin->setText(QObject::tr("登录"));
	btncancel->setText(QObject::tr("取消"));
}

