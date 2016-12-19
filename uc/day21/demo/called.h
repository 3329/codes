#ifndef CALLED_H
#define CALLED_H
#include <QObject>
class Called : public QObject{
Q_OBJECT
public slots:
	void bizlog();
};
#endif
