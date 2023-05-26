#include "main.h"

/**
 * get_builtin - Matches a command with a corresponding shellby built-in function.
 *
 * @command: The command to be matched.
 *
 * This function takes a command as input and matches it with a corresponding
 * built-in function in the shellby shell. It returns a function pointer to the
 * matched built-in function.
 *
 * Return: A function pointer to the corresponding built-in function,
 *         or NULL if no matching built-in function is found.
 */


int (*get_builtin(char *command))(char **args, char **head)
{
	builtin_t funcs[] = {
		{ "exit", shellby_exit },
		{ "env", _curr_env },
		{ "setenv", _modify_env },
		{ "unsetenv", _remove_env },
		{ "cd", shellby_cd },
		{ "alias", alias_for_shellby },
		{ "help", shellby_help },
		{ NULL, NULL }
	};
	int z;

	for (z = 0; funcs[z].name; z++)
	{
		if (compare_string(funcs[z].name, command) == 0)
			break;
	}
	return (funcs[z].f);
}

/**
 * shellby_exit - Terminates the shellby shell process.
 * @args: An array of arguments containing the exit value.
 * @head: A double pointer to the start of the args array.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         Otherwise, exits with the specified status value.
 *
 * Description: If no arguments are provided, the function returns -3
 *              to indicate that the shell process should terminate
 *              back in the main function. If an invalid exit value is
 *              provided, the function returns 2. Otherwise, the shell
 *              process is terminated with the given status value.
 */

int shellby_exit(char **args, char **head)
{
	int z, intLength = 10;
	unsigned int numb = 0, maxi = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			z = 1;
			intLength++;
		}
		for (; args[0][z]; z++)
		{
			if (z <= intLength && args[0][z] >= '0' && args[0][z] <= '9')
				numb = (numb * 10) + (args[0][z] - '0');
			else
				return (error_creator(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (numb > maxi - 1)
		return (error_creator(--args, 2));
	args -= 1;
	remove_args_from_memory(args, head);
	_env_free();
	free_alias(aliases);
	exit(numb);
}

/**
 * shellby_cd - Changes the current directory of the shellby process.
 * @args: An array of arguments containing the directory path.
 * @head: A double pointer to the start of the args array.
 *
 * Return: If the specified directory is not valid - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 *
 * Description: This function is responsible for changing the current
 *              directory of the shellby process. If the specified
 *              directory is not a valid directory path, it returns 2.
 *              If any error occurs during the directory change, it
 *              returns -1. Otherwise, it returns 0 to indicate a
 *              successful directory change.
 */

int shellby_cd(char **args, char __attribute__((__unused__)) **head)
{
	char **dir_info, *n_line = "\n";
	char *pass_old = NULL, *pass = NULL;
	struct stat dir;

	pass_old = getcwd(pass_old, 0);
	if (!pass_old)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || compare_string(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_env_get("OLDPWD") != NULL)
					(chdir(*_env_get("OLDPWD") + 7));
			}
			else
			{
				free(pass_old);
				return (error_creator(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(pass_old);
				return (error_creator(args, 2));
			}
		}
	}
	else
	{
		if (_env_get("HOME") != NULL)
			chdir(*(_env_get("HOME")) + 5);
	}

	pass = getcwd(pass, 0);
	if (!pass)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = pass_old;
	if (_modify_env(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pass;
	if (_modify_env(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pass, _str_len(pass));
		write(STDOUT_FILENO, n_line, 1);
	}
	free(pass_old);
	free(pass);
	free(dir_info);
	return (0);
}

/**
 * shellby_help - Displays information about shellby's built-in commands.
 * @args: An array of arguments.
 * @head: A pointer to the start of the args array.
 *
 * Return: Returns 0 on successful execution, -1 on error.
 *
 * Description: This function provides assistance and usage instructions for
 *              shellby's built-in commands. It displays information about
 *              each command to help users understand their functionality.
 *              In case of any errors during execution, it returns -1, otherwise
 *              it returns 0 to indicate successful completion.
 */

int shellby_help(char **args, char __attribute__((__unused__)) **head)
{
	if (!args[0])
		show_all_commands();
	else if (compare_string(args[0], "alias") == 0)
		show_help_alias();
	else if (compare_string(args[0], "cd") == 0)
		show_help_cd();
	else if (compare_string(args[0], "exit") == 0)
		exit_help();
	else if (compare_string(args[0], "env") == 0)
		_env_help();
	else if (compare_string(args[0], "setenv") == 0)
		_setenv_help();
	else if (compare_string(args[0], "unsetenv") == 0)
		_unsetenv_helper();
	else if (compare_string(args[0], "help") == 0)
		help_helper();
	else
		write(STDERR_FILENO, name, _str_len(name));

	return (0);
}

