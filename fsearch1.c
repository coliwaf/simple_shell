#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
#include <sys/stat.h>
#include <string.h>

/**
 * which_command - check if command exists
 *
 * @com: command
 * Return: NULL if command doesnt exists else return file_path if it exists
 */
char *which_command(char *com)
{
	char *path = getenv("PATH");
	char *path_copy;
	char *ptr;
	char *fpath;

	struct stat statbuf;

	int len_ptr, len_com, len_total;

	if (stat(com, &statbuf) == 0)
	{
		return (com);
	}

	if (path == NULL)
	{
		return (NULL);
	}
	else
	{
		path_copy = strdup(path);

		ptr = strtok(path_copy, ":");

		while (ptr != NULL)
		{
			len_ptr = strlen(ptr);
			len_com = strlen(com);
			len_total = len_ptr + len_com + 2;

			fpath = malloc(sizeof(char) * len_total);
			*fpath = '\0';

			strcpy(fpath, ptr);
			strcat(fpath, "/");
			strcat(fpath, com);

			if (stat(fpath, &statbuf) == 0)
			{
				free(path_copy);

				return (fpath);
			}
			else
			{
			free(fpath);

			ptr = strtok(NULL, ":");

			fpath = NULL;
			}
		}

		if (stat(com, &statbuf) == 0)
		{
			free(path_copy);
			return (com);
		}
		else
		{
		free(path_copy);
		return (NULL);
		}
	}
}
