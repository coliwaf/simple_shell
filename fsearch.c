#include "functions.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"
/*
 * which_file - find command path
 * @c: command
 * Return: (Success)
 */
char *which_file(char *c)
{
	char *path = getenv("PATH");

	char *cpath; char *aot; char *ptr;

	struct stat statbuff;

	int ld = 0, a = 0;

	const char *dlim = ":";

	if (path)
	{
	if (strcmp(c, "env") == 0)
	{
		return (NULL);
	}

	cpath = strdup(path);

	ptr = strtok(cpath, dlim);

	a = strlen(c);

	while (ptr != NULL)
	{
		ld = strlen(ptr);

		aot = malloc(ld + a + 2);
		*aot = '\0';

		strcpy(aot, ptr);

		strcat(aot, "/");
		strcat(aot, c);
		strcat(aot, "\0");


		if (stat(aot, &statbuff) == 0)
		{
			free(cpath);
			return (aot);
		}
		else
		{
			free(aot);

			ptr = strtok(NULL, dlim);
		}
	}


	free(cpath);

	if (stat(c, &statbuff) == 0)
	{

		return (c);
	}
	return (NULL);
	}

	if (stat(c, &statbuff) == 0)
	{
		return (c);
	}
return (NULL);
}
