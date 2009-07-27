#include "Timer.h"

#include <sys/time.h>

double Timer::get_time()
{
	struct timeval now;
	struct timezone tz_null;
	gettimeofday(&now,&tz_null);
	
	last = ((double) now.tv_sec) + ((double) now.tv_usec)/1000000.0;
	
	return last;
}

double Timer::time_since(double time)
{
	return get_time() - time;
}

double Timer::time_since_last()
{
	double tmp = last;
	last = get_time();
	return  last - tmp;
}
