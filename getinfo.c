#include "shell.h"

/**
 * initialize_info - Sets up the info_t struct.
 * @info: The address of the info_t struct.
 */
void initialize_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * configure_info - Configures the info_t struct.
 * @info: The address of the info_t struct.
 * @args: The argument vector.
 */
void configure_info(info_t *info, char **args)
{
	int i = 0;

	info->fname = args[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * release_info - Frees allocated memory in the info_t struct.
 * @info: The address of the info_t struct.
 * @full: True if freeing all fields, false otherwise.
 */
void release_info(info_t *info, int full)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (full)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
