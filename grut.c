#include "shell.h"
#include <stdio.h>
#include <string.h>

/**
 * help - this is the builtin help command
 * @cmd: the inserted command line
 * Return: 0 if sucessful (always successful)
 */

int help(char *cmd)
{
	char *s;
	int fd, r;
	char *file;

	if (cmd == NULL)

	{
		s = "help: no builtin entered.\n";

		r = strlen(s);

		r = write(1, s, r);

		return (0);
	}

	if (!strcmp(cmd, "cd"))

	{
		file = "help_cd";

		fd = open(file, O_RDWR);

		s = malloc(256);

		if (s == NULL)

			return (-1);

		while ((r = read(fd, s, 256)) > 0)

		{
			r = write(1, s, r);

			if  (r == -1)

			{
				return (-1);
			}
		}

		free(s);

		fd = close(fd);

		return (0);
	}

	else if (!strcmp(cmd, "history"))

	{
		file = "help_hist";

		fd = open(file, O_RDWR);

		s = malloc(256);

		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);

			if  (r == -1)

			{
				return (-1);
			}
		}

		free(s);

		fd = close(fd);

		return (0);
	}

	else if (!strcmp(cmd, "help"))

	{
		file = "help_hel";

		fd = open(file, O_RDWR);

		s = malloc(256);

		if (s == NULL)

			return (-1);

		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);

			if  (r == -1)
			{
				return (-1);
			}
		}

		free(s);

		fd = close(fd);

		return (0);
	}

	else if (!strcmp(cmd, "alias"))

	{
		file = "help_al";

		fd = open(file, O_RDWR);

		s = malloc(256);

		if (s == NULL)

			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);

			if  (r == -1)

			{
				return (-1);
			}
		}

		free(s);

		fd = close(fd);

		return (0);
	}
	else if (!strcmp(cmd, "unset"))
	{
		file = "help_unset";

		fd = open(file, O_RDWR);

		s = malloc(256);

		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);

			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);

		fd = close(fd);

		return (0);
	}
	else if (!strcmp(cmd, "unalias"))
	{
		file = "help_unal";

		fd = open(file, O_RDWR);

		s = malloc(256);

		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);

			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);

		fd = close(fd);

		return (0);
	}
	else if (!strcmp(cmd, "env"))
	{
		file = "help_env";

		fd = open(file, O_RDWR);

		s = malloc(256);

		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);

			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);

		fd = close(fd);

		return (0);
	}
	else if (!strcmp(cmd, "setenv"))
	{
		file = "help_setenv";

		fd = open(file, O_RDWR);

		s = malloc(256);

		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);
			if  (r == -1)
			{
				return (-1);
			}
		}
		free(s);

		fd = close(fd);

		return (0);
	}
	else if (!strcmp(cmd, "unsetenv"))
	{
		file = "help_unenv";

		fd = open(file, O_RDWR);

		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((r = read(fd, s, 256)) > 0)
		{
			r = write(1, s, r);
			if  (r == -1)
			{
				return (-1);
			}
		}

		free(s);

		fd = close(fd);

		return (0);
	}
	else
	{
		s = "help: no help topics match.\n";

		r = strlen(s);

		r = write(1, s, r);

		return (0);
	}
}
