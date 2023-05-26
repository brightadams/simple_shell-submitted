#include "main.h"
/**
 * get_location - funcion that locates a command in the PATH
 * @command: command to be located
 *
 * Return: NULL if an err_bool occurs or the command cannot be located
 * or the full pathname of the command if otherwise
 */
char *get_location(char *command)
{
	char **path, *tem;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		tem = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!tem)
			return (NULL);

		_strcpy(tem, dirs->dir);
		_strcat(tem, "/");
		_strcat(tem, command);

		if (stat(tem, &st) == 0)
		{
			free_list(head);
			return (tem);
		}

		dirs = dirs->next;
		free(tem);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_path_dir - function that copies path but also replaces
 * leading,sandwiched,trailing colons (:) with current working directory
 * @path: directories lis of colon-separated
 *
 * Return: copy of path with any leading,sandwiched,trailing
 * colons replacedwith the current working directory
 */
char *fill_path_dir(char *path)
{
	int z, len = 0;
	char *path_copy, *pass;

	pass = *(_getenv("PWD")) + 4;
	for (z = 0; path[z]; z++)
	{
		if (path[z] == ':')
		{
			if (path[z + 1] == ':' || z == 0 || path[z + 1] == '\0')
				len += _strlen(pass) + 1;
			else
				len++;
		}
		else
			len++;
	}
	path_copy = malloc(sizeof(char) * (len + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (z = 0; path[z]; z++)
	{
		if (path[z] == ':')
		{
			if (z == 0)
			{
				_strcat(path_copy, pass);
				_strcat(path_copy, ":");
			}
			else if (path[z + 1] == ':' || path[z + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pass);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[z], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - function that tokenizes a colon-separated
 * list of directories into a list_s linked list
 * @path: directories list of  colon-separated
 *
 * Return: pointer to initialized linked list
 */
list_t *get_path_dir(char *path)
{
	int index;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
