#include "shell.h"
/**
 * getallenv - get all environment
 * Return: environment
 *
 */
char **getallenv()
{
	char **environ = *(getenviron());
	char **envcopy;
	size_t len = 0;

	envcopy = environ;
	while (envcopy[len] != NULL)
		len++;
#ifdef DEBUGMODE
	printf("Got length of env lines %d\nNow copying\n", len);
#endif
	envcopy = malloc(sizeof(char **) * (len + 1));
	if (envcopy == NULL)
		return (NULL);
	while (len > 0)
	{
		envcopy[len] = environ[len];
		len--;
	}
	envcopy[len] = environ[len];
	return (envcopy);
}
/**
 * setallenv - set whole environment for new value
 * @envin: environment
 * @newval: new value to be added
 * Return: 0 if success, -1 if failure
 */
/* add should be null for first init to not free passed array */
int setallenv(char **envin, char *newval)
{
	char ***environ = getenviron();
	size_t len = 0;

#ifdef DEBUGMODE
	printf("In setallenv, newval:%s\n", newval);
#endif
	while (envin[len] != NULL)
		len++;
	if (newval != NULL)
		len++;
	*environ = malloc(sizeof(char **) * (len + 1));
	if (*environ == NULL)
		return (-1);
	for (len = 0; envin[len] != NULL; len++)
		if (newval == NULL)
		{
			(*environ)[len] = _strdup(envin[len]);
		}
		else
			(*environ)[len] = envin[len];
	if (newval != NULL)
	{
#ifdef DEBUGMODE
		printf("Adding newval:%s\n", newval);
#endif
		(*environ)[len] = newval;
		len++;
	}
	(*environ)[len] = NULL;
#ifdef DEBUGMODE
	printf("At end. Free old environ if adding a string\n");
#endif
	if (newval != NULL)
		free(envin);
	return (0);
}
/**
 * _getenv - get local environment
 * @name: environment variable
 * Return: string of local environment
 */
char *_getenv(char *name)
{
	char **environ = *(getenviron());
	int i, j;
	char *s;

#ifdef DEBUGMODE
	printf("In getenv, name:%s\n", name);
#endif
	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
#ifdef DEBUGSVARS
		printf("Checking against:%s\n", environ[i]);
#endif
		while (s[j] == name[j])
		{
			j++;
			if (name[j] == 0 && s[j] == '=')
				return (_strdup(s + j + 1));
		}
		i++;
	}
	return (name);
}
