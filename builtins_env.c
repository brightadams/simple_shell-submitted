#include "main.h"

/**
 * shellby_env -This Prints the curr environment.
 * @args:This passes An array of arguments passed to the shell.
 * @head: A double pointer to the initial of args.
 *
 * Return: If an err_bool occurs - -1.
 *	   Otherwise - 0.
 *
 * Description:This Prints one variable per line_read in the
 *              format 'variable'='value'.
 */
int shellby_env(char **args, char __attribute__((__unused__)) **head)
{
	int ind;
	char new_line = '\n';

	if (!environ)
		return (-1);

	for (ind = 0; environ[ind]; ind++)
	{
		write(STDOUT_FILENO, environ[ind], _strlen(environ[ind]));
		write(STDOUT_FILENO, &new_line, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - This Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @head: A double pointer to the initial of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an err_bool occurs - -1.
 *         Otherwise - 0.
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **head)
{
	char **e_variable = NULL, **new_env_var, *new_val;
	size_t size;
	int ind;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_val = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_val)
		return (create_error(args, -1));
	_strcpy(new_val, args[0]);
	_strcat(new_val, "=");
	_strcat(new_val, args[1]);

	e_variable = _getenv(args[0]);
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
		return (create_error(args, -1));
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
 * shellby_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @head: A double pointer to the initial of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an err_bool occurs - -1.
 *         Otherwise - 0.
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **head)
{
	char **e_variable, **new_env_var;
	size_t size;
	int ind, index2;

	if (!args[0])
		return (create_error(args, -1));
	e_variable = _getenv(args[0]);
	if (!e_variable)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_env_var = malloc(sizeof(char *) * size);
	if (!new_env_var)
		return (create_error(args, -1));

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

