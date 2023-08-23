 #include "shell.h"

/**
 * active_terminal - checks if shell is active and returns true
 * @data: pointer to struct
 * Return: 1: if in active mode, else 0
 */
int active_terminal(data_s *data)
{
	return (isatty(STDIN_FILENO) && data->retrv_file_descriptor <= 2);
}

/**
 * _atoi - converts string to integer
 * @s: the string param
 * Return: converted numb, O if no number found in string
 */
int _atoi(char *s)
{
	int i, output;
	int sign = 1, flag = 0;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * _isalpha - checks if char is alphabetic
 * @c: The char param
 * Return: 1 if @c is alphabetic, else returns 0
 */
int _isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/**
 * is_delimiter - checks if char is a delimeter.
 * @c: the char param
 * @delimiters: string containing chars to compare
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char c, char *delimiters)
{
	int s = 0;

	for (; delimiters[s]; s++)
		if (c == delimiters[s])
			return (1);
	return (0);
}
