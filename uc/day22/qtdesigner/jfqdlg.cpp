#include "jfqdlg.h"
void QJfqDlg::GetResult(){
	/*�õ�����*/
	QString strAdd=ui->edtAdd->text();
	int nAdd=strAdd.toInt();
	/*�õ�������*/
	QString strAdded=ui->edtAdded->text();
	int nAdded=strAdded.toInt();
	/*�����*/
	int nResult=nAdd+nAdded;
	/*��ʾ*/
	ui->lblResult->setText(QString::number(nResult));
}

QJfqDlg::QJfqDlg(QWidget *parent){
	ui=new Ui_JFQDlg();
	ui->setupUi(this);
	this->setVisible(true);
	
	connect(ui->btnEqual,SIGNAL(clicked()),
					this,SLOT(GetResult()));
}
QJfqDlg::~QJfqDlg(){
	delete ui;
}
