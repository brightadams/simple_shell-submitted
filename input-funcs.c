#include "main.h"

/**
 * _args_get - Reads a command from standard input and stores it in a buffer.
 * @line_read: The buffer to store the command.
 * @exe_ret: The return value of the executed tail command.
 *
 * Return: NULL if an error occurs, or a pointer to the stored command otherwise.
 */

char *_args_get(char *line_read, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompter = "$ ";

	if (line_read)
		free(line_read);

	read = line_getter(&line_read, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompter, 2);
		return (_args_get(line_read, exe_ret));
	}

	line_read[read - 1] = '\0';
	variable_replacement(&line_read, exe_ret);
	_line_input(&line_read, read);

	return (line_read);
}

/**
 * _args_call - Separates operators from commands in an array of arguments.
 * @args: The array of arguments.
 * @head: Double pointer to the initial element of args.
 * @exe_ret: The return value of the parent process tail executed command.
 *
 * Return: The return value of the executed tail command.
 */

int _args_call(char **args, char **head, int *exe_ret)
{
	int y, ind;

	if (!args[0])
		return (*exe_ret);
	for (ind = 0; args[ind]; ind++)
	{
		if (compare_n_string(args[ind], "||", 2) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			args = replace_aliases(args);
			y = exec_args(args, head, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++ind];
				ind = 0;
			}
			else
			{
				for (ind++; args[ind]; ind++)
					free(args[ind]);
				return (y);
			}
		}
		else if (compare_n_string(args[ind], "&&", 2) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			args = replace_aliases(args);
			y = exec_args(args, head, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++ind];
				ind = 0;
			}
			else
			{
				for (ind++; args[ind]; ind++)
					free(args[ind]);
				return (y);
			}
		}
	}
	args = replace_aliases(args);
	y = exec_args(args, head, exe_ret);
	return (y);
}

/**
 * exec_args - Executes a command specified by an array of arguments.
 * @args: The array of arguments.
 * @head: Double pointer to the initial element of args.
 * @exe_ret: The return value of the parent process tail executed command.
 *
 * Return: The return value of the executed command.
 */

int exec_args(char **args, char **head, int *exe_ret)
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
 * _args_handler - Processes, calls, and executes a command.
 * @exe_ret: The return value of the parent process tail executed command.
 *
 * Return: END_OF_FILE (-2) if an end-of-file is encountered,
 *         -1 if the input cannot be tokenized,
 *         or the exit value of the executed command otherwise.
 */

int _args_handler(int *exe_ret)
{
	int y = 0, ind;
	char **args, *line_read = NULL, **head;

	line_read = _args_get(line_read, exe_ret);
	if (!line_read)
		return (END_OF_FILE);

	args = _strtok(line_read, " ");
	free(line_read);
	if (!args)
		return (y);
	if (args_checker(args) != 0)
	{
		*exe_ret = 2;
		remove_args_from_memory(args, args);
		return (*exe_ret);
	}
	head = args;

	for (ind = 0; args[ind]; ind++)
	{
		if (compare_n_string(args[ind], ";", 1) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			y = _args_call(args, head, exe_ret);
			args = &args[++ind];
			ind = 0;
		}
	}
	if (args)
		y = _args_call(args, head, exe_ret);

	free(head);
	return (y);
}

/**
 * args_checker - Verifies if there are any leading ';', ';;', '&&', or '||' tokens.
 * @args: tokenized commands and arguments of the 2D pointer
 *
 * Return: 2 if a ';', '&&', or '||' token is found at an invalid position,
 *         or 0 otherwise.
 */

int args_checker(char **args)
{
	size_t z;
	char *current, *nex;

	for (z = 0; args[z]; z++)
	{
		current = args[z];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (z == 0 || current[1] == ';')
				return (error_creator(&args[z], 2));
			nex = args[z + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (error_creator(&args[z + 1], 2));
		}
	}
	return (0);
}
