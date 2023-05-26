#include "main.h"

/**
 * handle_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The len of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
	char *old_line, *n_line;
	char previous, current, next;
	size_t z, g;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	n_line = malloc(new_len + 1);
	if (!n_line)
		return;
	g = 0;
	old_line = *line;
	for (z = 0; old_line[z]; z++)
	{
		current = old_line[z];
		next = old_line[z + 1];
		if (z != 0)
		{
			previous = old_line[z - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					n_line[g++] = ' ';
					n_line[g++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					n_line[g++] = ';';
					n_line[g++] = ' ';
					continue;
				}
				if (previous != ' ')
					n_line[g++] = ' ';
				n_line[g++] = ';';
				if (next != ' ')
					n_line[g++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					n_line[g++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					n_line[g++] = '&';
					n_line[g++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					n_line[g++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					n_line[g++] = '|';
					n_line[g++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
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

	free(*line);
	*line = n_line;
}

/**
 * get_new_len - Gets the new len of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new len of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t z;
	ssize_t new_len = 0;
	char current, next;

	for (z = 0; line[z]; z++)
	{
		current = line[z];
		next = line[z + 1];
		if (current == '#')
		{
			if (z == 0 || line[z - 1] == ' ')
			{
				line[z] = '\0';
				break;
			}
		}
		else if (z != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[z - 1] != ' ' && line[z - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[z - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[z - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[z], &new_len);
		}
		else if (current == ';')
		{
			if (z != 0 && line[z - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
	}
}
