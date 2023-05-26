#include "main.h"

/**
 * _realloc - function that reallocates a memory
 * block using malloc and free
 * @pointer: pointer to previously allocated memory
 * @size_of_old_line: size in bytes_size of allocated space for pointer
 * @new_size: size in bytes_size for new memory block
 *
 * Return: pointer if new_size == size_of_old_line, NULL
 * if new_size == 0 and pointer is not NULL and
 * a pointer to reallocated memory block if otherwise
 */
void *_realloc(void *pointer, unsigned int size_of_old_line, unsigned int new_size)
{
	void *memo;
	char *copied_pointer, *fill;
	unsigned int ind;

	if (new_size == size_of_old_line)
		return (pointer);

	if (pointer == NULL)
	{
		memo = malloc(new_size);
		if (memo == NULL)
			return (NULL);

		return (memo);
	}

	if (new_size == 0 && pointer != NULL)
	{
		free(pointer);
		return (NULL);
	}

	copied_pointer = pointer;
	memo = malloc(sizeof(*copied_pointer) * new_size);
	if (memo == NULL)
	{
		free(pointer);
		return (NULL);
	}

	fill = memo;

	for (ind = 0; ind < size_of_old_line && ind < new_size; ind++)
		fill[ind] = *copied_pointer++;

	free(pointer);
	return (memo);
}

/**
 * assign_lineptr - function that reassigns the linePtr
 * variable for _getline
 * @linePtr: a buffer to store input string
 * @n: size of linePtr
 * @buffer: string to assign to the linePtr
 * @b: buffer size
 */
void assign_lineptr(char **linePtr, size_t *n, char *buffer, size_t b)
{
	if (*linePtr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*linePtr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*linePtr = buffer;
	}
	else
	{
		_strcpy(*linePtr, buffer);
		free(buffer);
	}
}

/**
 * _getline - function that reads input from a stream
 * @linePtr: buffer to store input
 * @n: The size of linePtr
 * @stream: stream to read from
 *
 * Return: number of bytes_size read
 */
ssize_t _getline(char **linePtr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t y;
	char c = 'x', *buffer;
	int e;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		e = read(STDIN_FILENO, &c, 1);
		if (e == -1 || (e == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (e == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_lineptr(linePtr, n, buffer, input);

	y = input;
	if (e != 0)
		input = 0;
	return (y);
}
