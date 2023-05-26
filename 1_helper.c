#include "main.h"

void free_args(char **args, char **head)
{
	size_t q;

	for (q = 0; args[q] || args[q + 1]; q++)
		free(args[q]);

	free(head);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
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
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @initial: The environmental variable to search for.
 * @leng: The len of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *initial, int leng)
{
	char **address_of_variable;
	char *sub = NULL, *tem, *varia;

	varia = malloc(leng + 1);
	if (!varia)
		return (NULL);
	varia[0] = '\0';
	_strncat(varia, initial, leng);

	address_of_variable = _getenv(varia);
	free(varia);
	if (address_of_variable)
	{
		tem = *address_of_variable;
		while (*tem != '=')
			tem++;
		tem++;
		sub = malloc(_strlen(tem) + 1);
		if (sub)
			_strcpy(sub, tem);
	}

	return (sub);
}

/**
 * variable_replacement - Handles variable sub.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the tail executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the tail executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int g, p = 0, leng;
	char *sub = NULL, *old_line = NULL, *n_line;

	old_line = *line;
	for (g = 0; old_line[g]; g++)
	{
		if (old_line[g] == '$' && old_line[g + 1] &&
				old_line[g + 1] != ' ')
		{
			if (old_line[g + 1] == '$')
			{
				sub = get_pid();
				p = g + 2;
			}
			else if (old_line[g + 1] == '?')
			{
				sub = _itoa(*exe_ret);
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
				sub = get_env_value(&old_line[g + 1], leng);
			}
			n_line = malloc(g + _strlen(sub)
					  + _strlen(&old_line[p]) + 1);
			if (!line)
				return;
			n_line[0] = '\0';
			_strncat(n_line, old_line, g);
			if (sub)
			{
				_strcat(n_line, sub);
				free(sub);
				sub = NULL;
			}
			_strcat(n_line, &old_line[p]);
			free(old_line);
			*line = n_line;
			old_line = n_line;
			g = -1;
		}
	}
}
