#include "main.h"

/**
 * _str_len - Calculates the length of a string.
 * @string_chars: Pointer to the string.
 *
 * Return: Length of the string.
 *
 * Description: This function takes a pointer to a string and determines the length
 *              of the string by iterating through each character until the null
 *              terminator is encountered. It returns the length of the string.
 */

int _str_len(const char *string_chars)
{
	int length = 0;

	if (!string_chars)
		return (length);
	for (length = 0; string_chars[length]; length++)
		;
	return (length);
}

/**
 * _copy_string - Copies the contents of the string pointed to by string_source to the
 *           buffer pointed to by string_destination, including the terminating null byte.
 * @string_destination: Pointer to the destination buffer.
 * @string_source: Pointer to the source string.
 *
 * Return: Pointer to the destination buffer.
 *
 * Description: This function copies the contents of the string pointed to by
 *              string_source to the buffer pointed to by string_destination,
 *              including the terminating null byte of the string. It assumes that
 *              the destination buffer is large enough to hold the entire source string.
 *              The function returns a pointer to the destination buffer.
 */

char *_copy_string(char *string_destination, const char *string_source)
{
	size_t z;

	for (z = 0; string_source[z] != '\0'; z++)
		string_destination[z] = string_source[z];
	string_destination[z] = '\0';
	return (string_destination);
}

/**
 * _string_concat - Concatenates two strings.
 * @string_destination: Points to the destination string.
 * @string_source: Points to  source string.
 *
 * Return: returns to the destination string.
 */

char *_string_concat(char *string_destination, const char *string_source)
{
	char *temp_destination;
	const char *temp_source;

	temp_destination = string_destination;
	temp_source =  string_source;

	while (*temp_destination != '\0')
		temp_destination++;

	while (*temp_source != '\0')
		*temp_destination++ = *temp_source++;
	*temp_destination = '\0';
	return (string_destination);
}

/**
 * my_strncat - Concatenates two strings up to a specified number of bytes.
 * @string_destination: Pointer to the destination string.
 * @string_source: Pointer to the source string.
 * @n: Number of bytes to copy from source.
 *
 * Return: Pointer to the destination string.
 */

char *_string_n_concat(char *string_destination, const char *string_source, size_t n)
{
	size_t destination_len = _str_len(string_destination);
	size_t z;

	for (z = 0; z < n && string_source[z] != '\0'; z++)
		string_destination[destination_len + z] = string_source[z];
	string_destination[destination_len + z] = '\0';

	return (string_destination);
}
