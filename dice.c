/* Dice game */

#include "includes.h"

int		is_playing 		(char	*who)
{
	/* Check if player is playing. Return 1 if so, 0 if not */
	game_players *c = players;

	while (c != NULL)
	{
		if (c->playing == YES)
			return (YES);
			
		c = c->next;
	}
	
	/* No match. */
	return (NO);
}

void	update_keep_since_roll 	(char	*who, int yesno)
{
	/* Update keep_since_roll to be YES or NO on specified player */
	game_players *c = players;
	
	while (c)
	{
		if (stricmp (c->nick, who) == 0)
		{
			c->keep_since_roll = yesno;
			return;
		}
		c = c->next;
		
	}
}

int		is_keep_since_roll	(char	*who)
{	
	/* Check to see if this player is following the	roll, then keep
	   scheme. Return YES if so, NO if not. */
	   
	game_players *c = players;

	while (c)
	{
		if (stricmp (c->nick, who) == 0)
		{
			/* Make sure they're playing */
			if (c->keep_since_roll == YES)
				return (YES);
			else
				return (NO);
		}
		
		c = c->next;
	}
	
	/* Return -1 for NO MATCH */
	return (-1);
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

long	count_dice		(game_players *c, long num, long kept)
{
	int				i = 0;
	int				dice = 0;
	if (kept == YES)
	{
		for (i = 0; c->kept[i] != 0; i++)
			dice++;
		return (dice);
	}
	
	for (i = 0; c->dice[i] != 0; i++)
		dice++;
		
	return (dice);
}
		

int		add_player_dice	(char *who, long num, long kept)
{
	/* Add dice to array, return number of dice in array.
	   If num supplied is 0, return number of dice in array */
  	char 			*ptr = NULL;
	game_players 	*c = players;
	
	/* Sanity check */
	if (num > 6)
		return;
	
	
	while (c)
	{
		if (stricmp (c->nick, who) == 0)
		{
			/* If num == 0, return number of dice. */
		}
		
		c = c->next;
	}
}

void 	roll_dice (char *chan, char *who, long count, long num)
{
	/* count is number of dice, number of sides on dice */
	long 			i = 0, j = 0, k = 0;
	long			total = 0;
	char			*ptr = NULL;
	char			DATA [STRING_LONG] = { "\0" };	
	game_players 	*c = players;

	/* Dice syntax = roll 1d100 */

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
		
		/* add_player_dice (who, count, i, NO); */
		
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
			c->keep_since_roll = NO;
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
		int	*s = n->dice;
		
		n->next = NULL;

		n->rollnum = 0;
		n->playing = 1;
	
		memset (s, 0, 6);
		
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

				