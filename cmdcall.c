#include "shell.h"

/**
 * checkpath - checks the path
 * @av: arguments
 * Return: 1
 */
int checkpath(char *av[])
{
	char *path, *pathptr, *pathvar, *ptr, *pathenv = "PATH", *linect;
	int pathlen, cmdlen;

#ifdef DEBUGMODE
	printf("In checkpath\n");
#endif
	for (ptr = av[0], cmdlen = 0; *ptr != 0; ptr++)
		cmdlen++;
	pathvar = _getenv(pathenv);
	if (pathvar != pathenv)
	{
		pathenv = pathvar;
		while (*pathvar != 0)
		{
#ifdef DEBUGMODE
			printf("in loop pathvar:%s:*pathvar:%c\n", pathvar, *pathvar);
#endif
			for (pathlen = 0, ptr = pathvar; *ptr != 0 && *ptr != ':'; ptr++)
				pathlen++;
			path = malloc(sizeof(char) * (cmdlen + pathlen + 2));
			if (path == NULL)
			{
				free(pathenv);
				return (-1);
			}
			pathptr = path;
			while (*pathvar != ':' && *pathvar != 0)
				*pathptr++ = *pathvar++;
			if (pathptr != path)
				*pathptr++ = '/';
			ptr = av[0];
			while (*ptr != 0)
				*pathptr++ = *ptr++;
			*pathptr = 0;
			if (!access(path, F_OK))
			{
#ifdef DEBUGMODE
				printf("Found path:%s\n", path);
#endif
				pathlen = cmdcall(av, path);
				free(path);
				free(pathenv);
				return (pathlen);
			}
			free(path);
			if (*pathvar == ':')
				pathvar++;
		}
	}
	linect = itos(linecount(0));
	path = getsvar("0");
	fprintstrs(2, path, ": ", linect, ": ", av[0], ": not found\n", NULL);
	free(path);
	free(linect);
	if (pathenv != pathvar)
		free(pathenv);
	return (127);
}
/**
 * cmdcall - calls commands
 * @av: arguments
 * @cmd: command
 * Return: retval
 */
int cmdcall(char *av[], char *cmd)
{
	pid_t command;
	int status;
	char *linect, *dolz;

#ifdef DEBUGMODE
	printf("In cmdcall av[0]:%s\n", av[0]);
#endif
	environ = getallenv();
	if (environ == NULL)
		return (-1);
#ifdef DEBUGMODE
	printf("Forking\n");
#endif
	command = fork();
#ifdef DEBUGMODE
	printf("command:%d\n", command);
	fflush(stdout);
#endif
	if (command == 0)
	{
#ifdef DEBUGMODE
		printf("Executing %s\n", av[0]);
#endif
		if (execve(cmd, av, *(getenviron())) == -1)
		{
			if (!access(cmd, F_OK))
			{
				printerr(NULL);
				exit(126);
			}
			else
			{
				linect = itos(linecount(0));
				dolz = getsvar("0");
				fprintstrs(2, dolz, ": ", linect, ": ", cmd, ": not found\n", NULL);
				free(dolz);
				free(linect);
				exit(127);
			}
			exit(1);
		}
#ifdef DEBUGMODE
		printf("Command done\n");
#endif
	}
	else
	{
		wait(&status);
	}
#ifdef DEBUGMODE
	printf("Status %d\n", status);
#endif
	free(environ);
	return (status);
