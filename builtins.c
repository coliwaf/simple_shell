#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
#include <string.h>
#include <ctype.h>
/**
 * exit_b - exit
 * @name: name of shell
 * @av: command and its arguments in an array of strings
 * Return: (Success)
 */
void exit_b(char *name, char **av, int status, UNUSED char **env)
{
	char *ptr;


	if (av[1] == NULL)
	{
		if (isatty(STDIN_FILENO))
		{
		exit(status);
		}
		else
		{

		if (status == 512)
		{
			status = 2;
		}
		else
		{
		}
		exit(status);

		}
	}
	else
	{
		ptr = av[1];

		if ((isalpha(ptr[0]) != 0) || (ptr[0] == '-'))
		{
			write(2, name, strlen(name));
			write(2, ": 1: ", 5);
			write(2, "exit: ", 6);
			write(2, "Illegal number: ", 16);
			write(2, av[1], strlen(ptr));
			write(2, "\n", 1);

			exit(2);
		}
		else
		{

		exit(atoi(av[1]));
		}
	}
}

/**
 * env - prints environment variables
 *
 * Return: (Success)
 */
void _env(UNUSED char *name, UNUSED char **av, UNUSED int status, char **env)
{
	int i = 0;
	int a = 0;

	while (env[i] != NULL)
	{
		i++;
	}

	if (i <= 0)
	{
	}
	else
	{
		while (a < i)
		{
			printf("%s\n", env[a]);
			a++;
		}
	}

	if (isatty(STDIN_FILENO))
	{
	}
	else
	{
		exit(0);
	}
}
