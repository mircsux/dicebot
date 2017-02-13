/* Signals */

#include "includes.h"


void		sig_alrm (int unused)
{
	alarmed = 1;
	alarm (AIL);
	AIL8 += AIL;
	/* Increase seconds count. */
	timer++;
	
	if (AIL8 >= SEND_DELAY)
	{
		AIL8 = 0;
		Send ();
	}
	AIL666 += AIL;
	if (AIL666 >= 60)
	{
		AIL666 = 0;
		S ("PING :%s\n", HOSTNAME);
	}
	
}

void		sig_segv (int unused)
{
	long	p = 0;
	
	/* Grab our pid number */
	p = getpid ();
	
	S ("QUIT :Caught signal SIG_SEGV (Segmentation Fault). We are bailing.\n");
	printf ("... SIG_SEGV\n");
	
	if (fork () > 0)
	{
		kill (p, 3); /* SIGQUIT - terminate process and dump core. */
		kill (p, 9); /* SIGKILL */
	}
	exit (0);
}

void	sig_hup 	(int unused)
{
	printf (".: SIGHUP - Restarting the program.\n");
	exit (0);
}