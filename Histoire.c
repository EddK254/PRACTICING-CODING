#include "shell.h"
#include <stdio.h>
#include <string.h>
#include "history.h"

/**
 * gethistory - history list obtained
 * Return: 0 if successful
 */

HistList **gethistory()
{
	static HistList *hlist;

	return (&hlist);
}

/**
 * sethist - value and hist are set
 * @cmd: the command
 * Return: 0 upon success
 */

int sethist(char *cmd)
{
	HistList **hlistroot = gethistory();
	HistList *hlist = *hlistroot;
	HistList *ptr = hlist, *new;

	if (hlist == NULL)
	{
		new = malloc(sizeof(HistList));
		if (new == NULL)
			return (-1);

		new->cmd = strdup(cmd);
		new->next = NULL;
		*hlistroot = new;
		return (0);
	}
	while (ptr->next != NULL)
		ptr = ptr->next;

	new = malloc(sizeof(HistList));
	if (new == NULL)
		return (-1);
	new->cmd = strdup(cmd);
	new->next = NULL;
	ptr->next = new;
	return (0);
}

/**
 * print_hist - all elements of listint printed
 *
 * Return: the number of elements
 */

int print_hist(void)
{
	HistList **hlistroot = gethistory();
	HistList *h = *hlistroot;
	int i;
	int len, numlen;
	char *s, *num;

	i = 0;
	while (h != NULL)
	{
		len = strlen(h->cmd);
		s = h->cmd;
		num = itos(i);
		numlen = strlen(num);
		write(1, num, numlen);
		putchar(' ');
		write(1, s, len);
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * exit_hist - history exited and copy to file
 * Return: int
 */

int exit_hist(void)
{
	int fd;
	char *file = ".simple_shell_history";
	int len;
	char *s;

	HistList **hlistroot = gethistory();
	HistList *hlist = *hlistroot;
	HistList *ptr = hlist;

	fd = open(file, O_CREAT | O_RDWR, 0600);
	if (fd == -1)
		return (-1);

	while (hlist != NULL)
	{
		ptr = hlist->next;
		s = hlist->cmd;
		len = strlen(s);
		write(fd, s, len);
		free(hlist->cmd);
		free(hlist);
		hlist = ptr;
	}

	close(fd);
	return (1);
}
