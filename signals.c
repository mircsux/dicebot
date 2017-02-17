/* Signals */

#include "includes.h"


void		sig_alrm (int unused)
{
	alarmed = 1;
	alarm (AIL);
	
	/* Increase seconds count. */
	timer++;
	
	LastInput += AIL;
	if (LastInput >= 500)
	{
		LastInput = 0;
		printf ("\nNo response from server in 5 mins, reconnecting.\n");
		prepare_bot ();
		register_bot();
	}
	
	
	AIL8 += AIL;
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
	
	RoundTimer += AIL;
	if (RoundTimer >= 60)
	{
		RoundTimer = 0;
		S ("PRIVMSG %s :Round_Timer = 0\n", config->BOTCHAN);
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

void	sig_int		(int unused)
{
	S ("PRIVMSG %s :Interrupted from the console. Show uptime here\n", config->BOTCHAN);
	exit (0);
}