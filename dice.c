/* Dice game */

#include "includes.h"

int		is_playing 		(char	*who)
{
	/* Check if player is playing. Return 1 if so, 0 if not */
	game_players *c = players;
	c = players;
	
	while (c != NULL)
	{
		if (c->playing == 1)
			return (1);
			
		c = c->next;
	}
	
	/* No match. */
	return (0);
}
	
void 	show_players (char *chan)
{
	/* Show list of players */
	game_players 	*c = players;
	
	if (c == NULL)
	{
		S ("PRIVMSG %s :There are no players.\n", chan);
		return;
	}
	while (c != NULL)
    {
		/* Go through the list of players, do stuff accordingly */
		S ("PRIVMSG %s :%s is playing. Rolls: %ld\n", chan, c->nick, c->rollnum);
		c = c->next;
	}	
	
}	

void	do_roll (char *cmd, char *chan, char *who, char *rest)
{
    char *number = NULL;
	char *dice_count = NULL;
	long  count = 0, num = 0;

	if ((is_playing (who)) == 0)
	{
		S ("PRIVMSG %s :%s is not playing.\n", chan, who);
		return;
	}
	
	if ((dice_count = strtok (rest, "d")) == NULL)
		return;
	
	if ((count = strtol (dice_count, (char **) NULL, count)) < 1)
		return;

	if ((number = strtok (NULL, "")) == NULL)
		return;

	if ((num = strtol (number, (char **) NULL, num)) < 1)
		return;

	printf ("count = %ld, num = %ld\n", count, num);

	roll_dice (chan, who, count, num);

}


void	reinit_players (void)
{
	/* Zero everything at the beginning of the round to start
	   fresh. */
	 
	game_players	*c = players;
	
	while (c != NULL)
	{
		c->playing = 0;
		c = c->next;
	}
}

void 	roll_dice (char *chan, char *who, long count, long num)
{
	/* count is number of dice, number of sides on dice */
	long 	i = 0, j = 0, k = 0;
	long	total = 0;
	char	*ptr = NULL;
	
	game_players *c = players;

	rolls  *rolls;

	/* Dice syntax = roll 1d100 */

	char	DATA [STRING_LONG] = { "\0" };

	srand (time (NULL));

		/* Sanity check. */
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
		/* Need a positive number, no 0. */
		i = (rand() % num) + 1;
		j += i;
		sprintf (DATA, "%s%s%ld", DATA, (k == 0) ? "" : " ", i);
		
		k++;	
		if (strlen (DATA) >= STRING_LONG)
			break;
	}

	while (c)
	{
		if (stricmp (c->nick, who) == 0)
		{
			c->rollnum++;
			c->rolltotal += j;
			k = c->rolltotal;
			break;
		}
		c = c->next;
	}

	/* FIXME: Kludge to remove space from beginning of DATA. */
	ptr = DATA;
	if (*ptr == ' ')
		ptr++;
		
	S ("PRIVMSG %s :%ld (%s)(Total: %ld)\n", chan, j, ptr, k);

	register_player (chan, who, j);
}
		
	
void		register_player	(char *chan, char *who, long dice_total)
{
	game_players *c = NULL, *n = NULL;
	
	n = malloc (sizeof (game_players));

	if (n == NULL) 
	{
		printf ("Memory allocation failure in register_player().\n");
		return;
	}
	
	memset 	(n, 0, sizeof (game_players));
	
	c = players;

	while (c)
	{   /* Check for players already and update. */
		if (stricmp (who, c->nick) == 0)
		{
			if (c->playing == 0)
			{
				c->playing = 1;
				c->rollnum++;
				c->rolltotal = dice_total;
				return;
			}
			
			return;
		}
		
		c = c->next;
	}
	
	/* New User */
	if (n != NULL)
	{
		n->next = NULL;

		n->rollnum = 0;
		n->playing = 1;
		strncpy (n->nick, who, sizeof (n->nick));
		n->next = NULL;
		
		if (players == NULL)
			players = n;
		else
		{
			c = players;

			while (c->next != NULL)
				c = c->next;

			c->next = n;
		}
	}
} 

void		remove_player (char		*nick)
{

	game_players	*pNode = NULL, *pPrev = NULL, *sc = NULL;
	
	pNode = players;
	pPrev = NULL;
	
	while (pNode)
	{
		if (stricmp (pNode->nick, nick) == 0)
		{
			if (pPrev != NULL)
			{
				pPrev->next = pNode->next;
			}
			else
				players = pNode->next;
			
			free (pNode);
			pNode = NULL;
			break;
		}
		
		pPrev = pNode;
		pNode = pNode->next;
	}
}

				