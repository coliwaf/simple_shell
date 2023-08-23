 #include "shell.h"

/**
 * err_puts - prints input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void err_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		err_putchar(str[i]);
		i++;
	}
}

/**
 * err_putchar - writes the char c to stderr
 * @c: The char to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int err_putchar(char c)
{
	static int i;
	static char buffr[WRITE_FULL_BUFFER_SIZE];

	if (c == NEGATIVE_ONE || i >= WRITE_FULL_BUFFER_SIZE)
	{
		write(2, buffr, i);
		i = 0;
	}
	if (c != NEGATIVE_ONE)
		buffr[i++] = c;
	return (1);
}

/**
 * put_file_descr - writes the char c to given file descr
 * @c: The char to print
 * @file_descr: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_file_descr(char c, int file_descr)
{
	static int i;
	static char buffr[WRITE_FULL_BUFFER_SIZE];

	if (c == NEGATIVE_ONE || i >= WRITE_FULL_BUFFER_SIZE)
	{
		write(file_descr, buffr, i);
		i = 0;
	}
	if (c != NEGATIVE_ONE)
		buffr[i++] = c;
	return (1);
}

/**
 * puts_file_descr - prints input string
 * @str: the string to be printed
 * @file_descr: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int puts_file_descr(char *str, int file_descr)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_file_descr(*str++, file_descr);
	}
	return (i);
}

