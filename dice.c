/* Dice game */

#include "includes.h"

void roll_dice (char *chan, long count, long num)
{
	long i = 0, j = 0, k = 0;

	/* Dice syntax = !roll 1d100 */

	char	DATA [STRING_LONG] = { "\0" };

	/* Sanity check. */

	srand (time (NULL));

	if (*chan != '#')
	{
		S ("PRIVMSG %s :Sanity check failed!\n", chan);
		return;
	}

	if (count > 100)
	{
		S ("PRIVMSG %s :I can't hold that many dice.\n", chan);
		return;
	}

	while (count-- > 0)
	{
		i = (rand() % num) + 1;
		j = j + i;
		k++;
		sprintf (DATA, "%s%s%ld", DATA, (k == 0) ? "" : " ", i);
			
		if (strlen (DATA) >= STRING_LONG)
			break;
	}

	S ("PRIVMSG %s :%ld (%s )\n", chan, j, DATA);
}
		
	
	
