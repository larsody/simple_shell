#include "shell.h"
/**
 * inputvalidator - validates input buffer
 * complete is bit flag type to complete.
 * 0 none, 1 single quote, 2 double quote, 4 logic,
 * fd is fd we used to get input the first time
 * @buf: buffer
 *
 * @fd: file descriptor
 *
 * Return: return value of command, 2 for syntax errors,
 * or negative numbers for syscall errors
 */
int inputvalidator(char **buf, int fd)
{
	char *newbuf, *bufgl, *bufptr = *buf;
	ssize_t lenr;
	size_t lenbuf;
	int start = 1;
	int complete = 0;

	linecount(1);
	if (*bufptr == 0)
		return (0);
	while (*bufptr)
	{
#ifdef DEBUGVALID
		printf("In valid loop complete:%d:bufptr:%s", complete, bufptr);
#endif
		while ((*bufptr == ' ' || *bufptr == '\n') && !(complete & 3))
			bufptr++;
		if (*bufptr == 0)
			break;
		if (start)
		{
			if (*bufptr == ';' && *(bufptr + 1) == ';')
			{
				free(*buf);
				printerr(": Syntax error \";;\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			if (*bufptr == ';')
			{
				free(*buf);
				printerr(": Syntax error \";\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			if (*bufptr == '&' && *(bufptr + 1) == '&')
			{
				free(*buf);
				printerr(": Syntax error \"&&\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			if (*bufptr == '&')
			{
				free(*buf);
				printerr(": Syntax error \"&\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			if (*bufptr == '|' && *(bufptr + 1) == '|')
			{
				free(*buf);
				printerr(": syntax error \"||\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			if (*bufptr == '|')
			{
				free(*buf);
				printerr(": syntax error \"|\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			start = 0;
		}
		if (bufptr[0] == '\n' && bufptr[1] == 0)
			break;
		if (*bufptr == '#' &&
		    !(complete & 3) &&
		    (bufptr == *buf || *(bufptr - 1) == ' '))
		{
			*bufptr = 0;
			break;
		}
		complete &= ~4;
#ifdef DEBUGVALID
		printf("!(complete&3):%d\n", !(complete & 3));
#endif
		if (*bufptr == '"' && !(complete & 3))
		{
			complete |= 2;
			bufptr++;
			continue;
		}
		if (*bufptr == '"' && complete & 2)
			complete &= ~2;
		if (*bufptr == '\'' && !(complete & 3))
		{
			complete |= 1;
			bufptr++;
			continue;
		}
		if (*bufptr == '\'' && complete & 1)
			complete &= ~1;
		if (bufptr[0] == '&' && !(complete & 3))
		{
			if (bufptr[1] == '&')
			{
				complete |= 4;
				start = 1;
				bufptr++;
			}
			else if (bufptr[1] == '|')
			{
				free(*buf);
				printerr(": syntax error \"|\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			else if (bufptr[1] == ';')
			{
				free(*buf);
				printerr(": syntax error \";\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
		}
		if ((bufptr[0] == '|') && !(complete & 3))
		{
			if (bufptr[1] == '|')
			{
				complete |= 4;
				start = 1;
				bufptr++;
			}
