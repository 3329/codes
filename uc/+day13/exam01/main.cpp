#include <QApplication>
#include <QDialog>
int main(int args,char **argv)
{
	//qmake -project
	//qmake **.pro
	//make
	//ִ�г���
	QApplication app(args,argv);
	////////////////////////////
	
	QDialog dlg;
	dlg.setVisible(true);
	
	////////////////////////////	
	return app.exec();//�ȴ����߳̽���
}
