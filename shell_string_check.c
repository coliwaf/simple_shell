#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @data: the struct param
 * @buffr: the char buffer
 * @p: address of current position in buffr
 * Return: if chain delimeter ret 1, else ret 0
 */
int is_chain(data_s *data, char *buffr, size_t *p)
{
	size_t j = *p;

	if (buffr[j] == '|' && buffr[j + 1] == '|')
	{
		buffr[j] = 0;
		j++;
		data->command_buffer_kind = OR_FLAG;
	}
	else if (buffr[j] == '&' && buffr[j + 1] == '&')
	{
		buffr[j] = 0;
		j++;
		data->command_buffer_kind = AND_FLAG;
	}
	else if (buffr[j] == ';')
	{
		buffr[j] = 0;
		data->command_buffer_kind = CHAIN_FLAG;
	}
	else
		return (0);

	*p = j;
	return (1);
}

/**
 * alias_change - changes aliases from strings that are tokenized
 * @data: the struct param
 *
 * Return: 1 if replaced, else 0
 */
int alias_change(data_s *data)
{
	int i;
	list_s *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_start_elem(data->alias, data->argv[0], '=');
		if (!node)
			return (0);

		free(data->argv[0]);

		p = _strchr(node->str, '=');

		if (!p)
			return (0);

		p = _strdup(p + 1);
		if (!p)
			return (0);
		data->argv[0] = p;
	}
	return (1);
}

/**
 * check_chain - checks if chaining continues based on last status
 * @data: the struct param
 * @buffr: the char buffer
 * @p: address of current position in buffr
 * @i: starting position in buffr
 * @len: length of buffr
 */
void check_chain(data_s *data, char *buffr, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (data->command_buffer_kind == AND_FLAG)
	{
		if (data->status)
		{
			buffr[i] = 0;
			j = len;
		}
	}

	if (data->command_buffer_kind == OR_FLAG)
	{
		if (!data->status)
		{
			buffr[i] = 0;
			j = len;
		}
	}

	*p = j;
}


/**
 * string_change - replaces string with new one
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int string_change(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * vars_change - replaces vars in the string that is tokenized
 * @data: the struct param
 * Return: 1 if replaced, 0 otherwise
 */
int vars_change(data_s *data)
{
	int i = 0;
	list_s *node;

	for (i = 0; data->argv[i]; i++)
	{
		if (data->argv[i][0] != '$' || !data->argv[i][1])
			continue;

		if (!_strcmp(data->argv[i], "$?"))
		{
			string_change(&(data->argv[i]),
			_strdup(convert_numb_base(data->status, 10, 0)));
			continue;
		}

		if (!_strcmp(data->argv[i], "$$"))
		{
			string_change(&(data->argv[i]),
			_strdup(convert_numb_base(getpid(), 10, 0)));
			continue;
		}
		node = node_start_elem(data->env, &data->argv[i][1], '=');
		if (node)
		{
			string_change(&(data->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		string_change(&data->argv[i], _strdup(""));

	}

	return (0);
}
