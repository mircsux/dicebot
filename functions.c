/* Functions */

#include "includes.h"

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

int
stricmp (const char *s1, const char *s2)
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


	
	