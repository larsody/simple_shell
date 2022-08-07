#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
* _strlen - Returns the length of a string.
* @s: A pointer to the characters string.
*
* Return: The length of the character string.
*/
int _strlen(const char *s)
{
int length = 0;
if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
return (length);
}

/**
* _strcpy - Copies the string pointed to by src, including the
*           terminating null byte, to the buffer pointed by des.
* @dest: Pointer to the destination of copied string.
* @src: Pointer to the src of the source string.
*
* Return: Pointer to dest.
*/
char *_strcpy(char *dest, const char *src)
{
size_t i;
for (i = 0; src[i] != '\0'; i++)
dest[i] = src[i];
dest[i] = '\0';
return (dest);
}
