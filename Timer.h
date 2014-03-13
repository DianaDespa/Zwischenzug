#include <stdio.h>
#include <sys/timeb.h>

class Timer{
	
	int startTime, stopTime, currentTime;
	
	struct timeb startSysTime, stopSysTime, currentSysTime;
	bool isRunning;
	
	Timer();
	void startTimer();
	void stopTimer();
	void resetTimer();
	void displayTime();
	

};