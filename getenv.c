#include "shell.h"

/**
 * fetch_environment - Returns a copy of the environment as a string array.
 * @info: Structure containing potential arguments.
 *
 * Return: Pointer to the string array containing the environment.
 */
char **fetch_environment(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * discard_environment_variable - Removes an environment variable.
 * @info: Structure containing potential arguments.
 * @variable: The string representing the environment variable.
 *
 * Return: 1 on deletion, 0 otherwise.
 */
int discard_environment_variable(info_t *info, char *variable)
{
	list_t *current = info->env;
	size_t index = 0;
	char *match;

	if (!current || !variable)
		return (0);

	while (current)
	{
		match = starts_with(current->str, variable);
		if (match && *match == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			current = info->env;
			continue;
		}
		current = current->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * set_environment_variable - Initializes or modifies an environment variable.
 * @info: Structure containing potential arguments.
 * @variable: The string representing the environment variable.
 * @value: The string representing the value of the environment variable.
 *
 * Return: Always 0.
 */
int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *current;
	char *match;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	current = info->env;
	while (current)
	{
		match = starts_with(current->str, variable);
		if (match && *match == '=')
		{
			free(current->str);
			current->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		current = current->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
