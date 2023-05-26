#include "main.h"

/**
 * _curr_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @head: A double pointer to the initial element of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 *
 * Description: Prints each variable in the format 'variable'='value'.
 */

int _curr_env(char **args, char __attribute__((__unused__)) **head)
{
	int ind;
	char new_line = '\n';

	if (!environ)
		return (-1);

	for (ind = 0; environ[ind]; ind++)
	{
		write(STDOUT_FILENO, environ[ind], _str_len(environ[ind]));
		write(STDOUT_FILENO, &new_line, 1);
	}

	(void)args;
	return (0);
}

/**
 * _modify_env - Modifies or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @head: A double pointer to the initial element of args.
 *
 * Description: The function takes the name of a new or existing PATH variable
 *              from args[1], and assigns the value specified in args[2] to it.
 *
 * Return: If an error occurs, the function returns -1.
 *         Otherwise, it returns 0.
 */

int _modify_env(char **args, char __attribute__((__unused__)) **head)
{
	char **e_variable = NULL, **new_env_var, *new_val;
	size_t size;
	int ind;

	if (!args[0] || !args[1])
		return (error_creator(args, -1));

	new_val = malloc(_str_len(args[0]) + 1 + _str_len(args[1]) + 1);
	if (!new_val)
		return (error_creator(args, -1));
	_copy_string(new_val, args[0]);
	_string_concat(new_val, "=");
	_string_concat(new_val, args[1]);

	e_variable = _env_get(args[0]);
	if (e_variable)
	{
		free(*e_variable);
		*e_variable = new_val;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_env_var = malloc(sizeof(char *) * (size + 2));
	if (!new_env_var)
	{
		free(new_val);
		return (error_creator(args, -1));
	}

	for (ind = 0; environ[ind]; ind++)
		new_env_var[ind] = environ[ind];

	free(environ);
	environ = new_env_var;
	environ[ind] = new_val;
	environ[ind + 1] = NULL;

	return (0);
}

/**
 * _remove_env - Removes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @head: A double pointer to the initial element of args.
 *
 * Description: The function deletes the specified PATH variable from the environment.
 *              The variable to remove is specified in args[1].
 *
 * Return: If an error occurs, the function returns -1.
 *         Otherwise, it returns 0.
 */

int _remove_env(char **args, char __attribute__((__unused__)) **head)
{
	char **e_variable, **new_env_var;
	size_t size;
	int ind, index2;

	if (!args[0])
		return (error_creator(args, -1));
	e_variable = _env_get(args[0]);
	if (!e_variable)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_env_var = malloc(sizeof(char *) * size);
	if (!new_env_var)
		return (error_creator(args, -1));

	for (ind = 0, index2 = 0; environ[ind]; ind++)
	{
		if (*e_variable == environ[ind])
		{
			free(*e_variable);
			continue;
		}
		new_env_var[index2] = environ[ind];
		index2++;
	}
	free(environ);
	environ = new_env_var;
	environ[size - 1] = NULL;

	return (0);
}

