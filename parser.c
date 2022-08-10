#include "shell.h"
/**
 * parsesetsvar - parse set shell vars, returns new buf after var setting
 * @buf: buffer
 * Return: string
 */
char *parsesetsvar(char *buf)
{
	int haseq;
	char *ptr, *name, *val, *bufstart = buf, *newbuf;

	do {
		haseq = 0;
		for (ptr = buf; *ptr; ptr++)
		{
#ifdef DEBUGSVARS
			printf("in loop ptr:%s\n", ptr);
#endif
			if (*ptr == '=')
			{
				name = strtok(buf, " ");
				buf = strtok(NULL, "");
				ptr = buf;
				haseq = 1;
				name = strtok(name, "=");
				val = strtok(NULL, "");
#ifdef DEBUGSVARS
				printf("In parsesetvar: setting var %s to %s\n", name, val);
#endif
				setsvar(name, val);
				if (buf == NULL)
				{
					free(bufstart);
					return (NULL);
				}
				continue;
			}
			if (*ptr == ' ' || *ptr == 0)
			{
				buf = _strdup(buf);
				/* do malloc fail test */
				free(bufstart);
				return (buf);
			}
			if (ptr == NULL)
			{
#ifdef DEBUGSVARS
				printf("No other args found, returning\n");
#endif
				free(bufstart);
				return (NULL);
			}
		}
	} while (haseq && *ptr != 0);
	newbuf = malloc(sizeof(char) * (_strlen(buf) + 1));
	if (newbuf == NULL)
		return (NULL);
	newbuf = _strcpy(newbuf, buf);
	free(bufstart);
	return (newbuf);
}

/**
 * subsvars - substitutes in svars for $names
 * @buf: buffer string that was input
 * Return: processed buffer string
 */
char *subsvars(char **buf)
{
	char *varptr = *buf, *ptr, *name, *val, *valptr, *dest, *dolptr;
	size_t buflen = _strlen(*buf);
	size_t varvlen, varnlen, i;
	int inquotes = 0;

#ifdef DEBUGSVARS
	printf("In subsvars\n");
#endif
	while (*varptr != 0)
	{
#ifdef DEBUGSVARS
		printf("Top of svar loop buf:%s::varptr:%s\n", *buf, varptr);
#endif
		while (*varptr != '$' && *varptr != 0)
		{
/*			printf("inquotes:%d:varptr:%s\n", inquotes, varptr);*/
			if (*varptr == '\\')
			{
				varptr++;
				if (*varptr != 0)
					varptr++;
				continue;
			}
			if (inquotes == 2 && *varptr == '"')
				inquotes = 0;
			if (inquotes == 0 && *varptr == '"')
				inquotes = 2;
			if (*varptr == '\'' && inquotes != 2)
			{
				varptr++;
				while (*varptr != '\'' && *varptr != 0)
					varptr++;
			}
			varptr++;
			if (*varptr == '$' &&
			    (varptr[1] == ' ' || varptr[1] == 0 || varptr[1] == '\n'))
				varptr++;
		}
#ifdef DEBUGSVARS
		printf("At $:%s\n", varptr);
#endif
		dolptr = varptr;
		if (*varptr == 0)
			return (*buf);
		varptr++;
		for (ptr = varptr, varnlen = 0; *ptr != 0 && *ptr != ' '
			     && *ptr != '\n' && *ptr != '\\'; ptr++)
			varnlen++;
#ifdef DEBUGSVARS
		printf("varnlen:%d varptr:%s\n", varnlen, varptr);
#endif
		name = malloc(sizeof(char) * (varnlen + 1));
		if (name == NULL)
			return (NULL);
		for (i = 0; i < varnlen; i++, varptr++)
			name[i] = *varptr;
		name[i] = 0;
#ifdef DEBUGSVARS
		printf("Name got:%s\n::varptr:%s\n", name, varptr);
#endif
		val = _getenv(name);
		if (val == name)
		{
#ifdef DEBUGSVARS
			printf("%s not an env var, checking svars\n", name);
#endif
			val = getsvar(name);
			if (val == name)
				val = _strdup("");
		}
		free(name);
#ifdef DEBUGSVARS
		printf("val got:%s\n", val);
#endif
		varvlen = _strlen(val);
/*
 *need new buffer for substituted var string
 */
		buflen = buflen - varnlen + varvlen + 1;
#ifdef DEBUGSVARS
		printf("malloc size:%d\n", buflen);
#endif
		name = malloc(sizeof(char) * (buflen));
		for (ptr = *buf, dest = name, valptr = val; *ptr != 0; ptr++, dest++)
		{
/*
 * printf("copy to new buf %s::%s\n", ptr, name);
 */
			if (val != NULL && ptr == dolptr)
			{
				while (*valptr != 0)
					*dest++ = *valptr++;
				free(val);
				val = NULL;
				varptr = dest;
				ptr += varnlen + 1;
				if (*ptr == 0)
					break;
			}
			*dest = *ptr;
		}
		*dest = *ptr;
#ifdef DEBUGSVARS
		printf("Resulting buf:%s::varptr:%s\n", name, varptr);
#endif
		free(*buf);
		*buf = name;
	}
	return (*buf);
}
