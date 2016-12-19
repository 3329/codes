#include <QApplication>
#include "mainframe.h"
int main(int args,char**argv)
{
	QApplication app(args,argv);
	ChatServer win;
	win.show();
	return app.exec();
}
