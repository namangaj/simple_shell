#include "shell.h"

/**
 * countNodes - counts the number of nodes in a linked list
 * @current: pointer to the first node
 *
 * Return: number of nodes
 */
size_t countNodes(const list_t *current)
{
	size_t count = 0;

	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}

/**
 * listToStrings - converts a linked list to an array of strings
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **listToStrings(list_t *head)
{
	list_t *node = head;
	size_t size = countNodes(head), index;
	char **stringsArray;
	char *string;

	if (!head || !size)
		return (NULL);

	stringsArray = malloc(sizeof(char *) * (size + 1));
	if (!stringsArray)
		return (NULL);

	for (index = 0; node; node = node->next, index++)
	{
		string = malloc(_strlen(node->str) + 1);
		if (!string)
		{
			while (index > 0)
				free(stringsArray[--index]);
			free(stringsArray);
			return (NULL);
		}

		string = _strcpy(string, node->str);
		stringsArray[index] = string;
	}
	stringsArray[index] = NULL;
	return (stringsArray);
}

/**
 * printListElements - prints all elements of a linked list
 * @current: pointer to the first node
 *
 * Return: number of elements
 */
size_t printListElements(const list_t *current)
{
	size_t count = 0;

	while (current)
	{
		_puts(convert_number(current->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(current->str ? current->str : "(nil)");
		_puts("\n");
		current = current->next;
		count++;
	}
	return (count);
}

/**
 * findNodeWithPrefix - finds a node whose string starts with a prefix
 * @startNode: pointer to list head
 * @prefix: string to match
 * @nextChar: the next character after prefix to match
 *
 * Return: matching node or NULL
 */
list_t *findNodeWithPrefix(list_t *startNode, char *prefix, char nextChar)
{
	char *p = NULL;

	while (startNode)
	{
		p = starts_with(startNode->str, prefix);
		if (p && ((nextChar == -1) || (*p == nextChar)))
			return (startNode);
		startNode = startNode->next;
	}
	return (NULL);
}

/**
 * getNodeIndex - gets the index of a node in the linked list
 * @head: pointer to list head
 * @targetNode: pointer to the target node
 *
 * Return: index of the target node or -1
 */
ssize_t getNodeIndex(list_t *head, list_t *targetNode)
{
	size_t index = 0;

	while (head)
	{
		if (head == targetNode)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
