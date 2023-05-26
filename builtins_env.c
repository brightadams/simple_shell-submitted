#include "main.h"

/**
 * shellby_env -This Prints the current environment.
 * @args:This passes An array of arguments passed to the shell.
 * @head: A double pointer to the initial of args.
 *
 * Return: If an err_bool occurs - -1.
 *	   Otherwise - 0.
 *
 * Description:This Prints one variable per line in the
 *              format 'variable'='value'.
 */
int shellby_env(char **args, char __attribute__((__unused__)) **head)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
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
	char **env_var = NULL, **new_environ, *value_new;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	value_new = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!value_new)
		return (create_error(args, -1));
	_strcpy(value_new, args[0]);
	_strcat(value_new, "=");
	_strcat(value_new, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = value_new;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(value_new);
		return (create_error(args, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = value_new;
	environ[index + 1] = NULL;

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
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(args, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}

