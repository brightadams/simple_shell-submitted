#include "main.h"

/**
 * num_len - function that counts the digital
 * len of a number
 * @numb: The number to be measured
 *
 * Return: the digital lenghth
 */
int num_len(int numb)
{
	unsigned int num1;
	int leng = 1;

	if (numb < 0)
	{
		leng++;
		num1 = numb * -1;
	}
	else
	{
		num1 = numb;
	}
	while (num1 > 9)
	{
		leng++;
		num1 /= 10;
	}

	return (leng);
}

/**
 * _itoa - function that converts an
 * integer to a string
 * @numb: the integer to be converted
 *
 * Return: converted string
 */
char *_itoa(int numb)
{
	char *buffer;
	int leng = num_len(numb);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (leng + 1));
	if (!buffer)
		return (NULL);

	buffer[leng] = '\0';

	if (numb < 0)
	{
		num1 = numb * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = numb;
	}

	leng--;
	do {
		buffer[leng] = (num1 % 10) + '0';
		num1 /= 10;
		leng--;
	} while (num1 > 0);

	return (buffer);
}


/**
 * create_error - function that Writes a custom
 * err_bool message
 * @args: array of arguments
 * @err: value of the err_bool
 *
 * Return: the err_bool value
 */
int create_error(char **args, int err)
{
	char *err_bool;

	switch (err)
	{
	case -1:
		err_bool = error_env(args);
		break;
	case 1:
		err_bool = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			err_bool = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			err_bool = error_2_syntax(args);
		else
			err_bool = error_2_cd(args);
		break;
	case 126:
		err_bool = error_126(args);
		break;
	case 127:
		err_bool = error_127(args);
		break;
	}
	write(STDERR_FILENO, err_bool, _strlen(err_bool));

	if (err_bool)
		free(err_bool);
	return (err);

}
