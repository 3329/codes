#include "logindlg.h"
#include <QApplication>
#include <QTextCodec>
int main(int args,char**argv)
{
	QApplication app(args,argv);
	QTextCodec *codec
		=QTextCodec::codecForName("gb2312");
	QTextCodec::setCodecForTr(codec);
	
	LoginDialog dlg;
	dlg.resize(400,300);
	dlg.setVisible(true);
	
	return app.exec();
}
