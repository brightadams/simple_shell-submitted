#include "main.h"

/**
 * show_all_commands - Displays all possible builtin shellby commands.
 *
 * Description: This function is responsible for displaying all the
 *              available builtin commands in the shellby shell. It
 *              provides a comprehensive list of commands along with
 *              their brief descriptions. This function does not
 *              take any arguments or return any value.
 */

void show_all_commands(void)
{
	char *mess = "Shellby\nThe ff commands are in-built.\n";

	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "Type 'help' to see the list.\nType 'help name' to find ";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, mess, _str_len(mess));
}

/**
 * show_help_alias - Displays information on the shellby builtin command 'alias'.
 *
 * Description: This function is responsible for displaying detailed information
 *              about the 'alias' command in the shellby shell. It provides an
 *              explanation of how the 'alias' command works, including examples
 *              of its usage and the expected output. This function does not
 *              take any arguments or return any value.
 */

void show_help_alias(void)
{
	char *mess = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "\n\talias: Prints a list of all aliases, one per line_read, in ";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = " the aliases name, name2, etc. one per line_read, in the ";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, mess, _str_len(mess));
}

/**
 * show_help_cd - Displays information on the shellby builtin command 'cd'.
 *
 * Description: This function is responsible for displaying detailed information
 *              about the 'cd' command in the shellby shell. It provides an
 *              explanation of how the 'cd' command works, including examples
 *              of its usage and the expected behavior. This function does not
 *              take any arguments or return any value.
 */

void show_help_cd(void)
{
	char *mess = "cd: cd [DIRECTORY]\n\tChanges the current dir of the";

	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = " process to DIR.\n\n\tIf no arg is given, the ";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "after a change of directory.\n";
	write(STDOUT_FILENO, mess, _str_len(mess));
}

/**
 * exit_help - Displays information about the shellby builtin command 'exit'.
 *
 * Return: None
 *
 * Description:
 *    This function prints detailed information about the 'exit' command in the
 *    shellby shell. It explains the purpose of the command, its usage, and the
 *    possible exit values. The function does not accept any arguments or return
 *    a value.
 */

void exit_help(void)
{
	char *mess = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = " exit 0.\n";
	write(STDOUT_FILENO, mess, _str_len(mess));
}

/**
 * help_helper - Displays information about the shellby builtin command 'help'.
 *
 * Return: None
 *
 * Description:
 *    This function displays detailed information about the 'help' command in
 *    the shellby shell. It explains the purpose of the command and how it can
 *    be used to get help for other commands. The function does not accept any
 *    arguments or return a value.
 */

void help_helper(void)
{
	char *mess = "help: help\n\tView all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, mess, _str_len(mess));
	mess = "builtin command.\n";
	write(STDOUT_FILENO, mess, _str_len(mess));
}

