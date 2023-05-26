#include "main.h"

/**
 * _line_input - Splits a line read from standard input into separate commands.
 * @line_read: A pointer to the line read from standard input.
 * @read: The length of the line read.
 *
 * Description: Inserts spaces to separate commands based on delimiters like
 *              ";", "||", and "&&". Replaces "#" with '\0' to ignore comments.
 */

void _line_input(char **line_read, ssize_t read)
{
	char *old_line, *n_line;
	char prev, curr, next;
	size_t z, g;
	ssize_t n_length;

	n_length = _new_line(*line_read);
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
 * _new_line - Calculates the new length of a line after partitioning
 *               it by delimiters such as ";", "||", "&&", or "#".
 * @line_read: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Truncates lines containing '#' comments by replacing '#' with '\0'.
 */


ssize_t _new_line(char *line_read)
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
				_operators_logical(&line_read[z], &n_length);
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
 * _operators_logical - Checks a line for logical operators "||" or "&&".
 * @line_read: points to the character to check in the line_read.
 * @n_length: points to the new length of the line_read in _new_line function.
 */

void _operators_logical(char *line_read, ssize_t *n_length)
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
