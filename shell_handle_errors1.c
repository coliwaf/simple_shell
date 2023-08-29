 #include "shell.h"

/**
 * numb_atoi_err - converts a string to integer
 * @s: the string to convert
 * Return: converted number else 0 if no numbers,
 *       -1 on error
 */
int numb_atoi_err(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else if (s[i] < '0')
		{
			return (-2);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints error message
 * @data: the struct param
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(data_s *data, char *estr)
{
	err_puts(data->prog_fnm);
	err_puts(": ");
	print_d(data->ln_count, STDERR_FILENO);
	err_puts(": ");
	err_puts(data->argv[0]);
	err_puts(": ");
	err_puts(estr);
}

/**
 * print_d - function prints a base 10 integer
 * @input: the input param
 * @file_descr: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int file_descr)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (file_descr == STDERR_FILENO)
		__putchar = err_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 *  convert_numb_base - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_numb_base(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CHANGE_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CHANGE_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	while (n != 0)
	{
		*--ptr = array[n % base];
		n /= base;
	}

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * convert_comments - function replaces first instance of '#' with '\0'
 * @buffr: address of the string to modify
 *
 * Return: Always 0;
 */
void convert_comments(char *buffr)
{
	int i;

	for (i = 0; buffr[i] != '\0'; i++)
		if (buffr[i] == '#' && (!i || buffr[i - 1] == ' '))
		{
			buffr[i] = '\0';
			break;
		}
}

