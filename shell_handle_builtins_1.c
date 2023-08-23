#include "shell.h"

/**
 * unset_alias - sets alias to string
 * @data: struct param
 * @str: the string alias
 * Return: 1 on error, 0 on success
 */
int unset_alias(data_s *data, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);

	c = *p;
	*p = 0;
	ret = del_node_at_idx(&(data->alias),
			fetch_node_idx(data->alias, node_start_elem(data->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets the provided alias to string
 * @data: struct param
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(data_s *data, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(data, str));

	unset_alias(data, str);
	return (add_to_node_end(&(data->alias), str, 0) == NULL);
}

/**
 * print_alias - prints the provided alias string
 * @node: the alias param
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_s *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * change_alias - replaces aliases in the tokenized string
 * @data: the struct param
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_alias(data_s *data)
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
 * handle_alias - mimics the alias(man alias) builtin
 * @data: Struct containing potential args
 *  Return: Always 0
 */
int handle_alias(data_s *data)
{
	int i = 0;
	char *p = NULL;

	list_s *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		p = _strchr(data->argv[i], '=');

		if (p)
			set_alias(data, data->argv[i]);
		else
			print_alias(node_start_elem(data->alias, data->argv[i], '='));
	}
	return (0);
}
