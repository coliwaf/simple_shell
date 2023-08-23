#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"
/**
 * _cd - changes directory of path
 * 
 * @name: name of shell
 * @av: array of commands and arguments
 * @status: exit status
 * Return: (Success)
 */
void _cd(UNUSED char *name, char **av, UNUSED int status, UNUSED char **env)
{
	char buff[100];
	char *cwd = getcwd(buff, 100);

	if (av[1] == NULL)
	{
		chdir("~");

		if (isatty(STDIN_FILENO))
		{
			exit(0);
		}
	}
	else if (strcmp(av[1], "-") == 0)
	{
		cwd = getenv("PWD");

		chdir(getenv("OLDPWD"));

		setenv("PWD", getcwd(buff, 100), 2);
		setenv("OLDPWD", cwd, 2);

		if (isatty(STDIN_FILENO))
		{
		}
		else
		{
		printf("%s\n", getcwd(buff, 100));
		exit(0);
		}
	}
	else
	{
		chdir(av[1]);

		setenv("PWD", getcwd(buff, 100), 2);
	
		if (isatty(STDIN_FILENO))
		{
		}
		else
		{
		printf("%s\n", getcwd(buff, 100));
		exit(0);
		}
	}
}
