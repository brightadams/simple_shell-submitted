#include "main.h"

/**
 * _strlen - function that returns the len of a string
 * @string_chars: pointer to the characters string
 *
 * Return: len of the character string
 */
int _strlen(const char *string_chars)
{
	int len = 0;

	if (!string_chars)
		return (len);
	for (len = 0; string_chars[len]; len++)
		;
	return (len);
}

/**
 * _strcpy - function that copies the contents of the string
 * pointed to by src to the buffer pointed to by dest, including
 * the terminating null byte of the string
 * @dest: pointer to the destination of string to be copied
 * @src: pointer to the src of the source string
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	size_t z;

	for (z = 0; src[z] != '\0'; z++)
		dest[z] = src[z];
	dest[z] = '\0';
	return (dest);
}

/**
 * _strcat - function that Concantenates two strings
 * @dest: a pointer to destination string
 * @src: a pointer to source string
 *
 * Return: pointer to destination string
 */
char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - function that concantenates two strings where n
 * number of bytes are copied from source
 * @dest: a pointer to the destination string
 * @src: a pointer to the source string
 * @n: number of bytes to copy from src
 *
 * Return: pointer to destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t z;

	for (z = 0; z < n && src[z] != '\0'; z++)
		dest[dest_len + z] = src[z];
	dest[dest_len + z] = '\0';

	return (dest);
}
