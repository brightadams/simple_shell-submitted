#include "main.h"

/**
 * help_env -This Displays information on the shellby builtin command 'env'.
 */
void help_env(void)
{
	char *mess = "env: env\n\tPrints the curr environment.\n";

	write(STDOUT_FILENO, mess, _strlen(mess));
}

/**
 * help_setenv -This  Displays information on the shellby builtin command 'setenv'.
 */
void help_setenv(void)
{
	char *mess = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, mess, _strlen(mess));
	mess = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, mess, _strlen(mess));
	mess = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, mess, _strlen(mess));
}

/**
 * help_unsetenv -It Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void help_unsetenv(void)
{
	char *mess = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, mess, _strlen(mess));
	mess = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, mess, _strlen(mess));
	mess = "message to stderr.\n";
	write(STDOUT_FILENO, mess, _strlen(mess));
}

