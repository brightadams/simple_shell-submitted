#include "main.h"

/**
 * _num_len - Determines the length of a number in terms of digits.
 * @numb: The number to be measured.
 *
 * Return: The count of digits in the given number.
 */

int _num_len(int numb)
{
	unsigned int numb1;
	int leng = 1;

	if (numb < 0)
	{
		leng++;
		numb1 = numb * -1;
	}
	else
	{
		numb1 = numb;
	}
	while (numb1 > 9)
	{
		leng++;
		numb1 /= 10;
	}

	return (leng);
}

/**
 * stringify - Converts an integer to its string representation.
 * @numb: The integer to be converted.
 *
 * Return: The string representation of the given integer.
 */

char *stringify(int numb)
{
	char *buffer;
	int leng = _num_len(numb);
	unsigned int numb1;

	buffer = malloc(sizeof(char) * (leng + 1));
	if (!buffer)
		return (NULL);

	buffer[leng] = '\0';

	if (numb < 0)
	{
		numb1 = numb * -1;
		buffer[0] = '-';
	}
	else
	{
		numb1 = numb;
	}

	leng--;
	do {
		buffer[leng] = (numb1 % 10) + '0';
		numb1 /= 10;
		leng--;
	} while (numb1 > 0);

	return (buffer);
}


/**
 * error_creator - Generates a customized error message.
 * @args: An array of arguments.
 * @err: The value of the error.
 *
 * Return: The error value.
 */

int error_creator(char **args, int err)
{
	char *err_bool;

	switch (err)
	{
	case -1:
		err_bool = shellby_error_env(args);
		break;
	case 1:
		err_bool = error_for_alias(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			err_bool = exit_errors(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			err_bool = error_syntax(args);
		else
			err_bool = cd_errors(args);
		break;
	case 126:
		err_bool = _perm_errors(args);
		break;
	case 127:
		err_bool = not_found_errors(args);
		break;
	}
	write(STDERR_FILENO, err_bool, _str_len(err_bool));

	if (err_bool)
		free(err_bool);
	return (err);

}
