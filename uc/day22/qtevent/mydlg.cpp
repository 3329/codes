#include "mydlg.h"
#include <QMessageBox>
void MyDlg::showM(){
	QMessageBox::information(this,"提示","鼠标事件");
}

MyDlg::MyDlg(QWidget *parent)
	:QDialog(parent){
	btn=new MyButton(this);
	btn->resize(100,30);
	btn->move(10,10);
	
	
	btn2=new MyButton(this);
	btn2->resize(100,100);
	btn2->move(150,100);
	
	resize(300,300);
	show();
	connect(btn,SIGNAL(clicked()),
					this,SLOT(showM()));
}
MyDlg::~MyDlg(){
	if(btn) delete btn;
}
