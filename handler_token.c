#include "main.h"

/**
 * token_len - function that loocates the delimiter
 * ind marking the end of the first token
 * @str: the string that will be searched
 * @deli: delimiter character
 *
 * Return: delimiter ind marking the end of
 * intitial token pointed to be str
 */
int token_len(char *str, char *deli)
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
 * count_tokens - function that counts the number of
 * delimited words contained in a string
 * @str: string to be searched
 * @deli: delimiter character
 *
 * Return: total counts of words contained within str
 */
int count_tokens(char *str, char *deli)
{
	int ind, tokens = 0, leng = 0;

	for (ind = 0; *(str + ind); ind++)
		leng++;

	for (ind = 0; ind < leng; ind++)
	{
		if (*(str + ind) != *deli)
		{
			tokens++;
			ind += token_len(str + ind, deli);
		}
	}

	return (tokens);
}

/**
 * _strtok - function that tokenizes a string
 * @line_read: the string
 * @deli: delimiter character to tokenize the string
 *
 * Return: pointer to array containing tokenized words
 */
char **_strtok(char *line_read, char *deli)
{
	char **pointer;
	int ind = 0, tokens, p, letters, l;

	tokens = count_tokens(line_read, deli);
	if (tokens == 0)
		return (NULL);

	pointer = malloc(sizeof(char *) * (tokens + 2));
	if (!pointer)
		return (NULL);

	for (p = 0; p < tokens; p++)
	{
		while (line_read[ind] == *deli)
			ind++;

		letters = token_len(line_read + ind, deli);

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
