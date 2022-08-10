#include "shell.h"
#include "alias.h"
/**
 * getalist - static wrapper getalias list
 * Return: address alist
 *
 */
AliasData **getalist()
{
	static AliasData *alist;

	return (&alist);
}
/**
 * getalias - get alias value
 * returns original argument if not found
 * @name: name of alias
 * Return: original argument if not found, otherwise value
 */
char *getalias(char *name)
{
	AliasData *alist = *(getalist());
	AliasData *ptr = alist;

	while (ptr != NULL && _strcmp(ptr->name, name))
	{
#ifdef DEBUGMODE
		printf("Checked .%s. against .%s.\n", name, ptr->name);
#endif
		ptr = ptr->next;
	}
	if (ptr == NULL)
	{
#ifdef DEBUGMODE
		printf("Alias not found %s\n", name);
#endif
		return (name);
	}
#ifdef DEBUGMODE
	printf("Checking alias %s\n", ptr->val);
#endif

	free(name);
	return (getalias(_strdup(ptr->val)));
}
/**
 * setalias - set alias and value
 * @name: name of alias
 * @val: value to set alias to
 * Return: 0 upon success
 */
int setalias(char *name, char *val)
{
	AliasData **alistroot = getalist();
	AliasData *alist = *alistroot;
	AliasData *ptr = alist, *new;

	if (alist == NULL)
	{
		new = malloc(sizeof(AliasData));
		if (new == NULL)
			return (-1);
		new->name = name;
		new->val = val;
		new->next = NULL;
		*alistroot = new;
		return (0);
	}
	while (_strcmp(ptr->name, name) && ptr->next != NULL)
		ptr = ptr->next;
	if (!_strcmp(ptr->name, name))
	{
		free(ptr->val);
		ptr->val = val;
		free(name);
	}
	else
	{
		new = malloc(sizeof(AliasData));
		if (new == NULL)
			return (-1);
		new->name = name;
		new->val = val;
		new->next = NULL;
		ptr->next = new;
	}
	return (0);
}
