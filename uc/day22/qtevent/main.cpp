#include <QApplication>
#include "mydlg.h"
int main(int args,char**argv){
	QApplication app(args,argv);
	MyDlg dlg;	
	return app.exec();
}
