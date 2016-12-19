#include "jfqdlg.h"
void QJfqDlg::GetResult(){
	/*得到加数*/
	QString strAdd=ui->edtAdd->text();
	int nAdd=strAdd.toInt();
	/*得到被加数*/
	QString strAdded=ui->edtAdded->text();
	int nAdded=strAdded.toInt();
	/*计算和*/
	int nResult=nAdd+nAdded;
	/*显示*/
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
