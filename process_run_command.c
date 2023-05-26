#include "main.h"

/**
 * open_error_mess - Prints an error message indicating that the file cannot be opened
 *             when it doesn't exist or lacks proper permissions.
 * @file_path: Path to the supposed file.
 *
 * Return: The exit code 127.
 */


int open_error_mess(char *file_path)
{
	char *err_bool, *history_string;
	int leng;

	history_string = stringify(hist);
	if (!history_string)
		return (127);

	leng = _str_len(name) + _str_len(history_string) + _str_len(file_path) + 16;
	err_bool = malloc(sizeof(char) * (leng + 1));
	if (!err_bool)
	{
		free(history_string);
		return (127);
	}

	_copy_string(err_bool, name);
	_string_concat(err_bool, ": ");
	_string_concat(err_bool, history_string);
	_string_concat(err_bool, ": Can't open ");
	_string_concat(err_bool, file_path);
	_string_concat(err_bool, "\n");

	free(history_string);
	write(STDERR_FILENO, err_bool, leng);
	free(err_bool);
	return (127);
}

/**
 * file_executor - Takes a file path and attempts to run the commands
 *                      stored within the file.
 *
 * @file_path: Path to the file containing the commands.
 * @exe_ret: Return value of the last executed command.
 *
 * Description: This function reads the specified file and executes the commands
 * stored within it. Each command is executed in the order they appear
 * in the file. If the file cannot be opened or accessed due to
 * insufficient permissions, a "can't open" error message is displayed.
 *
 * Return: If the file cannot be opened - 127.
 *         If memory allocation fails - -1.
 *         Otherwise, the return value of the last executed command.
 */


int file_executor(char *file_path, int *exe_ret)
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
		*exe_ret = open_error_mess(file_path);
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
		line_read = re_allocate(line_read, size_of_old_line, size_of_line);
		_string_concat(line_read, buffer);
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
	_line_input(&line_read, size_of_line);
	args = _strtok(line_read, " ");
	free(line_read);
	if (!args)
		return (0);
	if (args_checker(args) != 0)
	{
		*exe_ret = 2;
		remove_args_from_memory(args, args);
		return (*exe_ret);
	}
	head = args;

	for (z = 0; args[z]; z++)
	{
		if (compare_n_string(args[z], ";", 1) == 0)
		{
			free(args[z]);
			args[z] = NULL;
			y = _args_call(args, head, exe_ret);
			args = &args[++z];
			z = 0;
		}
	}

	y = _args_call(args, head, exe_ret);

	free(head);
	return (y);
}
