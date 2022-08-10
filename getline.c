#include "shell.h"
/**
 * _getline - gets a line from fd or std input
 * @lineptr: buffer to fill line with
 * @fd: file descriptor
 * Return: num of characters
 */
int _getline(char **lineptr, int fd)
{
	int size = 1025;
	int old_size = 0;
	int r = 1;
	int sum = 0;
	static char buffer[1025];
	static int begin;
	static int end;
	int c = 0;
	int d;

	if (fd == -2)
	{
		begin = 0;
		end = 0;
	}

	if (lineptr == NULL)
	{
		return (0);
	}
	if (*lineptr == NULL)
	{
		*lineptr = malloc(sizeof(char) * size + 1);
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		if (begin == end)
		{
			while (sum < 1024 && r != 0)
			{
				r = read(fd, buffer + sum, 1024 - sum);
				begin = 0;
				sum += r;
				end = sum;
				/*printf("r : %d\n", r);*/
				for (d = 0; r != 0 && d < end; d++)
					if (buffer[d] == '\n')
						r = 0;
			}
			if (sum == 0)
			{
				buffer[0] = 0;
				return (sum);
			}
