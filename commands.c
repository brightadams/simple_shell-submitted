#include "main.h"
/**
 * command_path - Finds the location of a command in the PATH.
 * @command: The command to locate.
 *
 * Return: NULL if an error occurs or the command cannot be found,
 *         or the full pathname of the command if it is found.
 */

char *command_path(char *command)
{
	char **pathName, *tem;
	list_t *dirs, *head;
	struct stat st;

	pathName = _env_get("PATH");
	if (!pathName || !(*pathName))
		return (NULL);

	dirs = get_dir_path(*pathName + 5);
	head = dirs;

	while (dirs)
	{
		tem = malloc(_str_len(dirs->dir) + _str_len(command) + 2);
		if (!tem)
			return (NULL);

		_copy_string(tem, dirs->dir);
		_string_concat(tem, "/");
		_string_concat(tem, command);

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
 * _fill_dirPath - Creates a copy of pathName while ensuring that any leading,
 *                 sandwiched, or trailing colons (:) are replaced with the
 *                 current working directory.
 * @pathName: A list of directories separated by colons.
 *
 * Return: A modified copy of pathName where any leading, sandwiched, or
 *         trailing colons are replaced with the current working directory.
 */

char *_fill_dirPath(char *pathName)
{
	int z, length = 0;
	char *copied_path, *pass;

	pass = *(_env_get("PWD")) + 4;
	for (z = 0; pathName[z]; z++)
	{
		if (pathName[z] == ':')
		{
			if (pathName[z + 1] == ':' || z == 0 || pathName[z + 1] == '\0')
				length += _str_len(pass) + 1;
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
				_string_concat(copied_path, pass);
				_string_concat(copied_path, ":");
			}
			else if (pathName[z + 1] == ':' || pathName[z + 1] == '\0')
			{
				_string_concat(copied_path, ":");
				_string_concat(copied_path, pass);
			}
			else
				_string_concat(copied_path, ":");
		}
		else
		{
			_string_n_concat(copied_path, &pathName[z], 1);
		}
	}
	return (copied_path);
}

/**
 * get_dir_path - Splits a colon-separated list of directories into
 *                a linked list of directories.
 * @pathName: The list of directories separated by colons.
 *
 * Return: A pointer to the initialized linked list of directories.
 */

list_t *get_dir_path(char *pathName)
{
	int ind;
	char **dirs, *copied_path;
	list_t *head = NULL;

	copied_path = _fill_dirPath(pathName);
	if (!copied_path)
		return (NULL);
	dirs = _strtok(copied_path, ":");
	free(copied_path);
	if (!dirs)
		return (NULL);

	for (ind = 0; dirs[ind]; ind++)
	{
		if (node_append(&head, dirs[ind]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
