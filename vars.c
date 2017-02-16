/* Vars */
#include "includes.h"


long	CONNECT_WAIT_TIMEOUT	= 10;
long	AIL666 					= 0;
long	AIL8					= 0;
long	timer					= 0;
long	LastInput				= 0;
long	RoundTimer				= 0;
time_t	Start_Time				= 0;

char	HOSTNAME[STRING_SHORT]	= "bifrost.ca.us.dal.net";
char	VHOST	[STRING_SHORT]	= "0";
char	MYNICK	[STRING_SHORT] 	= "mybot";

char	myline		[STRING_SHORT]  = { "\0" };
int		alarmed					= 0;
int		sockfd					= 0;
int		PORT					= 6667;
int		send_tog				= 0;
int		SEND_DELAY 				= 1;
int		BurstingWho				= 0;  /* Are we receiving a /who burst? */

struct 	sendq 		*sendqhead = NULL, *sendqtail = NULL;
struct	IUL		*iulhead = NULL;
struct	ISL		*islhead = NULL;

Config  	*config = NULL;
game_players	*players = NULL;