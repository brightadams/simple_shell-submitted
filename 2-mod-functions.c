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
	int index;

	for (index = 0; string_chars[index]; index++)
	{
		if (string_chars[index] == c)
			return (string_chars + index);
	}

	return (NULL);
}

/**
 * _strspn - function that gets the len of a prefix substring
 * @string_chars: the string that will be searched
 * @accept: the prefix that will be measured
 *
 * Return: number of bytes in string_chars which consist
 * only of bytes from accept
 */
int _strspn(char *string_chars, char *accept)
{
	int bytes = 0;
	int index;

	while (*string_chars)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*string_chars == accept[index])
			{
				bytes++;
				break;
			}
		}
		string_chars++;
	}
	return (bytes);
}

/**
 * _strcmp - function that compares two strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return: positive byte difference if s1 > s2, 0 if s1 = s2
 * and negative byte difference if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - function that compare two strings
 * @s1: first pointer to a string
 * @s2: second pointer to a string
 * @n: The first n bytes of the strings to to be compared
 *
 * Return: less than 0 if s1 is shorter than s2,
 * greater than 0 is s1 is longer than s2 and 0 if they match
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t z;

	for (z = 0; s1[z] && s2[z] && z < n; z++)
	{
		if (s1[z] > s2[z])
			return (s1[z] - s2[z]);
		else if (s1[z] < s2[z])
			return (s1[z] - s2[z]);
	}
	if (z == n)
		return (0);
	else
		return (-15);
}
