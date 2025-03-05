
#include "philo.h"

int get_left_fork(int id, int total);
{
	if(id == 1)
		return (total);
	else
		return(id - 1);
}

int get_right_fork(int id, int total)
{
	if(id == total)
		return (1);
	else
		return (id + 1);
}