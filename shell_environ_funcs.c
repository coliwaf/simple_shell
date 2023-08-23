#include "shell.h"

/**
 * prnt_env - prints current env
 * @data: Struct containing potential args
 *
 * Return: Always 0
 */
int prnt_env(data_s *data)
{
	prnt_list_str_elem(data->env);
	return (0);
}

/**
 * _getenv - gets val of environ var
 * @data: Struct containing potential args
 * @name: env var param
 *
 * Return: the value
 */
char *_getenv(data_s *data, const char *name)
{
	list_s *node = data->env;
	char *ptr;

	while (node)
	{
		ptr = str_starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_the_environ - Initialize a new environment variable,
 * or modify existing one
 * @data: Struct containing potential args
 *
 *  Return: Always 0
 */
int set_the_environ(data_s *data)
{
	if (data->argc != 3)
	{
		err_puts("Improper number of arguments\n");
		return (1);
	}
	if (_setenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_the_environ - Remove environment variable
 * @data: Struct containing potential args
 *
 * Return: Always 0
 */
int unset_the_environ(data_s *data)
{
	int i;

	if (data->argc == 1)
	{
		err_puts("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
		_unsetenv(data, data->argv[i]);

	return (0);
}

/**
 * create_env - populates env linked list
 * @data: Struct containing potential args
 *
 * Return: Always 0
 */
int create_env(data_s *data)
{
	list_s *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_to_node_end(&node, environ[i], 0);
	data->env = node;
	return (0);
}

