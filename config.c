/* Stuff involving config files */

#include "includes.h"

#define		C_UNKNOWN		0
#define		C_BOTNICK		1
#define		C_BOTUSER		2
#define		C_BOTNAME		3
#define		C_BOTSERV		4
#define		C_BOTCHAN		5
#define		C_SCOREFILE		6
struct
{
	const	char	*opt;
	const	int		c_value;
}	cfg_opt [] =
{
	{   "BOTNICK",		C_BOTNICK			},
	{   "BOTUSER",		C_BOTUSER			},
	{   "BOTNAME",		C_BOTNAME			},
	{   "BOTCHAN", 		C_BOTCHAN			},
	{   "BOTSERV",		C_BOTSERV			},
	{   "SCORE_FILE", 	C_SCOREFILE			},
	{   NULL,			0					}
};

/* Pretty self explanatory. */

int			do_config_set 		(const  int	opt, 	char *value)
{

	if (value == NULL)
		return (0);
	
	switch (opt)
	{
		case C_BOTNICK:
		{
			strncpy (config->BOTNICK, value, sizeof (config->BOTNICK));
			return (1);
		}
		
		case C_BOTUSER:
		{
			strncpy (config->BOTUSER, value, sizeof (config->BOTUSER));
			return (1);
		}
		case C_BOTNAME:
		{	strncpy (config->BOTNAME, value, sizeof (config->BOTNAME));
			return (1);
		}
		case C_BOTSERV:
		{
			do_add_servers (value);
			return (1);
		}
		case C_SCOREFILE:
		{
			strncpy (config->SCORE_FILE, value, sizeof (config->SCORE_FILE));
			return (1);
		}
		case C_BOTCHAN:
		{
			strncpy (config->BOTCHAN, value, sizeof (config->BOTCHAN));
			return (1);
		}

		default:
		{
			printf ("Invalid config setting\n");
			return (0);
		}
	}
	return (0);
}

void		load_config		(char *file)
{
	
	FILE		*fp = NULL;
	int			i = 0;
	char		str 	[STRING_LONG] = { "\0" };
	char		*opt = NULL, *value = NULL;
	
	config = malloc (sizeof (Config));
	
	memset (config, 0, sizeof (Config));
	
	if (config == NULL)
	{
		printf ("Out of memory in load_config()\n");
		exit (EXIT_FAILURE);
	}
	/* Exit out if we can't open the file, no use in 
	   lollygagging around. */
	if ((fp = fopen (file, "r")) == NULL)
	{
		printf ("Failed to load config file (%s)", file);
		return;
	}
	
	/* Run a check here at some point to assure our
	   config file is formatted properly */
	   
	while (fgets (str, STRING_LONG, fp))
	{
		stripline (str);
		/* NULL lines or lines that don't do us any good?
		   Just ignore them. */
		if ((opt = strtok (str, "=")) == NULL)
			return;
		
		value = strtok (NULL, "");
		if (value == NULL)
			return;
		
		for (i = 0; cfg_opt[i].opt; i++)
		{
			int	retval = 0;
			
			if (stricmp (opt, cfg_opt[i].opt) == 0)
			{
				retval = do_config_set (cfg_opt[i].c_value, value);
				/* Do stuff with retval here eventually */
			}	
		}
	}   /*End WHILE */
	
}

/* Print things to a "filename" */

void	my_log	(char	*filename, char *format,...)
{
	va_list		arglist;
	FILE		*fp = NULL;
	
	if ((fp = fopen (filename, "a")) == NULL)
		return;
		
	va_start 	(arglist, format);
	vfprintf 	(fp, format, arglist);
	va_end 		(arglist);
	fclose		(fp);
}