#include <QApplication>
#include <QWidget>
#include <QPushButton>
int main(int args,char **argv)
{
	QApplication app(args,argv);
	QWidget w;
	
	QPushButton btn("OK",&w);
	
	w.resize(400,400);
	w.move((1024-400)/2,(768-400)/2);
	
	btn.resize(100,30);
	btn.move(10,10);
		
	w.setVisible(true);
	return app.exec();
}
