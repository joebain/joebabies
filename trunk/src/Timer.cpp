#include "Timer.h"

#ifdef WIN32
	#include <windows.h>
#else
	#include <sys/time.h>
#endif

double Timer::get_time()
{
#ifdef WIN32
	SYSTEMTIME st;
	GetSystemTime(&st);
	last = ((double)st.wSecond) + ((double) st.wMilliseconds)/1000000.0;
#else
	struct timeval now;
	struct timezone tz_null;
	gettimeofday(&now,&tz_null);
	
	last = ((double) now.tv_sec) + ((double) now.tv_usec)/1000000.0;
#endif
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
