#ifndef MY_DLG_H
#define MY_DLG_H
#include <QDialog>
#include "mybutton.h" 
class MyDlg : public QDialog{
Q_OBJECT
public:
	MyButton *btn;
	
	MyButton *btn2;
		
	MyDlg(QWidget *parent=0);
	~MyDlg();
public slots:
	void showM();	
};
#endif
