#ifndef JFQ_DLG_H
#define JFQ_DLG_H
#include <QDialog>
#include "jfq.h"
class QJfqDlg : public QDialog{
Q_OBJECT
public:
	Ui_JFQDlg  *ui;
	QJfqDlg(QWidget *parent=0);
	~QJfqDlg();
public slots:
	void GetResult();
};
#endif
