#include "main.h"

/**
 * _strchr - function that locates a character in a string
 * @string_chars: the string that will be searched
 * @c: the character that will be located
 *
 * Return: a pointer to the first occurence if c is
 * found or NULL If c is not found
 */
char *_strchr(char *string_chars, char c)
{
	int ind;

	for (ind = 0; string_chars[ind]; ind++)
	{
		if (string_chars[ind] == c)
			return (string_chars + ind);
	}

	return (NULL);
}

/**
 * _strspn - function that gets the length of a prefix substring
 * @string_chars: the string that will be searched
 * @accept: the prefix that will be measured
 *
 * Return: number of bytes_size in string_chars which consist
 * only of bytes_size from accept
 */
int _strspn(char *string_chars, char *accept)
{
	int bytes_size = 0;
	int ind;

	while (*string_chars)
	{
		for (ind = 0; accept[ind]; ind++)
		{
			if (*string_chars == accept[ind])
			{
				bytes_size++;
				break;
			}
		}
		string_chars++;
	}
	return (bytes_size);
}

/**
 * _strcmp - function that compares two strings
 * @string1_pointer: the first string
 * @string2_pointer: the second string
 *
 * Return: positive byte difference if string1_pointer > string2_pointer, 0 if string1_pointer = string2_pointer
 * and negative byte difference if string1_pointer < string2_pointer
 */
int _strcmp(char *string1_pointer, char *string2_pointer)
{
	while (*string1_pointer && *string2_pointer && *string1_pointer == *string2_pointer)
	{
		string1_pointer++;
		string2_pointer++;
	}

	if (*string1_pointer != *string2_pointer)
		return (*string1_pointer - *string2_pointer);

	return (0);
}

/**
 * _strncmp - function that compare two strings
 * @string1_pointer: first pointer to a string
 * @string2_pointer: second pointer to a string
 * @n: The first n bytes_size of the strings to to be compared
 *
 * Return: less than 0 if string1_pointer is shorter than string2_pointer,
 * greater than 0 is string1_pointer is longer than string2_pointer and 0 if they match
 */
int _strncmp(const char *string1_pointer, const char *string2_pointer, size_t n)
{
	size_t z;

	for (z = 0; string1_pointer[z] && string2_pointer[z] && z < n; z++)
	{
		if (string1_pointer[z] > string2_pointer[z])
			return (string1_pointer[z] - string2_pointer[z]);
		else if (string1_pointer[z] < string2_pointer[z])
			return (string1_pointer[z] - string2_pointer[z]);
	}
	if (z == n)
		return (0);
	else
		return (-15);
}
