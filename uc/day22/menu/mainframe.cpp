#include "mainframe.h"
#include <QMessageBox>
ChatServer::ChatServer()
{
	resize(500,400);

	center=new QWidget(this);
	setCentralWidget (center);
	edt=new QTextEdit(center);
	txt=new QLineEdit(center);
	btn=new QPushButton(center);

	vlay=new QVBoxLayout(center);
	hlay=new QHBoxLayout;
	vlay->addWidget(edt);
	hlay->addWidget(txt);
	hlay->addWidget(btn);
	vlay->addWidget(edt);
	vlay->addLayout(hlay);

	status=new QStatusBar;
	lblinfo=new QLabel("information");
	lbltime=new QLabel("2010-10-08");
	lblinfo->setFrameStyle(QFrame::Box);
	status->addPermanentWidget(lblinfo,300);
	status->addPermanentWidget(lbltime,300);
	this->setStatusBar(status);

	toolbar=new QToolBar;
	act=new QAction("OK",toolbar);
	toolbar->addAction(act);
	addToolBar(toolbar);

	menubar=new QMenuBar;
	menu=new QMenu("File");
	menu->addAction(act);
	menubar->addAction(menu->menuAction());
	setMenuBar(menubar);
	connect(act,SIGNAL(triggered()),this,SLOT(onOk()));
	edt->setTextColor(QColor(0,255,255));
	edt->insertPlainText("Hello\n");
	edt->setTextColor ( QColor(0,255,0));
	edt->insertPlainText("World");//<font color=red>Hello</font>World
	edt->clear();


}
void ChatServer::onOk()
{
	QMessageBox::information(NULL,"OK","OK");
}
