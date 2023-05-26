#include "main.h"

/**
 * shellby_error_env - Creates an error message for _curr_env errors.
 * @args: arguments array
 *
 * Return: error of the string
 *
 * Description: This function takes an array of arguments and generates an error
 *              message for _curr_env errors. It returns the error string.
 */

char *shellby_error_env(char **args)
{
	char *err_bool, *history_string;
	int leng;

	history_string = stringify(hist);
	if (!history_string)
		return (NULL);

	args--;
	leng = _str_len(name) + _str_len(history_string) + _str_len(args[0]) + 45;
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
	_string_concat(err_bool, ": Unable to add/remove from environment\n");

	free(history_string);
	return (err_bool);
}

/**
 * error_for_alias - Creates an error message for alias_for_shellby errors.
 * @args: arguments array
 *
 * Return: error of the string
 *
 * Description: This function takes an array of arguments and generates an error
 *              message for alias_for_shellby errors. It returns the error string.
 */

char *error_for_alias(char **args)
{
	char *err_bool;
	int leng;

	leng = _str_len(name) + _str_len(args[0]) + 13;
	err_bool = malloc(sizeof(char) * (leng + 1));
	if (!err_bool)
		return (NULL);

	_copy_string(err_bool, "alias: ");
	_string_concat(err_bool, args[0]);
	_string_concat(err_bool, " not found\n");

	return (err_bool);
}

/**
 * exit_errors - Creates an error message for shellby_exit errors.
 * @args: arguments array
 *
 * Return: string of the error
 *
 * Description: This function takes an array of arguments and generates an error
 *              message for shellby_exit errors. It returns the error string.
 */

char *exit_errors(char **args)
{
	char *err_bool, *history_string;
	int leng;

	history_string = stringify(hist);
	if (!history_string)
		return (NULL);

	leng = _str_len(name) + _str_len(history_string) + _str_len(args[0]) + 27;
	err_bool = malloc(sizeof(char) * (leng + 1));
	if (!err_bool)
	{
		free(history_string);
		return (NULL);
	}

	_copy_string(err_bool, name);
	_string_concat(err_bool, ": ");
	_string_concat(err_bool, history_string);
	_string_concat(err_bool, ": exit: Illegal number: ");
	_string_concat(err_bool, args[0]);
	_string_concat(err_bool, "\n");

	free(history_string);
	return (err_bool);
}

/**
 * cd_errors - Creates an error message for shellby_cd errors.
 * @args: arguments array
 *
 * Return: string of the error
 *
 * Description: This function takes an array of arguments and generates an error
 *              message for shellby_cd errors. It returns the error string.
 */

char *cd_errors(char **args)
{
	char *err_bool, *history_string;
	int leng;

	history_string = stringify(hist);
	if (!history_string)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		_string_concat(err_bool, ": cd: Illegal option ");
	else
		_string_concat(err_bool, ": cd: can't cd to ");
	_string_concat(err_bool, args[0]);
	_string_concat(err_bool, "\n");

	free(history_string);
	return (err_bool);
}

/**
 * error_syntax - Creates an error message for syntax errors.
 * @args: Array of arguments passed.
 *
 * Return: Error string.
 *
 * Description: This function takes an array of arguments and generates an error
 *              message for syntax errors. It returns the error string.
 */

char *error_syntax(char **args)
{
	char *err_bool, *history_string;
	int leng;

	history_string = stringify(hist);
	if (!history_string)
		return (NULL);

	leng = _str_len(name) + _str_len(history_string) + _str_len(args[0]) + 33;
	err_bool = malloc(sizeof(char) * (leng + 1));
	if (!err_bool)
	{
		free(history_string);
		return (NULL);
	}

	_copy_string(err_bool, name);
	_string_concat(err_bool, ": ");
	_string_concat(err_bool, history_string);
	_string_concat(err_bool, ": Syntax err_bool: \"");
	_string_concat(err_bool, args[0]);
	_string_concat(err_bool, "\" unexpected\n");

	free(history_string);
	return (err_bool);
}
