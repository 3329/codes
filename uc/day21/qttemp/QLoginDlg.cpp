#include "QLoginDlg.h"
QLoginDlg::QLoginDlg(QWidget *parent)
	:QDialog(parent)
{
	/*����ʵ����*/
	
	lblUser=new QLabel(tr("<img src='../p1.png' width=80  height=30/>"),this);
	

	edtUser=new QLineEdit(tr("�����û���"),this); 	
	btnLogin=new QPushButton(tr("��¼"),this);
	/*�����ʼ��:��С,λ��*/
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
	
	this->setToolTip(tr("<s>������ʾ</s>"));
	btnLogin->setToolTip(tr("���ǵ�¼"));
	
	QIcon ico("../p1.png");
	this->setWindowIcon(ico);
	/*
	QFont font(tr("�Ķ�PL�п�Uni"),20,100,true);
	lblUser->setFont(font);
	*/
	this->setWindowTitle(tr("BOSS-��¼����"));
	this->setVisible(true);
	
}
QLoginDlg::~QLoginDlg()
{
	delete lblUser;
	delete edtUser;
	delete btnLogin;
}
