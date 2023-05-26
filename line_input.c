#include "main.h"

/**
 * re_allocate - Reallocates a memory block using malloc and free.
 * @pointer: Pointer to the previously allocated memory.
 * @size_of_old_line: Size in bytes of the allocated space for ptr.
 * @new_size: Size in bytes for the new memory block.
 *
 * Description: This function resizes the memory block pointed to by ptr to new_size bytes.
 *              If new_size is equal to old_size, the original block is returned.
 *              If new_size is 0 and ptr is not NULL, the block is freed and NULL is returned.
 *              If the allocation fails, NULL is returned.
 *
 * Return: Pointer if new_size is equal to old_size,
 *         NULL if new_size is 0 and ptr is not NULL,
 *         and a pointer to the reallocated memory block otherwise.
 */

void *re_allocate(void *pointer, unsigned int size_of_old_line, unsigned int new_size)
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
 * line_pointer - Reassigns the linePtr variable for line_getter.
 * @linePtr: Pointer to the buffer to store the input string.
 * @n: Size of linePtr.
 * @buffer: String to assign to the linePtr.
 * @b: Buffer size.
 *
 * Description: This function updates the linePtr and n variables used in line_getter
 *              with the provided buffer and buffer size.
 */

void line_pointer(char **linePtr, size_t *n, char *buffer, size_t b)
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
		_copy_string(*linePtr, buffer);
		free(buffer);
	}
}

/**
 * read_input - Reads input from a stream and stores it in a buffer.
 * @linePtr: Buffer to store the input.
 * @n: The size of the buffer.
 * @stream: Stream to read from.
 *
 * Description: This function reads input from the specified stream and stores it in the provided buffer.
 *              It reads up to n-1 bytes from the stream and adds a null terminator at the end of the input.
 *              The buffer should be large enough to hold the input, including the null terminator.
 *
 * Return: The number of bytes read from the stream. If an error occurs or the end of the stream is reached,
 *         it returns -1.
 */

ssize_t line_getter(char **linePtr, size_t *n, FILE *stream)
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
			buffer = re_allocate(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	line_pointer(linePtr, n, buffer, input);

	y = input;
	if (e != 0)
		input = 0;
	return (y);
}
