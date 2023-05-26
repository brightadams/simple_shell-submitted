#include "main.h"

/**
 * _copyenv - a function that creates a copy of the environment
 *
 * Return: If an err_bool occur return NULL or
 * a double pointer to the new copy if otherwise
 */
char **_copyenv(void)
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
		new_env_var[ind] = malloc(_strlen(environ[ind]) + 1);

		if (!new_env_var[ind])
		{
			for (ind--; ind >= 0; ind--)
				free(new_env_var[ind]);
			free(new_env_var);
			return (NULL);
		}
		_strcpy(new_env_var[ind], environ[ind]);
	}
	new_env_var[ind] = NULL;

	return (new_env_var);
}

/**
 * free_env - function that frees the copy of the environment
 */
void free_env(void)
{
	int ind;

	for (ind = 0; environ[ind]; ind++)
		free(environ[ind]);
	free(environ);
}

/**
 * _getenv - function that gets an environmental variable from the PATH
 * @varia:the environmental variable name
 *
 * Return: NULL If the environmental variable does not exist, or
 * a pointer to the environmental variable if otherwise
 */
char **_getenv(const char *varia)
{
	int ind, leng;

	leng = _strlen(varia);
	for (ind = 0; environ[ind]; ind++)
	{
		if (_strncmp(varia, environ[ind], leng) == 0)
			return (&environ[ind]);
	}

	return (NULL);
}
