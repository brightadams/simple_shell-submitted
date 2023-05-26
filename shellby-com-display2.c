#include "main.h"

/**
 * _env_help - This function displays information about the shellby builtin command 'env'.
 *
 * Return: None
 */

void _env_help(void)
{
	char *mess = "env: env\n\tPrints the curr environment.\n";

	write(STDOUT_FILENO, mess, _str_len(mess));
}

/**
 * _setenv_help - This function displays information about the shellby builtin command 'setenv'.
 *
 * Return: None
 */

void _setenv_help(void)
{
	char *mess = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, mess, _str_len(mess));
}

/**
 * _unsetenv_helper - This function displays information about the shellby builtin command 'unsetenv'.
 *
 * Return: None
 */

void _unsetenv_helper(void)
{
	char *mess = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "message to stderr.\n";
	write(STDOUT_FILENO, mess, _str_len(mess));
}

