#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	double get_time();
	double time_since(double time);
	double time_since_last();
private:
	double last;
};

#endif
