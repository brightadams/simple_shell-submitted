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
	char **pathName, *tem;
	list_t *dirs, *head;
	struct stat st;

	pathName = _getenv("PATH");
	if (!pathName || !(*pathName))
		return (NULL);

	dirs = get_path_dir(*pathName + 5);
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
 * fill_path_dir - function that copies pathName but also replaces
 * leading,sandwiched,trailing colons (:) with curr working directory
 * @pathName: directories lis of colon-separated
 *
 * Return: copy of pathName with any leading,sandwiched,trailing
 * colons replacedwith the curr working directory
 */
char *fill_path_dir(char *pathName)
{
	int z, length = 0;
	char *copied_path, *pass;

	pass = *(_getenv("PWD")) + 4;
	for (z = 0; pathName[z]; z++)
	{
		if (pathName[z] == ':')
		{
			if (pathName[z + 1] == ':' || z == 0 || pathName[z + 1] == '\0')
				length += _strlen(pass) + 1;
			else
				length++;
		}
		else
			length++;
	}
	copied_path = malloc(sizeof(char) * (length + 1));
	if (!copied_path)
		return (NULL);
	copied_path[0] = '\0';
	for (z = 0; pathName[z]; z++)
	{
		if (pathName[z] == ':')
		{
			if (z == 0)
			{
				_strcat(copied_path, pass);
				_strcat(copied_path, ":");
			}
			else if (pathName[z + 1] == ':' || pathName[z + 1] == '\0')
			{
				_strcat(copied_path, ":");
				_strcat(copied_path, pass);
			}
			else
				_strcat(copied_path, ":");
		}
		else
		{
			_strncat(copied_path, &pathName[z], 1);
		}
	}
	return (copied_path);
}

/**
 * get_path_dir - function that tokenizes a colon-separated
 * list of directories into a list_s linked list
 * @pathName: directories list of  colon-separated
 *
 * Return: pointer to initialized linked list
 */
list_t *get_path_dir(char *pathName)
{
	int ind;
	char **dirs, *copied_path;
	list_t *head = NULL;

	copied_path = fill_path_dir(pathName);
	if (!copied_path)
		return (NULL);
	dirs = _strtok(copied_path, ":");
	free(copied_path);
	if (!dirs)
		return (NULL);

	for (ind = 0; dirs[ind]; ind++)
	{
		if (add_node_end(&head, dirs[ind]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
