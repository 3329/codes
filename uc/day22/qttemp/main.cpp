#include <QApplication>
#include <QTextCodec>
#include "QLoginDlg.h"
int main(int args,char **argv)
{	
	QApplication app(args,argv);
	QTextCodec *codec=QTextCodec::codecForName("gb2312");
	QTextCodec::setCodecForTr(codec);	
	/*启动主窗体或者主对话框*/
	QLoginDlg dlg;	
	return app.exec();
}

