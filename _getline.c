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
			buffer[sum] = 0;
			sum = 0;
		}
		for (; buffer[begin]; begin++)
		{
			if (begin == 1024)
			{
				/*free(buffer);*/
				/*(*lineptr)[c] = EOF;*/
				/*return (c);*/
				break;
			}
			/*printf("beginning for\n");//debug check*/
			if (buffer[begin] == '\n')
			{
				(*lineptr)[c] = '\n';
				begin++;
				c++;
				(*lineptr)[c] = '\0';
				return (c);
			}
			else
			{
				(*lineptr)[c] = buffer[begin];
			}
			c++;
		}
		if (c + begin >= 1024)
		{
			old_size = size;
			size = size + 1024;
			*lineptr = _realloc(*lineptr, old_size, size);
			if (*lineptr == NULL)
			{
				return (-1);
			}
		}
		else
		{
			(*lineptr)[old_size + begin] = 0;
			return (c);
		}
		/*printf("j: %d, i:%d, r:%d\n", j, i ,r);*/
	}
}
	}
		i++;
	}
	return (name);
}
/**
 * _setenv - set environment for new value
 * @name: name of variable
 * @val: value of variable
 * Return: 0 or setallenv if success, -1 if fail
 */
int _setenv(char *name, char *val)
{
	char ***environroot = getenviron();
	char **environ = *environroot;
	int i, j, namel, vall;
	char *s, *ptr;

#ifdef DEBUGMODE
	printf("In setenv, name:%s:val:%s\n", name, val);
#endif
	if (name == NULL || val == NULL)
		return (0);
	namel = _strlen(name);
	vall = _strlen(val);
	ptr = malloc(sizeof(char) * (namel + vall + 2));
	if (ptr == NULL)
		return (-1);
	s = ptr;
	_strcpy(s, name);
	s += namel;
	_strcpy(s++, "=");
	_strcpy(s, val);
	s += vall;
	*s = 0;
#ifdef DEBUGMODE
	printf("Ptr mallocd:%s\n", ptr);
#endif
	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
		while (s[j] == name[j])
		{
			j++;
			if (name[j] == 0 && s[j] == '=')
			{
				free(environ[i]);
				environ[i] = ptr;
				return (0);
			}
		}
		i++;
	}
	return (setallenv(*environroot, ptr));
}
/**
 * _unsetenv - unset environment
 * @name: name of variable to unset
 * Return: 0 if sucess
 *
 * testing functionality  copy environ, if hits skip over, realloc
 */
int _unsetenv(char *name)
{
	char **environ = *getenviron();
	int i, j;
	int check = 0;
	char *s;
	char **env;

#ifdef DEBUGMODE
	printf("In unsetenv, name:%s\n", name);
#endif
	if (name == NULL)
		return (0);

	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
		while (s[j] == name[j])
		{
			j++;
			if (s[j] == '=' && name[j] == '\0')
			{
				check = 1;
				break;
			}
		}
		if (check == 1)
			break;
		i++;
	}
	free(environ[i]);
	while (environ[i] != NULL)
	{
		environ[i] = environ[i + 1];
		i++;
	}
	environ[i] = NULL;
	env = environ;
	setallenv(env, NULL);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (0);
}
