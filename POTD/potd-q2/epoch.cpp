/* Your code here! */
#include "epoch.h"

using namespace std;
int hours(time_t sec_since_epoch)
{
	int a;
	a = sec_since_epoch / 3600;
	return a;
};
int days(time_t sec_since_epoch)
{
	int b;
	b = sec_since_epoch / 3600;
	b = b / 24;
	return b;
};
int years(time_t sec_since_epoch)
{
	int c;
	c = sec_since_epoch / 3600;
	c = c / 24;
	c = c / 365;
	return c;
};








