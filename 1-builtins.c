#include "main.h"

/**
 * get_builtin -This  Matches a command with a corresponding
 * shellby builtin function
 * @command: The command to match
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args, char **head)
{
	builtin_t funcs[] = {
		{ "exit", shellby_exit },
		{ "env", shellby_env },
		{ "setenv", shellby_setenv },
		{ "unsetenv", shellby_unsetenv },
		{ "cd", shellby_cd },
		{ "alias", shellby_alias },
		{ "help", shellby_help },
		{ NULL, NULL }
	};
	int z;

	for (z = 0; funcs[z].name; z++)
	{
		if (_strcmp(funcs[z].name, command) == 0)
			break;
	}
	return (funcs[z].f);
}

/**
 * shellby_exit - Causes normal process termination
 * for the shellby shell.
 * @args: An array of arguments containing the exit val.
 * @head: A double pointer to the initial of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit val is invalid - 2.
 *         O/w - exits with the given status val.
 *
 * Description: Upon returning -3, the program exits back in the main function.
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
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (numb > maxi - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, head);
	free_env();
	free_alias_list(aliases);
	exit(numb);
}

/**
 * shellby_cd - Changes the current directory of the shellby process.
 * @args:This takes an array of arguments.
 * @head: A double pointer to the initial of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an err_bool occurs - -1.
 *         Otherwise - 0.
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
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(pass_old);
				return (create_error(args, 2));
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
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pass = getcwd(pass, 0);
	if (!pass)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = pass_old;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pass;
	if (shellby_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pass, _strlen(pass));
		write(STDOUT_FILENO, n_line, 1);
	}
	free(pass_old);
	free(pass);
	free(dir_info);
	return (0);
}

/**
 * shellby_help - Displays information about shellby builtin commands.
 * @args: An array of arguments.
 * @head: A pointer to the initial of args.
 *
 * Return: If an err_bool occurs - -1.
 *         Otherwise - 0.
 */
int shellby_help(char **args, char __attribute__((__unused__)) **head)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}

