#include "shell.h"

/**
 * free_bytes - frees and Nulls the address
 * @ptr: pointer addr to free
 * Return: if freed return 1, otherwise 0
 */
int free_bytes(void **ptr)
{
	if (ptr && *ptr)
	{
	free(*ptr);
	*ptr = NULL;
	return (1);
	}
	return (0);
}

/**
 * vector_free - frees a 2d char array(string of strings)
 * @vectr: char array to free
 */
void vector_free(char **vectr)
{
	char **a = vectr;

	if (!vectr)
		return;

	while (*vectr)
		free(*vectr++);

	free(a);
}

/**
 * _memset - fills memory with const byte
 * @s: pointer param
 * @b: byte to fill with @s
 * @n: number of bytes to fill
 * Return: pointer to @s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;

	return (s);
}

/**
 * _realloc - resizes a block of memory
 * @ptr: pointer to previously allocated memory block
 * @old_size: byte from previous block
 * @new_size: byte from new block
 * Return: pointer to newly allocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size > new_size ? new_size : old_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
