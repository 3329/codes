#include "QLoginDlg.h"
QLoginDlg::QLoginDlg(QWidget *parent)
	:QDialog(parent)
{
	/*对象实例化*/
	
	lblUser=new QLabel(tr("<img src='../p1.png' width=80  height=30/>"),this);
	

	edtUser=new QLineEdit(tr("输入用户名"),this); 	
	btnLogin=new QPushButton(tr("登录"),this);
	/*对象初始化:大小,位置*/
	lblUser->resize(80,30);
	edtUser->resize(150,30);
	btnLogin->resize(100,30);
	
	lblUser->move(20,20);
	edtUser->move(100,20);
	btnLogin->move(30,120);
	
	this->resize(270,180);
	this->move((1024-270)/2,(768-180)/2);
	QCursor cur(Qt::CrossCursor);
	this->setCursor(cur);
	
	QCursor cur2(Qt::UpArrowCursor);
	btnLogin->setCursor(cur2);
	
	this->setToolTip(tr("<s>我是提示</s>"));
	btnLogin->setToolTip(tr("我是登录"));
	
	QIcon ico("../p1.png");
	this->setWindowIcon(ico);
	/*
	QFont font(tr("文鼎PL中楷Uni"),20,100,true);
	lblUser->setFont(font);
	*/
	this->setWindowTitle(tr("BOSS-登录界面"));
	this->setVisible(true);
	
}
QLoginDlg::~QLoginDlg()
{
	delete lblUser;
	delete edtUser;
	delete btnLogin;
}
