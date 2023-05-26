#include "main.h"

void remove_args_from_memory(char **args, char **head)
{
	size_t q;

	for (q = 0; args[q] || args[q + 1]; q++)
		free(args[q]);

	free(head);
}

/**
 * lookup_pid - obtains the current process ID.
 *
 * Return:  current process ID as a string, or NULL on failure.
 *
 * Description:
 *    This function retrieves the process ID of the current process. It does
 *    so by opening the "stat" file, which contains information about the
 *    process, and extracting the PID from the first word in the file. The
 *    function reads the PID into a buffer and replaces the space character
 *    at the end with a null byte ('\0'). If successful, it returns the PID
 *    as a string. If an error occurs, it returns NULL.
 */

char *lookup_pid(void)
{
	size_t q = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[q] != ' ')
		q++;
	buffer[q] = '\0';

	close(file);
	return (buffer);
}

/**
 * env_value - obtains the value corresponding to an environmental variable.
 * @initial: The environment variable to look for.
 * @leng: The length of the environment variable to search for.
 *
 * Return: If the variable is not found, returns an empty string.
 *         Otherwise, returns the value of the environment variable.
 *
 * Description:
 *    This function searches for an environmentvariable in the format
 *    VARIABLE=VALUE. If the variable is found, it returns the corresponding
 *    value. If the variable is not found, it returns an empty string.
 */

char *env_value(char *initial, int leng)
{
	char **address_of_variable;
	char *sub = NULL, *tem, *varia;

	varia = malloc(leng + 1);
	if (!varia)
		return (NULL);
	varia[0] = '\0';
	_string_n_concat(varia, initial, leng);

	address_of_variable = _env_get(varia);
	free(varia);
	if (address_of_variable)
	{
		tem = *address_of_variable;
		while (*tem != '=')
			tem++;
		tem++;
		sub = malloc(_str_len(tem) + 1);
		if (sub)
			_copy_string(sub, tem);
	}

	return (sub);
}

/**
 * variable_replacement - takes variable substitution.
 * @line_read: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description:
 *    This function replaces occurrences of "$$" with the current PID,
 *    "$?" with the return value of the last executed program, and
 *    environmental variables preceded by "$" with their corresponding value.
 */

void variable_replacement(char **line_read, int *exe_ret)
{
	int g, p = 0, leng;
	char *sub = NULL, *old_line = NULL, *n_line;

	old_line = *line_read;
	for (g = 0; old_line[g]; g++)
	{
		if (old_line[g] == '$' && old_line[g + 1] &&
				old_line[g + 1] != ' ')
		{
			if (old_line[g + 1] == '$')
			{
				sub = lookup_pid();
				p = g + 2;
			}
			else if (old_line[g + 1] == '?')
			{
				sub = stringify(*exe_ret);
				p = g + 2;
			}
			else if (old_line[g + 1])
			{
				/* extract the variable name to search for */
				for (p = g + 1; old_line[p] &&
						old_line[p] != '$' &&
						old_line[p] != ' '; p++)
					;
				leng = p - (g + 1);
				sub = env_value(&old_line[g + 1], leng);
			}
			n_line = malloc(g + _str_len(sub)
					  + _str_len(&old_line[p]) + 1);
			if (!line_read)
				return;
			n_line[0] = '\0';
			_string_n_concat(n_line, old_line, g);
			if (sub)
			{
				_string_concat(n_line, sub);
				free(sub);
				sub = NULL;
			}
			_string_concat(n_line, &old_line[p]);
			free(old_line);
			*line_read = n_line;
			old_line = n_line;
			g = -1;
		}
	}
}
