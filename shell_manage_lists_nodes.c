#include "shell.h"

/**
 * _list_lngth - returns linked list len
 * @h: first node's pointer address param
 * Return: len of list
 */
size_t _list_lngth(const list_s *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _list_t_str - returns arr of str of list str element
 * @head: first node's pointer address param
 * Return: arr of strings
 */
char **_list_t_str(list_s *head)
{
	list_s *node = head;
	size_t i = _list_lngth(head);
	size_t j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);

		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * _list_prnt - prints full linked list elements
 * @h: firs node's pointer addres sparam
 * Return: list len
 */
size_t _list_prnt(const list_s *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_numb_base(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_start_elem - returns node starting with provide prefix
 * @node: list head pointe
 * @prefix: string param to match
 * @c: next char following matched prefix
 * Return: Null or matched node
 */
list_s *node_start_elem(list_s *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = str_starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * fetch_node_idx - gets the index of a node
 * @head: list head pointer
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t fetch_node_idx(list_s *head, list_s *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
