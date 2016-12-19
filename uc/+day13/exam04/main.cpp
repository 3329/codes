#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QTextCodec>
#include <QLineEdit>
int main(int args,char**argv)
{
	QApplication app(args,argv);
	
	QTextCodec *codec=QTextCodec::codecForName("gb2312");
	
	QTextCodec::setCodecForTr(codec);
	
	QDialog dlg;
	dlg.resize(400,300);
	dlg.move((1024-400)/2,(768-300)/2);
	
	QPushButton btn(&dlg);
	btn.resize(100,30);
	btn.move(100,100);
	btn.setText(QObject::tr("确定"));
	
	QLineEdit edt(&dlg);
	edt.resize(100,30);
	edt.move(100,200);
	edt.setText(QObject::tr("确定"));
	
	dlg.setVisible(true);
	return app.exec();
}
