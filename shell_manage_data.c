 #include "shell.h"

/**
 * clear_data - initializes data_s struct
 * @data: pointer to struct
 */
void clear_data(data_s *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * set_data - initializes data_s struct
 * @data: pointer to struct
 * @argv: arg vector param
 */
void set_data(data_s *data, char **argv)
{
	int i = 0;

	data->prog_fnm = argv[0];
	if (data->arg)
	{
		data->argv = strtow(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;

		alias_change(data);
		vars_change(data);
	}
}

/**
 * free_data - frees data_s struct fields
 * @data: pointer to struct
 * @all: bool param(true) if freeing all fields
 */
void free_data(data_s *data, int all)
{
	vector_free(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->command_buffr)
			free(data->arg);
		if (data->env)
			free_list(&(data->env));
		if (data->history)
			free_list(&(data->history));
		if (data->alias)
			free_list(&(data->alias));
		vector_free(data->environ);
		data->environ = NULL;
		free_bytes((void **)data->command_buffr);
		if (data->retrv_file_descriptor > 2)
			close(data->retrv_file_descriptor);
		_putchar(NEGATIVE_ONE);
	}
}

