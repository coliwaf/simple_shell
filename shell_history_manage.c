 #include "shell.h"

/**
 * history_file_get - gets the file containing history
 * @data: struct param
 *
 * Return: allocated string containing history file
 */
char *history_file_get(data_s *data)
{
	char *buffr, *dir;

	dir = _getenv(data, "HOME=");
	if (!dir)
		return (NULL);
	buffr = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE_NM) + 2));
	if (!buffr)
		return (NULL);
	buffr[0] = 0;
	_strcpy(buffr, dir);
	_strcat(buffr, "/");
	_strcat(buffr, HIST_FILE_NM);
	return (buffr);
}

/**
 * create_update_history - creates a file, or appends to existing file
 * @data: the struct param
 *
 * Return: 1 on success, else -1
 */
int create_update_history(data_s *data)
{
	ssize_t file_descr;
	char *filename = history_file_get(data);
	list_s *node = NULL;

	if (!filename)
		return (-1);

	file_descr = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_descr == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		puts_file_descr(node->str, file_descr);
		put_file_descr('\n', file_descr);
	}
	put_file_descr(NEGATIVE_ONE, file_descr);
	close(file_descr);
	return (1);
}

/**
 * get_history - function reads history from specified file
 * @data: the struct param
 *
 * Return: hist_ln_count on success, 0 otherwise
 */
int get_history(data_s *data)
{
	int i, last = 0, ln_count = 0;
	ssize_t file_descr, rdlen, fsize = 0;
	struct stat st;
	char *buffr = NULL, *filename = history_file_get(data);

	if (!filename)
		return (0);

	file_descr = open(filename, O_RDONLY);
	free(filename);
	if (file_descr == -1)
		return (0);
	if (!fstat(file_descr, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffr = malloc(sizeof(char) * (fsize + 1));
	if (!buffr)
		return (0);
	rdlen = read(file_descr, buffr, fsize);
	buffr[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffr), 0);
	close(file_descr);
	for (i = 0; i < fsize; i++)
		if (buffr[i] == '\n')
		{
			buffr[i] = 0;
			history_list_update(data, buffr + last, ln_count++);
			last = i + 1;
		}
	if (last != i)
		history_list_update(data, buffr + last, ln_count++);
	free(buffr);
	data->hist_ln_count = ln_count;
	while (data->hist_ln_count-- >= HIST_MAX_SIZE)
		del_node_at_idx(&(data->history), 0);
	history_renumber(data);
	return (data->hist_ln_count);
}

/**
 * history_list_update - appends entry to a linked list history
 * @data: Struct containing potential args
 * @buffr: buffer
 * @ln_count: the history ln_count, hist_ln_count
 *
 * Return: Always 0
 */
int history_list_update(data_s *data, char *buffr, int ln_count)
{
	list_s *node = NULL;

	if (data->history)
		node = data->history;
	add_to_node_end(&node, buffr, ln_count);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * history_renumber - changes the renumbers the history linked list
 * @data: Struct containing potential args
 *
 * Return: the new hist_ln_count
 */
int history_renumber(data_s *data)
{
	list_s *node = data->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (data->hist_ln_count = i);
}

