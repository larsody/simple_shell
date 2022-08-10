#include "shell.h"
/**
 * _strcmp - compares two strings
 * @s1: char pointer
 * @s2: char pointer
 *
 * _strcmp: compares two strings at the same spot on each string
 * Return: positive, negative, or 0 if theyre the same
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}
/**
 * _strlen - counts the length of the string
 * @str: string
 * Return: length of the string
 */
size_t _strlen(char *str)
{
	size_t length = 0;

	while (*str++)
		length++;

	return (length);
}
