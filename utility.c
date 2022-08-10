#include "shell.h"
#include <stdarg.h>
/**
 * linecount - count lines
 *
 * @increment: icnrementer
 *
 * Return: count
 */
int linecount(int increment)
{
	static int count;

	count = count + increment;

	return (count);
}
/**
 * itos - converts integer to string
 *
 * @digits: int
 *
 * Return: a string
 */
char *itos(int digits)
{
	int count, i, neg, absMod, digitTest;
	char *output;

	digitTest = digits;
	count = 0;
	neg = 0;
	if (digits == 0)
	{
		output = malloc(sizeof(char) * 2);
		output[0] = '0';
		output[1] = 0;
		return (output);
	}
	if (digits < 0)
	{
		neg = 1;
		count++;
	}
	while (digitTest != 0)
	{
		digitTest /= 10;
		count++;
	}
	output = malloc(sizeof(char) * count + 1);
	if (output == NULL)
		return (NULL);
	if (neg)
		output[0] = '-';
	digitTest = digits;
	for (i = count - 1; i >= 0 + neg; i--)
	{
		absMod = digitTest % 10;
		output[i] = (absMod < 0 ? -absMod : absMod) + '0';
		digitTest /= 10;
	}
	output[count] = '\0';
	return (output);
