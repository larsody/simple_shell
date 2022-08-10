#include "shell.h"
#include "history.h"

/**
 * gethistory - gets the history list
 * Return: 0 uposon success
 */

HistList **gethistory()
{
	static HistList *hlist;

	return (&hlist);
}

/**
 * sethist - set hist and value
 * @cmd: command
 * Return: 0 upon success
 */

int sethist(char *cmd)
{
	HistList **hlistroot = gethistory();
	HistList *hlist = *hlistroot;
	HistList *ptr = hlist, *new;

	if (hlist == NULL)
	{
		new = malloc(sizeof(HistList));
		if (new == NULL)
			return (-1);

		new->cmd = _strdup(cmd);
		new->next = NULL;
		*hlistroot = new;
		return (0);
	}
	while (ptr->next != NULL)
		ptr = ptr->next;

	new = malloc(sizeof(HistList));
	if (new == NULL)
		return (-1);
	new->cmd = _strdup(cmd);
	new->next = NULL;
	ptr->next = new;
	return (0);
}

