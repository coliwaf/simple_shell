 #include "shell.h"

/**
 * input_buffer - chains commands in the buffer
 * @data: struct param
 * @buffr: buffer mem address
 * @len: length var mem address
 *
 * Return: returned bytes
 */
ssize_t input_buffer(data_s *data, char **buffr, size_t *len)
{
	ssize_t res = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buffr);
		*buffr = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		res = getline(buffr, &len_p, stdin);
#else
		res = _getline(data, buffr, &len_p);
#endif
		if (res > 0)
		{
			if ((*buffr)[res - 1] == '\n')
			{
				(*buffr)[res - 1] = '\0';
				res--;
			}
			data->ln_count_flag = 1;
			convert_comments(*buffr);
			history_list_update(data, *buffr, data->hist_ln_count++);
			{
				*len = res;
				data->command_buffr = buffr;
			}
		}
	}
	return (res);
}

/**
 * get_input - gets full line except the newline
 * @data: struct param
 *
 * Return: bytes read
 */
ssize_t get_input(data_s *data)
{
	static char *buffr;
	static size_t i, j, len;
	ssize_t res = 0;
	char **buf_p = &(data->arg);
	char *p;

	_putchar(NEGATIVE_ONE);
	res = input_buffer(data, &buffr, &len);
	if (res == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffr + i;

		check_chain(data, buffr, &j, i, len);
		while (j < len)
		{
			if (is_chain(data, buffr, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			data->command_buffer_kind = FLAG_REG;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buffr;
	return (res);
}

/**
 * read_buf - reads a buffer
 * @data: struct param
 * @buffr: buffer
 * @i: size
 *
 * Return: res
 */
ssize_t read_buf(data_s *data, char *buffr, size_t *i)
{
	ssize_t res = 0;

	if (*i)
		return (0);
	res = read(data->retrv_file_descriptor, buffr, GET_BUFFER_SIZE);
	if (res >= 0)
		*i = res;
	return (res);
}
/**
 * _getline - gets the next line of input from STDIN
 * @data: struct param
 * @ptr: address of pointer to buffer as NULL or preallocated
 * @length: len of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(data_s *data, char **ptr, size_t *length)
{
	static char buffr[GET_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t res = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	res = read_buf(data, buffr, &len);
	if (res == -1 || (res == 0 && len == 0))
		return (-1);

	c = _strchr(buffr + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffr) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buffr + i, k - i);
	else
		_strncpy(new_p, buffr + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(NEGATIVE_ONE);
}

