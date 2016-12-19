#include <QApplication>
#include "fishpool.h"
int main(int args,char**argv)
{
	QApplication app(args,argv);
	FishPool pool;
	pool.show();
	return app.exec();
}
