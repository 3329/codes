#ifndef  MAIN_FRAME_H
#define  MAIN_FRAME_H
#include <QMainWindow>
#include <QStatusBar>
#include <QLabel>
#include <QToolBar>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QTextEdit>
#include <QLineEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
class ChatServer : public QMainWindow
{
Q_OBJECT
private:
	QStatusBar  *status;
	QLabel		*lblinfo;
	QLabel		*lbltime;

	QToolBar	*toolbar;
	QAction		*act;
	QMenuBar    *menubar;
	QMenu   	*menu;
	QTextEdit   *edt;
	QLineEdit   *txt;
	QPushButton *btn;
	QWidget		*center;

	QVBoxLayout  *vlay;
	QHBoxLayout  *hlay;
public:
	ChatServer();
public slots:
	void onOk();
};
#endif
