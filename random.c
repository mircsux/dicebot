/* Random stuff */

#include "includes.h"

int		get_random_number 	(int max)
{
	int 	result;

	result = ((float) max) * (rand() / (RAND_MAX + 1.0));

	if (result >= max)  // Paranoid check.
		result = max -1;

	return (result);
}

