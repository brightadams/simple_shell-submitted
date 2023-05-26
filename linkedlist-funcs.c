#include "main.h"

/**
 * append_alias - Adds a node to the end of an alias_t linked list.
 * @head: A pointer to the head of the alias_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: a pointer to the new node.
 *         Otherwise - error occurs - NULL.
 *
 * Description: This function appends a new alias node with the given name and
 *              value to the end of the alias_t linked list. If an error occurs,
 *              NULL is returned. Otherwise, a pointer to the new node is returned.
 */

alias_t *append_alias(alias_t **head, char *name, char *value)
{
	alias_t *n_node = malloc(sizeof(alias_t));
	alias_t *tail;

	if (!n_node)
		return (NULL);

	n_node->next = NULL;
	n_node->name = malloc(sizeof(char) * (_str_len(name) + 1));
	if (!n_node->name)
	{
		free(n_node);
		return (NULL);
	}
	n_node->value = value;
	_copy_string(n_node->name, name);

	if (*head)
	{
		tail = *head;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = n_node;
	}
	else
		*head = n_node;

	return (n_node);
}

/**
 * node_append - appends node to linked list.
 * @head: points to the head of the list_t list.
 * @dir: The directory path name for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 *
 * Description: This function appends a new node with the given directory path name
 *              to the end of the list_t linked list. If an error occurs, NULL is returned.
 *              Otherwise, a pointer to the new node is returned.
 */

list_t *node_append(list_t **head, char *dir)
{
	list_t *n_node = malloc(sizeof(list_t));
	list_t *tail;

	if (!n_node)
		return (NULL);

	n_node->dir = dir;
	n_node->next = NULL;

	if (*head)
	{
		tail = *head;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = n_node;
	}
	else
		*head = n_node;

	return (n_node);
}

/**
 * free_alias - Frees an alias_t linked list.
 * @head: The head of the alias_t list.
 *
 * Description: This function frees the memory allocated for an alias_t linked list.
 *              It starts from the head node and iterates through the list, freeing
 *              each node and its associated memory. The head pointer is set to NULL
 *              after all nodes have been freed.
 */

void free_alias(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * free_list - Frees a list_t linked list.
 * @head: points to the head of the list_t list.
 *
 * Description: This function frees the memory allocated for a list_t linked list.
 *              It starts from the head node and iterates through the list, freeing
 *              each node and its associated memory. The head pointer is set to NULL
 *              after all nodes have been freed.
 */

void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}

