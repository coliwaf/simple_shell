#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "functions.h"
/**
 * main - C shell
 *
 * @argv: command and its arguments
 * @argc: number of arguments - we shall not use it
 * @env: environment
 * Return: -1 if error but +1 if successfull
 */
int main(__attribute__((unused))int argc, char **argv, char **env)
{
	char *buffer = NULL;
	char *name = argv[0];
	char **av;
	char *fpath;
	char *cwd;

	ssize_t chars_read;
	size_t i = 0;
	int pid;
	int status = 0;
	int n;

	while (1)
	{
		cwd = getenv("PWD");

		print_prompt(cwd);

		chars_read = getline(&buffer, &i, stdin);

		if (chars_read < 0)
		{
			free(buffer);
			buffer = NULL;

			if (isatty(STDIN_FILENO))
			{
				write(2, "\nHshell logging out\nhappy coding punk hahaha\n", 45);
			}
			exit(0);
		}

		av = tokenize_av(argv, buffer, chars_read);

		if (av == NULL)
		{
			free(buffer);
			free_as(av);
			exit(127);
		}

		n = check_space(buffer, chars_read);

		if (n == 1)
		{
			continue;
		}
		/*av = array of tokens*/

		fpath = which_file(av[0]);

		if (fpath == NULL)
		{
			free(fpath);
		
			get_builtins(av[0])(name, av, status, env);
			/*_perror(name, av[0]);*/

			if (isatty(STDIN_FILENO))
			{

			}
			else
			{
			/*free_as(av);*/
			/*free(buffer);*/
			exit(127);
			}
		}
		else
		{
			pid = fork();

			if (pid == 0)
			{

			execute_command(fpath, av, env);
			}
			wait(&status);
			WEXITSTATUS(status);

		}

		if (strchr(av[0], '/') == NULL)
		{
			free(fpath);
		}

		free(buffer);
		buffer = NULL;
		free_as(av);
	}

exit(0);
}
