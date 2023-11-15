#include "shell.h"

/**
 * generateHistoryFilePath - creates the path for the history file
 * @info: parameter struct
 *
 * Return: allocated string containing the history file path
 */
char *generateHistoryFilePath(info_t *info)
{
	char *homeDir = _getenv(info, "HOME=");
	if (!homeDir)
		return (NULL);

	char *historyFilePath = malloc(sizeof(char) * (_strlen(homeDir) + _strlen(HIST_FILE) + 2));
	if (!historyFilePath)
		return (NULL);

	historyFilePath[0] = '\0';
	_strcpy(historyFilePath, homeDir);
	_strcat(historyFilePath, "/");
	_strcat(historyFilePath, HIST_FILE);

	return (historyFilePath);
}

/**
 * saveHistoryToFile - writes history to a file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int saveHistoryToFile(info_t *info)
{
	ssize_t fileDescriptor;
	char *filename = generateHistoryFilePath(info);
	list_t *historyNode = NULL;

	if (!filename)
		return (-1);

	fileDescriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fileDescriptor == -1)
		return (-1);

	for (historyNode = info->history; historyNode; historyNode = historyNode->next)
	{
		_putsfd(historyNode->str, fileDescriptor);
		_putfd('\n', fileDescriptor);
	}

	_putfd(BUF_FLUSH, fileDescriptor);
	close(fileDescriptor);

	return (1);
}

/**
 * loadHistoryFromFile - reads history from a file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int loadHistoryFromFile(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fileDescriptor, readLength, fileSize = 0;
	struct stat fileStat;
	char *fileBuffer = NULL, *filename = generateHistoryFilePath(info);

	if (!filename)
		return (0);

	fileDescriptor = open(filename, O_RDONLY);
	free(filename);

	if (fileDescriptor == -1)
		return (0);

	if (!fstat(fileDescriptor, &fileStat))
		fileSize = fileStat.st_size;

	if (fileSize < 2)
		return (0);

	fileBuffer = malloc(sizeof(char) * (fileSize + 1));
	if (!fileBuffer)
		return (0);

	readLength = read(fileDescriptor, fileBuffer, fileSize);
	fileBuffer[fileSize] = '\0';

	if (readLength <= 0)
		return (free(fileBuffer), 0);

	close(fileDescriptor);

	for (i = 0; i < fileSize; i++)
	{
		if (fileBuffer[i] == '\n')
		{
			fileBuffer[i] = '\0';
			buildHistoryList(info, fileBuffer + last, linecount++);
			last = i + 1;
		}
	}

	if (last != i)
		buildHistoryList(info, fileBuffer + last, linecount++);

	free(fileBuffer);

	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);

	renumberHistory(info);

	return (info->histcount);
}

/**
 * buildHistoryList - adds an entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	addNodeEnd(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumberHistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}
