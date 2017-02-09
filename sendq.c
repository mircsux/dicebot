/* SendQ stuff */

#include "includes.h"

/**
 * Delete one or more elements from the sendq
 * 1 = delete all pri/not's
 * 0 = delete first in queue
 * 6/23/00 Dan
 * - Updated to use head and tail pointer queue
 * - All variables now initialized when declared
 * - Optimized the main while loop a bit, reduced amount of code
 */
void
del_sendq (long toggle)
{
	struct sendq *pNode = sendqhead, *pPrev = 0;

	if (NULL == sendqhead)
	{
		return;
	}

	if (toggle == 0)
	{
		/* Just delete the head */
		pNode = sendqhead;
		sendqhead = sendqhead->next;

		free (pNode);
	}
	else
	{
		/* Iterate through the queue and delete each element which is
		 * a PRIVMSG or NOTICE
		 */
		for (; pNode != NULL; pPrev = pNode, pNode = pNode->next)
		{
			if (0 == strncmp (pNode->data, "PRI", 3) || 0 == strncmp (pNode->data, "NOT", 3))
			{
				/* Found one, let's delete it */
				if (pPrev != NULL)
				{
					pPrev->next = pNode->next;
				}
				else
				{
					sendqhead = pNode->next;
				}
				free (pNode);
				pNode = NULL;
				break;
			}
		}						/* for */
	}							/* else */

	/* Update the tail pointer if needed */
	if (NULL == sendqhead)
	{
		sendqtail = NULL;
	}
}

int
get_sendq_count (long toggle)
{
	struct sendq *c;
	long i = 0, x = 0;

	c = sendqhead;
	while (c != NULL)
	{
		i++;
		if (c->data[0] == 'P' && c->data[1] == 'R' && c->data[2] == 'I')
			x++;
		else if (c->data[0] == 'N' && c->data[1] == 'O' && c->data[2] == 'T')
			x++;
		c = c->next;
	}
	if (toggle == 1)
		clear_sendq (i, 1);
	if (toggle == 2)
		return i;

	if (i < OUTPUT1_COUNT)
		SEND_DELAY = OUTPUT1_DELAY;
	else if (i < OUTPUT2_COUNT)
		SEND_DELAY = OUTPUT2_DELAY;
	else
		SEND_DELAY = OUTPUT3_DELAY;
	if (x > OUTPUT_PURGE_COUNT)
		clear_sendq (x, 0);
	return i;
}

void
clear_sendq (long count, long toggle)
{
	long i = 0;

	i = count;
	while (i > 1)
	{
		i--;
		del_sendq (1);
	}
	send_tog = 1;
/*	if (toggle != 1)
		L090 (CHAN, count); */
}
