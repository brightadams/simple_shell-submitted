#include "main.h"

/**
 * error_126 - function that Creates an err_bool
 * message for permission denied failures
 * @args: array of arguments passed
 *
 * Return: Error string
 */
char *error_126(char **args)
{
	char *err_bool, *history_string;
	int leng;

	history_string = _itoa(hist);
	if (!history_string)
		return (NULL);

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
	_strcat(err_bool, ": ");
	_strcat(err_bool, args[0]);
	_strcat(err_bool, ": Permission denied\n");

	free(history_string);
	return (err_bool);
}

/**
 * error_127 - function that creates an err_bool
 * message for command not found failures
 * @args: array of arguments passed
 *
 * Return: err_bool string
 */
char *error_127(char **args)
{
	char *err_bool, *history_string;
	int leng;

	history_string = _itoa(hist);
	if (!history_string)
		return (NULL);

	leng = _strlen(name) + _strlen(history_string) + _strlen(args[0]) + 16;
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
	_strcat(err_bool, ": not found\n");

	free(history_string);
	return (err_bool);
}
