#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "functions.h"
#include <sys/stat.h>

/**
 * tokenize_av - tokenize buffer
 *
 * @av: destiation of array of tokens
 * @buffer: source of string
 * @n: number of characters in buffer
 * Return: (Success)
 */
char **tokenize_av(char **av, char *buffer, ssize_t n)
{
	char *buff_copy = malloc(sizeof(char) * (n + 1));
	char *ptr;
	char *ptr2;

	int a = 0;
	int i = 0;


	if (buff_copy == NULL)
	{
		free(buff_copy);
		return (NULL);
	}
	*buff_copy = '\0';

	strcpy(buff_copy, buffer);

	ptr = strtok(buff_copy, " \n");

	while (ptr != NULL)
	{
		a++;

		ptr = strtok(NULL, " \n");
	}
	a = a + 1;

	/*a = number of tokens*/

	av = malloc(sizeof(char *) * a);

	if (av == NULL)
	{
		free_as(av);
		return (NULL);
	}
	*av = '\0';

	ptr2 = strtok(buffer, " \n");

	for (i = 0; ptr2 != NULL; i++)
	{
		av[i] = malloc(sizeof(char) * (strlen(ptr2) + 1));

		strcpy(av[i], ptr2);

		ptr2 = strtok(NULL, " \n");

	}
	av[i] = NULL;

	free(buff_copy);

	return (av);
}

/**
 * free_as - frees memory allocated to array of strings
 * @av: array of stringd
 * Return: (Success)
 */
void free_as(char **av)
{
	int i = 0;

	if (av == NULL)
	{
		free(av);
	}
	else
	{
	while (av[i] != NULL)
	{
		free(av[i]);
		i++;
	}
	free(av[i]);
	free(av);
	}
}
/**
 * check_space - check space
 *
 * @buffer: buffer from getline
 * @chars_read: number of character in buffer
 * Return: (Success)
 */
int check_space(char *buffer, __attribute__((unused))ssize_t chars_read)
{
	int a = 0;
	char *ptr;

	ptr = strtok(buffer, " \n");

	while (ptr != NULL)
	{
		a++;
		ptr = strtok(NULL, " \n");
	}

	if (a == 0)
	{
		return (1);
	}
	else
	{
		return (-1);
	}
}

/**
 * _perror - handle file not found
 * @name: name of compiled file
 *
 * @command: command
 * Return: (Success)
 */
void _perror(char *name, UNUSED char **av, UNUSED int status, UNUSED char **env)
{
	write(2, name, strlen(name));
	write(2, ": 1: ", 5);
	write(2, av[0], strlen(av[0]));
	write(2, ": not found\n", 12);
}
