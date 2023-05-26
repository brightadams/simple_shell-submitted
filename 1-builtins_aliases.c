#include "main.h"

/**
 * shellby_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args:This is an array of arguments.
 * @head: A double pointer that begins args.
 *
 * Return: If an err_bool occurs - -1.
 *         Otherwise - 0.
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **head)
{
	alias_t *tem = aliases;
	int z, y = 0;
	char *value;

	if (!args[0])
	{
		while (tem)
		{
			print_alias(tem);
			tem = tem->next;
		}
		return (y);
	}
	for (z = 0; args[z]; z++)
	{
		tem = aliases;
		value = _strchr(args[z], '=');
		if (!value)
		{
			while (tem)
			{
				if (_strcmp(args[z], tem->name) == 0)
				{
					print_alias(tem);
					break;
				}
				tem = tem->next;
			}
			if (!tem)
				y = create_error(args + z, 1);
		}
		else
			set_alias(args[z], value);
	}
	return (y);
}

/**
 * set_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'
 * @variable_name:Should be the  Name of the alias
 * @value: The Value of the alias. First character is an '='
 */
void set_alias(char *variable_name, char *value)
{
	alias_t *tem = aliases;
	int leng, g, p;
	char *value_new;

	*value = '\0';
	value++;
	leng = _strlen(value) - _strspn(value, "'\"");
	value_new = malloc(sizeof(char) * (leng + 1));
	if (!value_new)
		return;
	for (g = 0, p = 0; value[g]; g++)
	{
		if (value[g] != '\'' && value[g] != '"')
			value_new[p++] = value[g];
	}
	value_new[p] = '\0';
	while (tem)
	{
		if (_strcmp(variable_name, tem->name) == 0)
		{
			free(tem->value);
			tem->value = value_new;
			break;
		}
		tem = tem->next;
	}
	if (!tem)
		add_alias_end(&aliases, variable_name, value_new);
}

/**
 * print_alias -This Prints the alias in the format name='value'.
 * @alias:This Pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *string_alias;
	int leng = _strlen(alias->name) + _strlen(alias->value) + 4;

	string_alias = malloc(sizeof(char) * (leng + 1));
	if (!string_alias)
		return;
	_strcpy(string_alias, alias->name);
	_strcat(string_alias, "='");
	_strcat(string_alias, alias->value);
	_strcat(string_alias, "'\n");

	write(STDOUT_FILENO, string_alias, leng);
	free(string_alias);
}
/**
 * replace_aliases -This Goes through all the arguments and replace any matching alias
 * with their value.
 * @args:All 2D pointer to the arguments.
 *
 * Return:All 2D pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *tem;
	int z;
	char *value_new;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (z = 0; args[z]; z++)
	{
		tem = aliases;
		while (tem)
		{
			if (_strcmp(args[z], tem->name) == 0)
			{
				value_new = malloc(sizeof(char) * (_strlen(tem->value) + 1));
				if (!value_new)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(value_new, tem->value);
				free(args[z]);
				args[z] = value_new;
				z--;
				break;
			}
			tem = tem->next;
		}
	}

	return (args);
}

