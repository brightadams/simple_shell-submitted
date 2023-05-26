#include "main.h"

/**
 * token_len - function that loocates the delimiter
 * index marking the end of the first token
 * @str: the string that will be searched
 * @delim: delimiter character
 *
 * Return: delimiter index marking the end of
 * intitial token pointed to be str
 */
int token_len(char *str, char *delim)
{
	int index = 0, leng = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		leng++;
		index++;
	}

	return (leng);
}

/**
 * count_tokens - function that counts the number of
 * delimited words contained in a string
 * @str: string to be searched
 * @delim: delimiter character
 *
 * Return: total counts of words contained within str
 */
int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, leng = 0;

	for (index = 0; *(str + index); index++)
		leng++;

	for (index = 0; index < leng; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - function that tokenizes a string
 * @line: the string
 * @delim: delimiter character to tokenize the string
 *
 * Return: pointer to array containing tokenized words
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, p, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (p = 0; p < tokens; p++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[p] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[p])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[p][l] = line[index];
			index++;
		}

		ptr[p][l] = '\0';
	}
	ptr[p] = NULL;
	ptr[p + 1] = NULL;

	return (ptr);
}
