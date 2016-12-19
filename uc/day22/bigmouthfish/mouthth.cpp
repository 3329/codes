#include "mouthth.h"
void MouthTh::run()
{
	while(!isstop)
	{
		QThread::msleep(80);
		//emit openmouth();	
	}
}
