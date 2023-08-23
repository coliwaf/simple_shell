 #include "shell.h"

/**
 * get_environ - returns copy of the environ vars as string array
 * @data: Struct containing potential args
 *
 * Return: array of strings containing environment vars
 */
char **get_environ(data_s *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = _list_t_str(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}

/**
 * _unsetenv - Remove environment var
 * @data: Struct containing potential args
 *
 *  Return: 1 on successful delete, else 0
 * @var: string env var param
 */
int _unsetenv(data_s *data, char *var)
{
	list_s *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = str_starts_with(node->str, var);
		if (p && *p == '=')
		{
			data->env_changed = del_node_at_idx(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_changed);
}
/**
 * _setenv - Initialize a new environment variable,
 *             or modify existing one
 * @data: Struct containing potential args
 *
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(data_s *data, char *var, char *value)
{
	char *buffr = NULL;
	list_s *node;
	char *p;

	if (!var || !value)
		return (0);

	buffr = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffr)
		return (1);
	_strcpy(buffr, var);
	_strcat(buffr, "=");
	_strcat(buffr, value);
	node = data->env;
	while (node)
	{
		p = str_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffr;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_to_node_end(&(data->env), buffr, 0);
	free(buffr);
	data->env_changed = 1;
	return (0);
}

