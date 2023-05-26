#include "main.h"

/**
 * _perm_errors - Generates an error message for permission denied failures.
 * @args: arguments array
 *
 * Return: error message of string
 */

char *_perm_errors(char **args)
{
	char *err_bool, *history_string;
	int leng;

	history_string = stringify(hist);
	if (!history_string)
		return (NULL);

	leng = _str_len(name) + _str_len(history_string) + _str_len(args[0]) + 24;
	err_bool = malloc(sizeof(char) * (leng + 1));
	if (!err_bool)
	{
		free(history_string);
		return (NULL);
	}

	_copy_string(err_bool, name);
	_string_concat(err_bool, ": ");
	_string_concat(err_bool, history_string);
	_string_concat(err_bool, ": ");
	_string_concat(err_bool, args[0]);
	_string_concat(err_bool, ": Permission denied\n");

	free(history_string);
	return (err_bool);
}

/**
 * not_found_errors - Generates an error message for command not found failures.
 * @args: arguments array
 *
 * Return: error message of string
 */

char *not_found_errors(char **args)
{
	char *err_bool, *history_string;
	int leng;

	history_string = stringify(hist);
	if (!history_string)
		return (NULL);

	leng = _str_len(name) + _str_len(history_string) + _str_len(args[0]) + 16;
	err_bool = malloc(sizeof(char) * (leng + 1));
	if (!err_bool)
	{
		free(history_string);
		return (NULL);
	}

	_copy_string(err_bool, name);
	_string_concat(err_bool, ": ");
	_string_concat(err_bool, history_string);
	_string_concat(err_bool, ": ");
	_string_concat(err_bool, args[0]);
	_string_concat(err_bool, ": not found\n");

	free(history_string);
	return (err_bool);
}
