#include "main.h"

/**
 * get_args - function that gets a command from standard input
 * @line: buffer to store the command
 * @exe_ret: return value of tail command executed
 *
 * Return: NULL if an err_bool occurs or, a pointer
 * to the stored command if otherwise
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_args - function that partitions operators from commands
 * @args: array of arguments
 * @head: double pointer to initial of args
 * @exe_ret: return value of parent process tail executed command
 *
 * Return: return value of the tail executed command
 */
int call_args(char **args, char **head, int *exe_ret)
{
	int y, index;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			y = run_args(args, head, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (y);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			y = run_args(args, head, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (y);
			}
		}
	}
	args = replace_aliases(args);
	y = run_args(args, head, exe_ret);
	return (y);
}

/**
 * run_args - function that calls the execution of a command
 * @args: array of arguments
 * @head: double pointer to initial of args
 * @exe_ret: return value of parent process tail executed command
 *
 * Return: return value of the tail executed command
 */
int run_args(char **args, char **head, int *exe_ret)
{
	int y, z;
	int (*builtin)(char **args, char **head);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		y = builtin(args + 1, head);
		if (y != EXIT)
			*exe_ret = y;
	}
	else
	{
		*exe_ret = execute(args, head);
		y = *exe_ret;
	}

	hist++;

	for (z = 0; args[z]; z++)
		free(args[z]);

	return (y);
}

/**
 * handle_args - function that gets, calls, and
 * runs the execution of command
 * @exe_ret: return value of the parent process
 * tail executed command
 *
 * Return: END_OF_FILE (-2) if an end-of-file is read
 * and -1 If the input cannot be tokenized or the
 * exit value of the tail executed command if otherwise
 */
int handle_args(int *exe_ret)
{
	int y = 0, index;
	char **args, *line = NULL, **head;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (y);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	head = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			y = call_args(args, head, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		y = call_args(args, head, exe_ret);

	free(head);
	return (y);
}

/**
 * check_args - function that checks if there are
 * any leading ';', ';;', '&&', or '||'
 * @args: 2D pointer to tokenized commands and arguments
 *
 * Return: 2 if a ';', '&&', or '||' is placed at an
 * invalid position or  0 if Otherwise
 */
int check_args(char **args)
{
	size_t z;
	char *cur, *nex;

	for (z = 0; args[z]; z++)
	{
		cur = args[z];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (z == 0 || cur[1] == ';')
				return (create_error(&args[z], 2));
			nex = args[z + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[z + 1], 2));
		}
	}
	return (0);
}
