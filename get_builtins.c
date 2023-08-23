#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <unistd.h>
#include <string.h>
/**
 * get_builtins - get builtins functions and executes them
 *
 * @cmd: command
 * @av: arrays of strings
 * Return: -1 on failure else 1 on success
 */
void (*get_builtins(char *cmd))(char *name, char **av, int status, UNUSED char **env)
{

get_b built[] = {

	{"exit", exit_b},
	{"cd", _cd},
	{"env", _env},
	/*{"alias", _alias},*/
	{"_perror", _perror},
	{NULL, NULL},
};

int i = 0;

	while (built[i].com != NULL)
	{
		if (strcmp(built[i].com, cmd) == 0)
		{
			return (built[i].f);
		}
		i++;
	}

return(built[i -1].f);
}
