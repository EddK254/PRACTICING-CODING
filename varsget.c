#include "shell_vars.h"

/**
 * getspecial - the getspecial static var wrapper
 * Return: shellvar special address
 */

ShellVar **getspecial()
{
	static ShellVar *special;

	return (&special);
}

/**
 * getsvars - obtain static vars wrapper
 *
 * Return: var address
 */

ShellVar **getvars()
{
	static ShellVar *vars;

	return (&vars);
}
