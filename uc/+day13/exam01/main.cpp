#include <QApplication>
#include <QDialog>
int main(int args,char **argv)
{
	//qmake -project
	//qmake **.pro
	//make
	//执行程序
	QApplication app(args,argv);
	////////////////////////////
	
	QDialog dlg;
	dlg.setVisible(true);
	
	////////////////////////////	
	return app.exec();//等待子线程结束
}
