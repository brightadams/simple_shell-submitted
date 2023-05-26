#include "main.h"

/**
 * handle_line - Partitions a line_read read from standard input as needed.
 * @line_read: A pointer to a line_read read from standard input.
 * @read: The length of line_read.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **line_read, ssize_t read)
{
	char *old_line, *n_line;
	char prev, curr, next;
	size_t z, g;
	ssize_t n_length;

	n_length = get_new_len(*line_read);
	if (n_length == read - 1)
		return;
	n_line = malloc(n_length + 1);
	if (!n_line)
		return;
	g = 0;
	old_line = *line_read;
	for (z = 0; old_line[z]; z++)
	{
		curr = old_line[z];
		next = old_line[z + 1];
		if (z != 0)
		{
			prev = old_line[z - 1];
			if (curr == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					n_line[g++] = ' ';
					n_line[g++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					n_line[g++] = ';';
					n_line[g++] = ' ';
					continue;
				}
				if (prev != ' ')
					n_line[g++] = ' ';
				n_line[g++] = ';';
				if (next != ' ')
					n_line[g++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (next == '&' && prev != ' ')
					n_line[g++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					n_line[g++] = '&';
					n_line[g++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (next == '|' && prev != ' ')
					n_line[g++]  = ' ';
				else if (prev == '|' && next != ' ')
				{
					n_line[g++] = '|';
					n_line[g++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (z != 0 && old_line[z - 1] != ' ')
				n_line[g++] = ' ';
			n_line[g++] = ';';
			if (next != ' ' && next != ';')
				n_line[g++] = ' ';
			continue;
		}
		n_line[g++] = old_line[z];
	}
	n_line[g] = '\0';

	free(*line_read);
	*line_read = n_line;
}

/**
 * get_new_len - Gets the new length of a line_read partitioned
 *               by ";", "||", "&&&", or "#".
 * @line_read: The line_read to check.
 *
 * Return: The new length of the line_read.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line_read)
{
	size_t z;
	ssize_t n_length = 0;
	char curr, next;

	for (z = 0; line_read[z]; z++)
	{
		curr = line_read[z];
		next = line_read[z + 1];
		if (curr == '#')
		{
			if (z == 0 || line_read[z - 1] == ' ')
			{
				line_read[z] = '\0';
				break;
			}
		}
		else if (z != 0)
		{
			if (curr == ';')
			{
				if (next == ';' && line_read[z - 1] != ' ' && line_read[z - 1] != ';')
				{
					n_length += 2;
					continue;
				}
				else if (line_read[z - 1] == ';' && next != ' ')
				{
					n_length += 2;
					continue;
				}
				if (line_read[z - 1] != ' ')
					n_length++;
				if (next != ' ')
					n_length++;
			}
			else
				logical_ops(&line_read[z], &n_length);
		}
		else if (curr == ';')
		{
			if (z != 0 && line_read[z - 1] != ' ')
				n_length++;
			if (next != ' ' && next != ';')
				n_length++;
		}
		n_length++;
	}
	return (n_length);
}
/**
 * logical_ops - Checks a line_read for logical operators "||" or "&&".
 * @line_read: A pointer to the character to check in the line_read.
 * @n_length: Pointer to n_length in get_new_len function.
 */
void logical_ops(char *line_read, ssize_t *n_length)
{
	char prev, curr, next;

	prev = *(line_read - 1);
	curr = *line_read;
	next = *(line_read + 1);

	if (curr == '&')
	{
		if (next == '&' && prev != ' ')
			(*n_length)++;
		else if (prev == '&' && next != ' ')
			(*n_length)++;
	}
	else if (curr == '|')
	{
		if (next == '|' && prev != ' ')
			(*n_length)++;
		else if (prev == '|' && next != ' ')
			(*n_length)++;
	}
}
