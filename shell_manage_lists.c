#include "shell.h"

/**
 * add_to_node_start - prepends a node to the list
 * @head: pointer addr to head node
 * @str: str param
 * @num: index referenced in history
 * Return: list size
 */
list_s *add_to_node_start(list_s **head, const char *str, int num)
{
	list_s *new_head;

	new_head = malloc(sizeof(list_s));
	if (!head)
		return (NULL);
	if (!new_head)
		return (NULL);

	_memset((void *)new_head, 0, sizeof(list_s));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_to_node_end - append node to the end of list
 * @head: pointer addr to head node
 * @str: str param
 * @num: node index used by history
 * Return: list len
 */
list_s *add_to_node_end(list_s **head, const char *str, int num)
{
	list_s *new_node;
	list_s *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_s));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_s));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * prnt_list_str_elem - prints str element of a list_s linked list only
 * @h: first node's pointer address param
 * Return: list len
 */
size_t prnt_list_str_elem(const list_s *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * del_node_at_idx - deletes node at given index
 * @head: address of first node's pointer param
 * @index: index of node to delete
 * Return: On success - 1, on failure - 0
 */
int del_node_at_idx(list_s **head, unsigned int index)
{
	list_s *curr_node;
	list_s *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
	{
		return (0);
	}
	if (!index)
	{
		curr_node = *head;
		*head = (*head)->next;
		free(curr_node->str);
		free(curr_node);
		return (1);
	}
	curr_node = *head;
	while (curr_node)
	{
		if (i == index)
		{
			prev_node->next = curr_node->next;
			free(curr_node->str);
			free(curr_node);
			return (1);
		}
		i++;
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of list
 * @head_ptr: ptr addr to list head
 * Return: void
 */
void free_list(list_s **head_ptr)
{
	list_s *node;
	list_s *next_node;
	list_s *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
