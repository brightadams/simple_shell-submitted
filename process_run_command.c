#include "main.h"

/**
 * cant_open - when the file doesn't exist or lacks proper permissions, print
 * a cant open err_bool.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *err_bool, *history_string;
	int leng;

	history_string = _itoa(hist);
	if (!history_string)
		return (127);

	leng = _strlen(name) + _strlen(history_string) + _strlen(file_path) + 16;
	err_bool = malloc(sizeof(char) * (leng + 1));
	if (!err_bool)
	{
		free(history_string);
		return (127);
	}

	_strcpy(err_bool, name);
	_strcat(err_bool, ": ");
	_strcat(err_bool, history_string);
	_strcat(err_bool, ": Can't open ");
	_strcat(err_bool, file_path);
	_strcat(err_bool, "\n");

	free(history_string);
	write(STDERR_FILENO, err_bool, leng);
	free(err_bool);
	return (127);
}

/**
 * proc_file_commands -This Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the tail executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the tail command ran.
 */
int proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, z;
	unsigned int size_of_line = 0;
	unsigned int size_of_old_line = 120;
	char *line_read, **args, **head;
	char buffer[120];
	int y;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line_read = malloc(sizeof(char) * size_of_old_line);
	if (!line_read)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && size_of_line == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		size_of_line += b_read;
		line_read = _realloc(line_read, size_of_old_line, size_of_line);
		_strcat(line_read, buffer);
		size_of_old_line = size_of_line;
	} while (b_read);
	for (z = 0; line_read[z] == '\n'; z++)
		line_read[z] = ' ';
	for (; z < size_of_line; z++)
	{
		if (line_read[z] == '\n')
		{
			line_read[z] = ';';
			for (z += 1; z < size_of_line && line_read[z] == '\n'; z++)
				line_read[z] = ' ';
		}
	}
	variable_replacement(&line_read, exe_ret);
	handle_line(&line_read, size_of_line);
	args = _strtok(line_read, " ");
	free(line_read);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	head = args;

	for (z = 0; args[z]; z++)
	{
		if (_strncmp(args[z], ";", 1) == 0)
		{
			free(args[z]);
			args[z] = NULL;
			y = call_args(args, head, exe_ret);
			args = &args[++z];
			z = 0;
		}
	}

	y = call_args(args, head, exe_ret);

	free(head);
	return (y);
}
