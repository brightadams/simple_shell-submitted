#include "main.h"

/**
 * sig_handler - Prints a new prompt upon receiving a signal.
 * @sig: The signal received.
 *
 * Description: This function is a signal handler that is called when a signal is received.
 *              It prints a new prompt to indicate that a signal has been received.
 *
 * Return: void.
 */

void sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute - Command gets executed in a child process.
 * @args: args array
 * @head: Double pointer to the first leters of the arguments.
 *
 * Return: An error code if an error occurs, or
 * the exit value of the last executed command if otherwise.
 *
 * Description: This function runs a command in a separate child process.
 *              It takes an array of arguments and executes the command using the execvp system call.
 *              The function returns the exit value of the command if it is executed successfully.
 *              If an error occurs during execution, it returns an error code.
 */

int execute(char **args, char **head)
{
	pid_t child_pid;
	int status, flag = 0, y = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = command_path(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			y = (error_creator(args, 126));
		else
			y = (error_creator(args, 127));
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
				y = (error_creator(args, 126));
			_env_free();
			remove_args_from_memory(args, head);
			free_alias(aliases);
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
 * main - The main function that runs a simple UNIX command interpreter.
 * @argc: number of arguments provided.
 * @argv: Array of pointers to the arguments passed.
 *
 * Return: The exit value of the last executed command.
 *
 * Description: This is the entry point of the program and serves as the main loop of the shell.
 *              It reads user input, parses it into commands, and executes them accordingly.
 *              The function returns the exit value of the last executed command.
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
	environ = dup_env();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		y = file_executor(argv[1], exe_ret);
		_env_free();
		free_alias(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (y != END_OF_FILE && y != EXIT)
			y = _args_handler(exe_ret);
		_env_free();
		free_alias(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompter, 2);
		y = _args_handler(exe_ret);
		if (y == END_OF_FILE || y == EXIT)
		{
			if (y == END_OF_FILE)
				write(STDOUT_FILENO, n_line, 1);
			_env_free();
			free_alias(aliases);
			exit(*exe_ret);
		}
	}

	_env_free();
	free_alias(aliases);
	return (*exe_ret);
}
