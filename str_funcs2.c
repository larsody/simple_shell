#include "shell.h"

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
* _strchr - Locates a character in a string.
* @s: The string to be searched.
* @c: The character to be located.
*
* Return: If c is found - a pointer to the first occurence.
*         If c is not found - NULL.
*/
char *_strchr(char *s, char c)
{
int index;
for (index = 0; s[index]; index++)
{
if (s[index] == c)
return (s + index);
}
return (NULL);
}

/**
* _strspn - Gets the length of a prefix substring.
* @s: The string to be searched.
* @accept: The prefix to be measured.
*
* Return: The number of bytes in s which
*         consist only of bytes from accept.
*/
int _strspn(char *s, char *accept)
{
int bytes = 0;
int index;
while (*s)
{
for (index = 0; accept[index]; index++)
{
if (*s == accept[index])
{
bytes++;
break;
}
}
s++;
}
return (bytes);
}
