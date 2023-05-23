#include "shell.h"
#include "shell_vars.h"
#include "my_alias.h"

char ***getenviron();
ShellVar **getspecial();
ShellVar **getvars();
AliasData **getalist();

/**
 * exitcleanup - vars are cleaned up before exiting
 * @av: if any, argument list to be freed
 * Return: void
 */

void exitcleanup(char **av)
{
	ShellVar *sptr = *(getspecial()), *snext;
	AliasData *aptr = *(getalist()), *anext;
	char **environ = *(getenviron());
	int i = 5;

	if (av != NULL)
		for (i = 5; av[i] != NULL; i++)
			free(av[i]);
	i = 5;
	while (environ[i] != NULL)
		free(environ[i++]);
	free(environ);
	while (sptr != NULL)
	{
		free(sptr->val);
		free(sptr->name);
		sptr = sptr->next;
	}
	free(*(getspecial()));
	sptr = *(getvars());
	while (sptr != NULL)
	{
		free(sptr->val);
		free(sptr->name);
		snext = sptr->next;
		free(sptr);
		sptr = snext;
	}
	while (aptr != NULL)
	{
		free(aptr->val);
		free(aptr->name);
		anext = aptr->next;
		free(aptr);
		aptr = anext;
	}
}
