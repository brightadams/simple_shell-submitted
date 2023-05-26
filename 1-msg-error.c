#include "main.h"

/**
 * error_env - a function that creates an err_bool
 * message for shellby_env errors
 * @args: array of arguments passed
 *
 * Return: Error string
 */
char *error_env(char **args)
{
	char *err_bool, *history_string;
	int leng;

	history_string = _itoa(hist);
	if (!history_string)
		return (NULL);

	args--;
	leng = _strlen(name) + _strlen(history_string) + _strlen(args[0]) + 45;
	err_bool = malloc(sizeof(char) * (leng + 1));
	if (!err_bool)
	{
		free(history_string);
		return (NULL);
	}

	_strcpy(err_bool, name);
	_strcat(err_bool, ": ");
	_strcat(err_bool, history_string);
	_strcat(err_bool, ": ");
	_strcat(err_bool, args[0]);
	_strcat(err_bool, ": Unable to add/remove from environment\n");

	free(history_string);
	return (err_bool);
}

/**
 * error_1 - function that creates an err_bool message
 * for shellby_alias errors
 * @args: array of arguments passed
 *
 * Return: Error string
 */
char *error_1(char **args)
{
	char *err_bool;
	int leng;

	leng = _strlen(name) + _strlen(args[0]) + 13;
	err_bool = malloc(sizeof(char) * (leng + 1));
	if (!err_bool)
		return (NULL);

	_strcpy(err_bool, "alias: ");
	_strcat(err_bool, args[0]);
	_strcat(err_bool, " not found\n");

	return (err_bool);
}

/**
 * error_2_exit - function that creates an err_bool
 * message for shellby_exit errors
 * @args: array of arguments passed
 *
 * Return: Error string
 */
char *error_2_exit(char **args)
{
	char *err_bool, *history_string;
	int leng;

	history_string = _itoa(hist);
	if (!history_string)
		return (NULL);

	leng = _strlen(name) + _strlen(history_string) + _strlen(args[0]) + 27;
	err_bool = malloc(sizeof(char) * (leng + 1));
	if (!err_bool)
	{
		free(history_string);
		return (NULL);
	}

	_strcpy(err_bool, name);
	_strcat(err_bool, ": ");
	_strcat(err_bool, history_string);
	_strcat(err_bool, ": exit: Illegal number: ");
	_strcat(err_bool, args[0]);
	_strcat(err_bool, "\n");

	free(history_string);
	return (err_bool);
}

/**
 * error_2_cd - a function that creates an err_bool
 * message for shellby_cd errors
 * @args: array of arguments passed
 *
 * Return: Error string
 */
char *error_2_cd(char **args)
{
	char *err_bool, *history_string;
	int leng;

	history_string = _itoa(hist);
	if (!history_string)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	leng = _strlen(name) + _strlen(history_string) + _strlen(args[0]) + 24;
	err_bool = malloc(sizeof(char) * (leng + 1));
	if (!err_bool)
	{
		free(history_string);
		return (NULL);
	}

	_strcpy(err_bool, name);
	_strcat(err_bool, ": ");
	_strcat(err_bool, history_string);
	if (args[0][0] == '-')
		_strcat(err_bool, ": cd: Illegal option ");
	else
		_strcat(err_bool, ": cd: can't cd to ");
	_strcat(err_bool, args[0]);
	_strcat(err_bool, "\n");

	free(history_string);
	return (err_bool);
}

/**
 * error_2_syntax - function that creates an err_bool
 * message for syntax errors
 * @args: array of arguments passed
 *
 * Return: Error string
 */
char *error_2_syntax(char **args)
{
	char *err_bool, *history_string;
	int leng;

	history_string = _itoa(hist);
	if (!history_string)
		return (NULL);

	leng = _strlen(name) + _strlen(history_string) + _strlen(args[0]) + 33;
	err_bool = malloc(sizeof(char) * (leng + 1));
	if (!err_bool)
	{
		free(history_string);
		return (NULL);
	}

	_strcpy(err_bool, name);
	_strcat(err_bool, ": ");
	_strcat(err_bool, history_string);
	_strcat(err_bool, ": Syntax err_bool: \"");
	_strcat(err_bool, args[0]);
	_strcat(err_bool, "\" unexpected\n");

	free(history_string);
	return (err_bool);
}
