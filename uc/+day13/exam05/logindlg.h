#ifndef LOGIN_DLG_H
#define LOGIN_DLG_H
#include <QDialog> 
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
class LoginDialog : public QDialog
{
private:
	QLabel *lbluser;
	QLabel *lblpass;
	QLineEdit *edtuser;
	QLineEdit *edtpass;
	QPushButton *btnlogin;
	QPushButton *btncancel;
	
public:
	LoginDialog(QWidget *parent=NULL);
};
#endif
