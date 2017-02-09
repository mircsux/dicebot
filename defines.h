/* Defines */

#define	CONFIG_DIR				"dat"
#define	CONFIG_FILE				"config.ini"

#define	YES						1
#define	NO						0
#define	AIL						1
#define	USEC					0
#define	WSEC					10
#define	RECHECK					45
#define ERR_SOCK_OPT			-1
#define ERR_TIMED_OUT           -1
#define ERR_CANT_MALLOC         -1
#define ERR_OPEN_SOCKET         -2
#define ERR_CONN_REFUSED        -2
#define ERR_NOT_ADDR            -3
#define ERR_WRITE_SOCKET        -3
#define ERR_NO_REACH            -4
#define ERR_CANT_CONNECT        -5
#define ERR_READ_SOCKET         -5
#define ERR_SERVER_BUSY         -6
#define ERR_NO_DOCUMENTS        -6
#define ERR_NO_DATA             -7
#define SUCCESS                 0

#ifndef EXIT_SUCCESS
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
#endif

#define	STRING_LONG		4096
#define STRING_SHORT	512

/* ==== OUTPUTS - TIMERS ==== */
/*
 * LASTCOMM_TIME is the length of time (in seconds)
 * that your bot will not reply to a topic already
 * asked. Thus if someone asked your bot about "mirc"
 * that question could not be asked again in the
 * same format for N seconds (or till the question
 * is out of buffer). This prevents the bot from
 * falling prey to users who like to repeat.
 * (default = 5)
 */
#define LASTCOMM_TIME 5

/*
 * BELOW is the output timers. Darkbot does not
 * output text without first putting it into a
 * que list. If the bot has several lines of text
 * waiting to be sent, it starts to delay longer
 * and longer between output, so it can't flood
 * itself off of IRC. Explanation:
 *
 * If text in que is < OUTPUT1_COUNT, output it.
 * If text in que is > OUTPUT1_COUNT, delay
 * OUTPUT1_DELAY seconds. If que is > OUTPUT2_COUNT,
 * delay OUTPUT2_DELAY seconds. If number of text
 * in que is higher than OUTPUT_PURGE_COUNT, then
 * just delete all unneeded output (ie; any text
 * and notices, but leaving in stuff like kicks
 * and modes) The defaults below are recommended,
 * as the bot isn't going to flood off. If you are
 * having the bot delete output messages and you'd
 * like to increase the que, update the 
 * OUTPUT_PURGE_COUNT to a larger number. Just keep
 * in mind if someone floods your bot with a lot of
 * VERSION requests, the bot will sit there outputting
 * a lot of version replies instead of deleting them,
 * causing it to act as if it's just sitting there not
 * doing anything when you ask it something in your
 * channel. (defaults = 4) = 1) = 6) = 2)
 */
#define OUTPUT1_COUNT 4
#define OUTPUT1_DELAY 1
#define OUTPUT2_COUNT 6
#define OUTPUT2_DELAY 2

/*
 * If still < OUTPUT_PURGE_COUNT and > OUTPUT2_COUNT
 * then delay OUTPUT3_DELAY secs. (default = 3)
 */
#define OUTPUT3_DELAY 3

/*
 * When all else fails... if more than OUTPUT_PURGE_COUNT
 * delete them all! No use in making the bot output slowly
 * over a long period of time... imagine if you set this to
 * 50, and had an OUTPUT3_DELAY of 3 secs.. thats 50*3 secs
 * till the bot is ready to output any new data to you!
 * (default = 7)
 */
#define OUTPUT_PURGE_COUNT 7
