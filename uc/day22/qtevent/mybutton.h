#ifndef MY_BUTTON_H
#define MY_BUTTON_H
#include <QPushButton>
#include <QPaintEvent>
class MyButton : public QPushButton{
public:
	MyButton(QWidget *parent=0);
public:
	void paintEvent(QPaintEvent *e); 
};
#endif
