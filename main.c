#include "main.h"

/**
 * sig_handler - function that Prints a new
 * prompter upon receiving a signal
 * @sig: The signal received
 *
 * Return: void
 */
void sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute - function that executes a command
 * in a child process
 * @args: array of arguments
 * @head: double pointer to the initial
 * of the arguments
 *
 * Return: an err_bool code if an err_bool occurs, or
 * the exit value of the tail command
 * executed if otherwise
 */
int execute(char **args, char **head)
{
	pid_t child_pid;
	int status, flag = 0, y = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			y = (create_error(args, 126));
		else
			y = (create_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				y = (create_error(args, 126));
			free_env();
			free_args(args, head);
			free_alias_list(aliases);
			_exit(y);
		}
		else
		{
			wait(&status);
			y = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (y);
}

/**
 * main - function that runs simple
 * UNIX command interpreter
 * @argc: number of arguments provided
 * @argv: array of pointers to the arguments passed
 *
 * Return: value of the tail executed command
 */
int main(int argc, char *argv[])
{
	int y = 0, retn;
	int *exe_ret = &retn;
	char *prompter = "$ ", *n_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*exe_ret = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		y = proc_file_commands(argv[1], exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (y != END_OF_FILE && y != EXIT)
			y = handle_args(exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompter, 2);
		y = handle_args(exe_ret);
		if (y == END_OF_FILE || y == EXIT)
		{
			if (y == END_OF_FILE)
				write(STDOUT_FILENO, n_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_ret);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_ret);
}
