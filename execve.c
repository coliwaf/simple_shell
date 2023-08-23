#include <stdio.h>
#include <unistd.h>
#include "functions.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
/**
 * execute_command - executes commands on path
 *
 * @com: command
 * @args: arguments
 * @env: environment
 * Return: (Success)
 */
void execute_command(char *com, char **args, char **env)
{
	if (execve(com, args, env) == -1)
	{
		write(2, "-Hshell : ", 7);
		write(2, args[0], strlen(args[0]));
		write(2, ": command not found", 19);
	}
}
