#include "main.h"

/**
 * _find_char - Locates the first occurrence of a character in a string.
 * @string: The string to be searched.
 * @c: The character to be located.
 *
 * Return: A pointer to the first occurrence of the character if found,
 *         or NULL if the character is not found.
 */

char *_find_char(char *string_chars, char c)
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
 * _string_prefix_len - Gets the length of a prefix substring.
 * @string_chars: The string to be searched.
 * @accept: The prefix to be measured.
 *
 * Return: The number of bytes in the string which consist only of bytes from accept.
 */

int _string_prefix_len(char *string_chars, char *accept)
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
 * compare_string - Compares two strings.
 * @string1_pointer: The first string.
 * @string2_pointer: The second string.
 *
 * Return: A positive byte difference if string1_pointer is greater than string2_pointer,
 *         0 if string1_pointer is equal to string2_pointer,
 *         and a negative byte difference if string1_pointer is less than string2_pointer.
 */

int compare_string(char *string1_pointer, char *string2_pointer)
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
 * compare_n_string - Compares two strings.
 * @string1_pointer: The first string.
 * @string2_pointer: The second string.
 * @n: The number of bytes to compare.
 *
 * Return: A value less than 0 if string1_pointer is shorter than string2_pointer,
 *         a value greater than 0 if string1_pointer is longer than string2_pointer,
 *         and 0 if the first n bytes of string1_pointer and string2_pointer match.
 */

int compare_n_string(const char *string1_pointer, const char *string2_pointer, size_t n)
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
