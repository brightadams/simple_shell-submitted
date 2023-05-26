#include "main.h"

/**
 * _strlen - function that returns the length of a string
 * @string_chars: pointer to the characters string
 *
 * Return: length of the character string
 */
int _strlen(const char *string_chars)
{
	int length = 0;

	if (!string_chars)
		return (length);
	for (length = 0; string_chars[length]; length++)
		;
	return (length);
}

/**
 * _strcpy - function that copies the contents of the string
 * pointed to by string_source to the buffer pointed to by string_destination, including
 * the terminating null byte of the string
 * @string_destination: pointer to the destination of string to be copied
 * @string_source: pointer to the string_source of the source string
 *
 * Return: pointer to string_destination
 */
char *_strcpy(char *string_destination, const char *string_source)
{
	size_t z;

	for (z = 0; string_source[z] != '\0'; z++)
		string_destination[z] = string_source[z];
	string_destination[z] = '\0';
	return (string_destination);
}

/**
 * _strcat - function that Concantenates two strings
 * @string_destination: a pointer to destination string
 * @string_source: a pointer to source string
 *
 * Return: pointer to destination string
 */
char *_strcat(char *string_destination, const char *string_source)
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
 * _strncat - function that concantenates two strings where n
 * number of bytes_size are copied from source
 * @string_destination: a pointer to the destination string
 * @string_source: a pointer to the source string
 * @n: number of bytes_size to copy from string_source
 *
 * Return: pointer to destination string
 */
char *_strncat(char *string_destination, const char *string_source, size_t n)
{
	size_t destination_len = _strlen(string_destination);
	size_t z;

	for (z = 0; z < n && string_source[z] != '\0'; z++)
		string_destination[destination_len + z] = string_source[z];
	string_destination[destination_len + z] = '\0';

	return (string_destination);
}
