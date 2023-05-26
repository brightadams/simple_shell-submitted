#include "main.h"

/**
 * alias_for_shellby - Handles the 'alias' builtin command in the shellby shell.
 * @args: An array of arguments.
 * @head: A double pointer to the initial element of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 *
 * Description: This function is responsible for processing the 'alias' command in the shellby shell.
 *              It supports various operations such as printing all defined aliases, printing a specific alias,
 *              or setting a new alias. The function takes the arguments passed to the command and performs
 *              the corresponding operation. If an error occurs during the execution, the return value is -1,
 *              otherwise it is 0.
 */

int alias_for_shellby(char **args, char __attribute__((__unused__)) **head)
{
	alias_t *tem = aliases;
	int z, y = 0;
	char *value;

	if (!args[0])
	{
		while (tem)
		{
			display_alias(tem);
			tem = tem->next;
		}
		return (y);
	}
	for (z = 0; args[z]; z++)
	{
		tem = aliases;
		value = _find_char(args[z], '=');
		if (!value)
		{
			while (tem)
			{
				if (compare_string(args[z], tem->name) == 0)
				{
					display_alias(tem);
					break;
				}
				tem = tem->next;
			}
			if (!tem)
				y = error_creator(args + z, 1);
		}
		else
			set_alias_value(args[z], value);
	}
	return (y);
}

/**
 * set_alias_value - Sets an existing alias 'variable_name' with a new value 'value',
 *             or creates a new alias with 'variable_name' and 'value'.
 * @variable_name: The name of the alias.
 * @value: The value of the alias. The first character is '='.
 *
 * Description: This function is used to set an existing alias with a new value
 *              or create a new alias. It takes the name of the alias and the value
 *              as parameters. The value should be in the format '=value'. If the
 *              alias with the given name already exists, its value will be updated
 *              with the new value. If the alias doesn't exist, a new alias will be
 *              created. The function performs the necessary operations to set or
 *              create the alias and returns void.
 */

void set_alias_value(char *variable_name, char *value)
{
	alias_t *tem = aliases;
	int leng, g, p;
	char *new_val;

	*value = '\0';
	value++;
	leng = _str_len(value) - _string_prefix_len(value, "'\"");
	new_val = malloc(sizeof(char) * (leng + 1));
	if (!new_val)
		return;
	for (g = 0, p = 0; value[g]; g++)
	{
		if (value[g] != '\'' && value[g] != '"')
			new_val[p++] = value[g];
	}
	new_val[p] = '\0';
	while (tem)
	{
		if (compare_string(variable_name, tem->name) == 0)
		{
			free(tem->value);
			tem->value = new_val;
			break;
		}
		tem = tem->next;
	}
	if (!tem)
		append_alias(&aliases, variable_name, new_val);
}

/**
 * display_alias - Prints the alias in the format 'name=value'.
 * @alias: Points to an alias.
 *
 * Description: This function takes a pointer to an alias structure and prints
 *              the alias in the format 'name=value'. It retrieves the name and
 *              value from the alias structure and prints them to the standard output.
 */

void display_alias(alias_t *alias)
{
	char *string_alias;
	int leng = _str_len(alias->name) + _str_len(alias->value) + 4;

	string_alias = malloc(sizeof(char) * (leng + 1));
	if (!string_alias)
		return;
	_copy_string(string_alias, alias->name);
	_string_concat(string_alias, "='");
	_string_concat(string_alias, alias->value);
	_string_concat(string_alias, "'\n");

	write(STDOUT_FILENO, string_alias, leng);
	free(string_alias);
}
/**
 * replace_aliases - Goes through all the arguments and replaces any matching alias
 *                   with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the modified arguments.
 *
 * Description: This function takes a 2D pointer to the arguments and iterates through
 *              each argument. If an argument matches an existing alias, it replaces
 *              the argument with the value of the alias. The modified arguments are
 *              returned.
 */

char **replace_aliases(char **args)
{
	alias_t *tem;
	int z;
	char *new_val;

	if (compare_string(args[0], "alias") == 0)
		return (args);
	for (z = 0; args[z]; z++)
	{
		tem = aliases;
		while (tem)
		{
			if (compare_string(args[z], tem->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_str_len(tem->value) + 1));
				if (!new_val)
				{
					remove_args_from_memory(args, args);
					return (NULL);
				}
				_copy_string(new_val, tem->value);
				free(args[z]);
				args[z] = new_val;
				z--;
				break;
			}
			tem = tem->next;
		}
	}

	return (args);
}

