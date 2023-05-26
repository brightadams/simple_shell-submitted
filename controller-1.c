#include "main.h"

/**
 * dup_env - Creates a duplicate of the current environment.
 *
 * Return: NULL if an error occurs, or
 *         a double pointer to the newly created copy of the environment.
 */

char **dup_env(void)
{
	char **new_env_var;
	size_t size;
	int ind;

	for (size = 0; environ[size]; size++)
		;

	new_env_var = malloc(sizeof(char *) * (size + 1));
	if (!new_env_var)
		return (NULL);

	for (ind = 0; environ[ind]; ind++)
	{
		new_env_var[ind] = malloc(_str_len(environ[ind]) + 1);

		if (!new_env_var[ind])
		{
			for (ind--; ind >= 0; ind--)
				free(new_env_var[ind]);
			free(new_env_var);
			return (NULL);
		}
		_copy_string(new_env_var[ind], environ[ind]);
	}
	new_env_var[ind] = NULL;

	return (new_env_var);
}

/**
 * _env_free - Releases the memory allocated for the copied environment.
 */

void _env_free(void)
{
	int ind;

	for (ind = 0; environ[ind]; ind++)
		free(environ[ind]);
	free(environ);
}

/**
 * _env_get - Retrieves the value of an environmental variable from the PATH.
 * @variable: The name of the environmental variable.
 *
 * Return: NULL if the environmental variable does not exist, or
 *         a pointer to the value of the environmental variable if found.
 */

char **_env_get(const char *varia)
{
	int ind, leng;

	leng = _str_len(varia);
	for (ind = 0; environ[ind]; ind++)
	{
		if (compare_n_string(varia, environ[ind], leng) == 0)
			return (&environ[ind]);
	}

	return (NULL);
}
