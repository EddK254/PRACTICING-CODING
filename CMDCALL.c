#include "shell.h"
#include <stdio.h>
#include <string.h>

/**
 * checkpath - path is checked
 * @av: the arguments
 * Return: 1
 */

int checkpath(char *av[])
{
	char *path, *pathptr, *pathvar, *ptr, *pathenv = "PATH", *linect;
	int pathlen, cmdlen;

#ifdef DEBUGMODE
	printf("In checkpath\n");
#endif
	for (ptr = av[0], cmdlen = 0; *ptr != 0; ptr++)
		cmdlen++;
	pathvar = getenv(pathenv);
	if (pathvar != pathenv)
	{
		pathenv = pathvar;
		while (*pathvar != 0)
		{
#ifdef DEBUGMODE
			printf("in loop pathvar:%s:*pathvar:%c\n", pathvar, *pathvar);
#endif
			for (pathlen = 0, ptr = pathvar; *ptr != 0 && *ptr != ':'; ptr++)
				pathlen++;
			path = malloc(sizeof(char) * (cmdlen + pathlen + 2));
			if (path == NULL)
			{
				free(pathenv);
				return (-1);
			}
			pathptr = path;
			while (*pathvar != ':' && *pathvar != 0)
				*pathptr++ = *pathvar++;
			if (pathptr != path)
				*pathptr++ = '/';
			ptr = av[0];
			while (*ptr != 0)
				*pathptr++ = *ptr++;
			*pathptr = 0;
			if (!access(path, F_OK))
			{
#ifdef DEBUGMODE
				printf("Found path:%s\n", path);
#endif
				pathlen = cmdcall(av, path);
				free(path);
				free(pathenv);
				return (pathlen);
			}
			free(path);
			if (*pathvar == ':')
				pathvar++;
		}
	}
	linect = itos(lineCount(0));
	path = getSvar("0");
	fprintstrs(2, path, ": ", linect, ": ", av[0], ": not found\n", NULL);
	free(path);
	free(linect);
	if (pathenv != pathvar)
		free(pathenv);
	return (127);
}
/**
 * cmdcall - it calls the commands
 * @av: the arguments
 * @cmd: the command
 * Return: retval
 */

int cmdcall(char *av[], char *cmd)
{
	pid_t command;
	int status;
	char *linect, *dolz;

#ifdef DEBUGMODE
	printf("In cmdcall av[0]:%s\n", av[0]);
#endif
	environ = getAllEnv();
	if (environ == NULL)
		return (-1);
#ifdef DEBUGMODE
	printf("Forking\n");
#endif
	command = fork();
#ifdef DEBUGMODE
	printf("command:%d\n", command);
	fflush(stdout);
#endif
	if (command == 0)
	{
#ifdef DEBUGMODE
		printf("Executing %s\n", av[0]);
#endif
		if (execve(cmd, av, *(getEnviron())) == -1)
		{
			if (!access(cmd, F_OK))
			{
				printerr(NULL);
				exit(126);
			}
			else
			{
				linect = itos(lineCount(0));
				dolz = getSvar("0");
				fprintstrs(2, dolz, ": ", linect, ": ", cmd, ": not found\n", NULL);
				free(dolz);
				free(linect);
				exit(127);
			}
			exit(1);
		}
#ifdef DEBUGMODE
		printf("Command done\n");
#endif
	}
	else
	{
		wait(&status);
	}
#ifdef DEBUGMODE
	printf("Status %d\n", status);
#endif
	free(environ);
	return (status);
}

/**
 * builtincall - this calls the builtin commands
 * @av: the arguments
 * Return: retval
 */

int builtincall(char *av[])
{
	int retval = 0;
	char *retstr;

	if (av[0] == NULL)
		return (0);
#ifdef DEBUGMODE
	printf("In builtincall %p\n%s\n", av[0], av[0]);
	printf("av[1]:%s\n", av[1]);
#endif
	if (!strcmp(av[0], "exit"))
	{
		if (av[1] != NULL)
			if (av[1][0] >= '0' && av[1][0] <= '9')
			{
				retval = atoi(av[1]);
				exitcleanup(av);
				exit_hist();
				exit(retval);
			}
			else
			{
				printerr(": exit: Illegal number: ");
				fprintstrs(STDERR_FILENO, av[1], "\n", NULL);
				retval = 2;
			}
		else
		{
			retstr = getSvar("?");
			retval = atoi(retstr);
			free(retstr);
			exitcleanup(av);
			exit_hist();
			exit(retval);
		}
	}
	else if (!strcmp(av[0], "cd"))
		retval = _cd(av);
/*
 *
 * else if (!strcmp(av[0], "getenv"))
 *	retval = !printf("%s\n", getenv(av[1]));
*/
	else if (!strcmp(av[0], "history"))
		retval = print_hist();
	else if (!strcmp(av[0], "help"))
		retval = help(av[1]);
	else if (!strcmp(av[0], "env"))
		retval = printEnv();
	else if (!strcmp(av[0], "setenv"))
		retval = setenv(av[1], av[2]);
	else if (!strcmp(av[0], "unsetenv"))
		retval = unsetenv(av[1]);
	else if (!strcmp(av[0], "alias"))
		retval = aliasCmd(av);
	else if (!strcmp(av[0], "unset"))
		retval = unsetSvar(av[1]);
	else if (!strcmp(av[0], "unalias"))
		retval = unsetAlias(av[1]);
	else if (av[0][0] != '/' &&
		 !(av[0][0] == '.' && (av[0][1] == '/' ||
				       (av[0][1] == '.' && av[0][2] == '/'))))
		retval = checkpath(av);
	else
		retval = cmdcall(av, av[0]);
#ifdef DEBUGMODE
	printf("After call back in builtin retval:%d\n", retval);
#endif
	if (retval % 256 == 0)
		retval /= 256;
	retstr = itos(retval % 128);
#ifdef DEBUGMODE
	printf("Status string:%s\n", retstr);
#endif
	setSvar("?", retstr);
	free(retstr);
	return (retval);
}
