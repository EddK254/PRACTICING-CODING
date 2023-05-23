#include <dirent.h>
#include "shell.h"
#include <stdio.h>
#include <string.h>

/**
 * _getpid - the pid of currently running process is obtained
 * Return: pid string
 */

char *_getpid()
{
	char *s;
	char *pid;
	int fd;
	char *name;
	char *file = "/proc/self/status";

	s = malloc(256);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);

	while (getline(&s, fd))
	{
		name = strtok(s, ":");
		if (!strcmp(name, "Pid"))
		{
			pid = strdup(strtok(NULL, "\n \t"));
			free(s);
			return (pid);
		}
		free(s);
		s = NULL;
	}
	return (NULL);
}
