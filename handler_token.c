#include "main.h"

/**
 * get_token_length - Finds the index of the delimiter that marks
 *             the end of the first token in a string.
 * @str: The string to be searched.
 * @deli: The delimiter character.
 *
 * Return: The index of the delimiter that marks the end of
 *         the initial token pointed to by str.
 */

int get_token_length(char *str, char *deli)
{
	int ind = 0, leng = 0;

	while (*(str + ind) && *(str + ind) != *deli)
	{
		leng++;
		ind++;
	}

	return (leng);
}

/**
 * tokens_counter - Counts the number of delimited words
 *                in a string.
 * @str: The string to be searched.
 * @deli: The delimiter character.
 *
 * Return: The total count of words contained within str.
 */

int tokens_counter(char *str, char *deli)
{
	int ind, tokens = 0, leng = 0;

	for (ind = 0; *(str + ind); ind++)
		leng++;

	for (ind = 0; ind < leng; ind++)
	{
		if (*(str + ind) != *deli)
		{
			tokens++;
			ind += get_token_length(str + ind, deli);
		}
	}

	return (tokens);
}

/**
 * _strtok - Splits a string into tokens based on a specified delimiter.
 * @line_read: The string to be tokenized.
 * @deli: The delimiter character used to separate the tokens.
 *
 * Return: A pointer to an array that contains the tokenized words.
 */

char **_strtok(char *line_read, char *deli)
{
	char **pointer;
	int ind = 0, tokens, p, letters, l;

	tokens = tokens_counter(line_read, deli);
	if (tokens == 0)
		return (NULL);

	pointer = malloc(sizeof(char *) * (tokens + 2));
	if (!pointer)
		return (NULL);

	for (p = 0; p < tokens; p++)
	{
		while (line_read[ind] == *deli)
			ind++;

		letters = get_token_length(line_read + ind, deli);

		pointer[p] = malloc(sizeof(char) * (letters + 1));
		if (!pointer[p])
		{
			for (ind -= 1; ind >= 0; ind--)
				free(pointer[ind]);
			free(pointer);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			pointer[p][l] = line_read[ind];
			ind++;
		}

		pointer[p][l] = '\0';
	}
	pointer[p] = NULL;
	pointer[p + 1] = NULL;

	return (pointer);
}
