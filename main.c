/*  Main() */

#include "includes.h"


int			main			(int argc, char **argv)
{
	int 	i = 0;
	fd_set	fdvar;
	struct	timeval		timeout;
	struct	ISL			*isl = islhead;
	
#ifdef		SA_NOCLDSTOP
	struct	sigaction	newact;
#endif
	

/* This is the best way to deternmine if sigaction() can be used.
 * sigaction() is more portable than signal(), so use it if we can. */

 #ifdef 	SA_NOCLDSTOP
        newact.sa_handler = sig_alrm;
        sigemptyset (&newact.sa_mask);
        newact.sa_flags = 0;
        sigaction (SIGALRM, &newact, NULL);
        newact.sa_handler = sig_segv;
        sigemptyset (&newact.sa_mask);
        newact.sa_flags = 0;
        sigaction (SIGSEGV, &newact, NULL);
        newact.sa_handler = sig_hup;
        sigemptyset (&newact.sa_mask);
        newact.sa_flags = 0;
        sigaction (SIGHUP, &newact, NULL);
		newact.sa_handler = sig_int;
		sigemptyset(&newact.sa_mask);
		newact.sa_flags = 0;
		sigaction (SIGINT, &newact, NULL);
#else
        signal (SIGALRM, sig_alrm);
        signal (SIGSEGV, sig_segv);
        signal (SIGHUP, sig_hup);
		signal (SIGINT, sig_int);
#endif

	printf ("[*** Ron's IRC Bot %s ***]\r\n", PACKAGE_VERSION);
	
	/* Load config file. */
	printf ("Loading dat/setup.ini\n");
	load_config ("dat/setup.ini");
	
	Start_Time = time (NULL);
	
	alarm (AIL);
	prepare_bot ();
	register_bot ();

	printf_servers();
	
	while (1)
	{
		timeout.tv_sec = WSEC;
		timeout.tv_usec = USEC;
		
		FD_ZERO (&fdvar);
	    FD_SET (sockfd, &fdvar);
		
		switch (select (NFDBITS, &fdvar, NULL, NULL, &timeout))
		{
			case 0:
			   break;
			case -1:
				if (!alarmed)
				{
					sleep (RECHECK);
				}   
				else 
				{ 
					alarmed = 0; 
				}
				break;
				
			default:
			   parse_server_message (sockfd, &fdvar);
			   break;
	    }
	}
	
	/* Close socket */
	close (sockfd);
	free (config);
	free (islhead);
	free (iulhead);
	free (sendqhead);
	free (sendqtail);
	return (0);
	
}

