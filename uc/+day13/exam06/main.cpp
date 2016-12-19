#include <QApplication>
#include "dlglogin.h"
int main(int args,char **argv)
{
	QApplication app(args,argv);
	DlgLogin dlg;
	dlg.setVisible(true);
	
	return app.exec();
}
