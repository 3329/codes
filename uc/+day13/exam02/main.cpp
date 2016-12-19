#include <QApplication>
#include <QWidget>
#include <QPushButton>
int main(int args,char**argv)
{
	QApplication app(args,argv);
	QWidget win;
	win.resize(400,300);
	win.move((1024-400)/2,(768-300)/2);
	
	QPushButton btn(&win);
	btn.resize(100,30);
	btn.move(10,10);
	btn.setText("È·¶¨");
	btn.setVisible(true);	
	
	win.setVisible(true);	
	return app.exec();
}
