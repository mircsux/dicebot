/* Dice game */

#include "includes.h"

void 	show_players (char *chan)
{
	/* Show list of players */
	struct players 	*c = NULL;
	
	c = playerhead;
	
	while (c != NULL)
	{
		/* Go through the list of players, do stuff accordingly */
		
	}
	
}	

void	do_roll (char *cmd, char *chan, char *who, char *rest)
{
    char *number = NULL;
	char *dice_count = NULL;
	long  count = 0, num = 0;

	if ((dice_count = strtok (rest, "d")) == NULL)
		return;
	
	if ((count = strtol (dice_count, (char **) NULL, count)) < 1)
		return;

	if ((number = strtok (NULL, "")) == NULL)
		return;

	if ((num = strtol (number, (char **) NULL, num)) < 1)
		return;

	printf ("count = %ld, num = %ld\n", count, num);

	roll_dice (chan, count, num);

}


void	reinit_players (void)
{
	struct players	*c = playerhead;
	
	while (c != NULL)
	{
		c->playing = 0;
		c = c->next;
	}
}

void 	roll_dice (char *chan, long count, long num)
{
	long i = 0, j = 0, k = 0;

	/* Dice syntax = roll 1d100 */

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
		
	
	
