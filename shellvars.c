#include "shell.h"
#include "shellvars.h"
/**
 * initsvars - initialize vars
 * @ac: arguemnts intiger
 * @av: string arguments
 * Return: int
 */
int initsvars(int ac, char **av)
{
	ShellVar **specialroot = getspecial();
	ShellVar *special;
	ShellVar *ptr;
	int i = 0;
	char nums[2] = {0, 0};

	/* 0-9, #, $, ?, dash, underscore */
	*specialroot = malloc(sizeof(ShellVar) * 15);
	if (*specialroot == NULL)
		return (-1);
	special = *specialroot;
#ifdef DEBUGMODE
	printf("special:%p:*getspecial():%p:\n", special, *(getspecial()));
#endif
	special->val = _strdup("0");
	special->name = _strdup("?");
	ptr = special + 1;
	special->next = ptr;
	while (av[i] != NULL)
	{
#ifdef DEBUGMODE
		printf("av[%d]=%s\n", i, av[i]);
#endif
		nums[0] = i + '0';
		ptr->val = _strdup(av[i]);
		ptr->name = _strdup(nums);
		ptr->next = ptr + 1;
		ptr = ptr->next;
		i++;
	}
	while (i < 10)
	{
		nums[0] = i + '0';
		ptr->val = _strdup("0");
		ptr->name = _strdup(nums);
		ptr->next = ptr + 1;
		ptr = ptr->next;
		i++;
	}
	ptr->name = _strdup("$");
	ptr->val = _strdup("0");
	ptr->next = ptr + 1;
	ptr = ptr->next;
	ptr->name = _strdup("#");
	ptr->val = itos(ac);
	ptr->next = NULL;
	return (0);
}
