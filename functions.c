/* Functions */

#include "includes.h"

char	* strlwr (char *buf)
{
        char *ptr = buf;

        for (; ptr && *ptr; ++ptr)
        {
                *ptr = tolower (*ptr);
        }
        return buf;
}

int		is_number	(char *buf)
{
	if (strspn (buf, "0123456789") == strlen (buf))
		return (1);
	return (0);
}
		
	
void	stripline (char *ptr)
{
        for (; ptr && *ptr; ++ptr)
        {
                if ('\r' == *ptr || '\n' == *ptr)
                {
                        *ptr = 0;
                        return;
                }
        }
}

int		stricmp (const char *s1, const char *s2)
{
        register int c = 0;

        while ((c = tolower (*s1)) == tolower (*s2))
        {
                if (c == 0)
                        return 0;
                s1++;
                s2++;
        }
        if (c < tolower (*s2))
                return -1;
        return 1;
}

/* Returns number of people actively playing. */

long	get_num_players (void)
{
	game_players 	*c = players;
	long			i = 0;
	
	while (c)
	{
		if (c->playing == 1)
			i++;
			
		c = c->next;
		
	}
	
	return (i);
}

char		*get_nick_from_who	(char *nick, char *who)
{
	int		i = 0;
	int		max = 0;
	
	/* Max number of chars to scan to get nickname. 
     * Sort of sanity check here, not necessarily needed. */
	if ((max = strlen (who)) < 1)
		return (NULL);
	
	if ((nick = malloc (STRING_LONG)) == NULL)
	{
		printf ("Memory allocation failure in get_nick_from_who.\n");
		return (NULL);
	}
	
	for (i = 0; i < max; i++)
	{
		if (who[i] == '!')
		{
			nick[i++] = '\0';
			return (nick);
		}
		
		nick[i] = who[i];
	}

	return (nick);
}
	
	
	
	
	
/* Return num word from object pointed to by str, 
   using sep as a delimeter. */
char	*get_word		(int num, char *str, int sep)
{
	char 	*ptr = NULL;
	int 	i = 0, j = 0;
	int		sepcount = 0;
	
	if ((ptr = malloc (STRING_LONG)) == NULL)
	{
		printf ("Out of memory in get_word\n");
		exit (EXIT_FAILURE);
		
	}
	
	memset (ptr, 0, sizeof (STRING_LONG));
	
	for (i = 0, j = 0, sepcount = 0; str[i]; i++, j++)
	{
		if (str[i] == sep)
		{
			i++; /* Trim out sep char */
			sepcount++; 

			if (sepcount == num)
			{	
				ptr[j++] = '\0';
				return (ptr);
			}
		
			j = 0;
		}
	
		ptr[j] = str[i];
	}

	ptr[j++] = '\0';
	/* If number of seperators counted is less than 
	   the one we called for, return NULL ptr. */
	if (sepcount < (num-1))
	{
		ptr = NULL;
		return (ptr);
	}
	
	return (ptr);
}

char		*my_uptime	(char *str, time_t uptime)
{
	long days = 0, hours = 0, mins = 0, secs = 0;
	
	uptime = time (NULL) - Start_Time;
	
	if ((str = malloc (STRING_LONG)) == NULL)
	{
		printf ("Memory allocation failure in my_uptime.\n");
		return (NULL);
	}
	
	days = uptime / 86400; 
	hours = uptime / 3600;
	mins = uptime / 60;
	secs = uptime % 60;
	
	if (days > 0)
		sprintf (str, "%ldday%s", days, (days == 1) ? "" : "s");
	if (hours > 0)
		sprintf (str, "%s%ldhour%s", (days > 0) ? str : "",
			hours, (hours % 24) == 1 ? "" : "s");
	if (mins > 0)
		sprintf (str, "%s%ldmin%s", (hours > 0) ? str : "",
			mins, (mins % 60) == 1 ? "" : "s");
			
	if (secs > 0)
		sprintf (str, "%s%ldsec%s", (mins > 0 ) ? str : "",
			secs, secs == 1 ? "" : "s");
			
	return (str);

}

	
	