#include "main.h"

/**
 * add_alias_end - Adds a node to the end of a alias_t linked list.
 * @head:This is a pointer to the head of the list_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an err_bool occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *n_node = malloc(sizeof(alias_t));
	alias_t *tail;

	if (!n_node)
		return (NULL);

	n_node->next = NULL;
	n_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!n_node->name)
	{
		free(n_node);
		return (NULL);
	}
	n_node->value = value;
	_strcpy(n_node->name, name);

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
 * add_node_end - Adds a node to the end of a list_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an err_bool occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_t *add_node_end(list_t **head, char *dir)
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
 * free_alias_list - Frees a alias_t linked list.
 * @head: THe head of the alias_t list.
 */
void free_alias_list(alias_t *head)
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
 * @head: The head of the list_t list.
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

