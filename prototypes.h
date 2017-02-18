/* Function Prototypes */

int		create_connection 		(char *, char *, long);
int		set_config_opt			(int, char *);
int		get_random_number		(int);
int		main					(int, char **);
int		recv_data				(int, char *);
int		Send 					(void);
int		send_data				(int, char *);
int		writeln					(const char *);
int		readln 					(int);
int		try_server_command		(int, char *, char *, char *);
int		try_user_command		(char *, char *, char *, char *);
char	*strlwr 				(char *);
int		register_bot			(void);
int		get_sendq_count 		(long);
int		Snow 					(const char *, ...);
int		stricmp 				(const char *, const char *);
char	*get_word				(int, char *, int);
void    clear_sendq 			(long, long);
void	my_log					(char	*, char *,...);
void	S 						(const char *, ...);
void	do_add_servers			(char *);
void	do_info					(char *, char *, char *, char *);
void	add_iul_user			(char *, char *, char *, long);
void	add_isl_server 			(char *, long, char *);
void	del_iul_user 			(const char *, char *);
void	del_sendq 				(long);
void	do_chanserv				(char *);
void	load_config				(char *);

void	do_roll					(char *, char *, char *, char *);
void	do_play					(char *, char *, char *, char *);
void	do_keep					(char *, char *, char *, char *);
void 	roll_dice				(char *, char *who, long, long);
void	reinit_players 			(void);
void	register_player			(char *, char *, long);
void	remove_player 			(char *);
int		is_playing				(char *);
int		add_player_dice			(char *, long, long, long);
long	get_num_players 		(void);
char	*get_nick_from_who		(char *, char *);

void	parse					(int, char *);
void	parse_001				(int, char *, char *, char *);
void	parse_error				(int, char *, char *, char *);
void	parse_end_of_who		(int, char *, char *, char *);
void	parse_join				(int, char *, char *, char *);
void	parse_kick				(int, char *, char *, char *);
void	parse_mode				(int, char *, char *, char *);
void	parse_nick				(int, char *, char *, char *);
void	parse_part				(int, char *, char *, char *);
void	parse_ping				(int, char *, char *, char *);
void	parse_privmsg			(int, char *, char *, char *);
void	parse_who				(int, char *, char *, char *);
void	parse_server_message	(int, fd_set *);
void	prepare_bot				(void);
void	printf_servers			(void);
void	show_players			(char *);
void	sig_alrm				(int);
void	sig_hup					(int);
void	sig_segv				(int);
void	sig_int					(int);
void	stripline 				(char *);

extern	long	CONNECT_WAIT_TIMEOUT;
extern	long	AIL666;
extern	long	AIL8;
extern	long	LastInput;
extern	long	RoundTimer;
extern	time_t	Start_Time;

extern	char	HOSTNAME		[STRING_SHORT];
extern	char	VHOST			[STRING_SHORT];
extern	char	MYNICK			[STRING_SHORT];
extern	char	myline			[STRING_SHORT];
extern	char	*my_uptime		(char	*, time_t);

extern	int		alarmed;
extern	int		sockfd;
extern	int		PORT;
extern  int		send_tog;
extern	int		SEND_DELAY;
extern 	int		BurstingWho;
extern	long	timer;		/* Internal timer counter */

extern	struct sendq
{
        char data[STRING_SHORT];
        struct sendq *next;
}		*sendqhead, *sendqtail;

/* Internal Server List */
struct 		ISL	
{
		char		server 	[STRING_SHORT];
		char		pass	[STRING_SHORT];
		char		nick 	[STRING_SHORT];
		char		userid	[STRING_SHORT];
		long		port;
		long		contime;
		int			sockfd;
		int 		alarmed;
		struct		timeval	timeout;
		int			Connected;
		char		LINE	[STRING_LONG];
		struct		ISL		*next;
		
}  *islhead;

/* Internal User List */
struct		IUL
{
	char	chan		[STRING_SHORT]; /* User's channel */
	char	nick		[STRING_SHORT]; /* User's nickname */
	char	uh			[STRING_SHORT]; /* User's hostmask */
	int		level;						/* Level user authed, if authed */
	long	idle;
	struct	IUL *next;
}   *iulhead;


typedef		struct	player_struct
{
	char	nick	[STRING_LONG];
	long	score;
	long	all_time_score;
	long 	rollnum;
	long	rolltotal;
	long	playing;
	long	last_roll_time;
	int		my_turn;
	int		keep_since_roll;
	
	int		dice1, dice2, dice3, dice4, dice5, dice6;
	int		kept1, kept2, kept3, kept4, kept5, kept6;
	
	struct 	player_struct *next;
}  	game_players;

typedef	struct	config_struct	{
	char	BOTNICK 		[STRING_SHORT];		/* My nickname */
	char	BOTCHAN			[STRING_LONG];		/* My channels */
	char	BOTUSER			[STRING_SHORT];		/* My username */
	char	BOTNAME			[STRING_SHORT];		/* My IRCNAME */
	char	BOTSERV			[STRING_LONG];		/* My servers/ports/pass */
	char	SCORE_FILE		[STRING_LONG];		/* Location of saved scores. */
	long	REJOIN_ON_KICK;					/* Rejoin on kick? */
} Config;


extern	Config *config;
extern	game_players *players;
