#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * print_prompt - prints prompt
 * @cwd: current working directory
 *
 * Return: (Success);
 */
int print_prompt(char *cwd)
{
	char *user = getenv("USER");
	/*char *user_name = getenv("SUDO_USER");*/
	/*char *hostname = get_host_name();*/

	if (isatty(STDIN_FILENO))
	{
		write(1, user, strlen(user));
		/*write(1, hostname, strlen(hostname));*/
		/*write(1, "@[", 2);*/
		/*write(1, user_name, strlen(user_name));*/
		/*write(1, "]", 1);*/
		write(1, ":", 1);
		write(1, cwd, strlen(cwd));
		write(1, "$ ", 2);
		return (0);
	}
	return (-1);
}
