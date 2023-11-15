#include "shell.h"

/**
 * customMemset - Fills memory with a constant byte
 * @memory: The pointer to the memory area
 * @byte: The byte to fill *memory with
 * @size: The amount of bytes to be filled
 *
 * Return: A pointer to the memory area @memory
 */
char *customMemset(char *memory, char byte, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		memory[i] = byte;
	return (memory);
}

/**
 * freeStringArray - Frees an array of strings
 * @stringArray: The array of strings
 */
void freeStringArray(char **stringArray)
{
	char **temp = stringArray;

	if (!stringArray)
		return;
	while (*stringArray)
		free(*stringArray++);
	free(temp);
}

/**
 * customRealloc - Reallocates a block of memory
 * @prevPtr: Pointer to the previous malloc'ated block
 * @oldSize: Byte size of the previous block
 * @newSize: Byte size of the new block
 *
 * Return: Pointer to the old block if reallocation fails, otherwise, a
 * pointer to the new block
 */
void *customRealloc(void *prevPtr, unsigned int oldSize, unsigned int newSize)
{
	char *newPtr;

	if (!prevPtr)
		return (malloc(newSize));
	if (!newSize)
		return (free(prevPtr), NULL);
	if (newSize == oldSize)
		return (prevPtr);

	newPtr = malloc(newSize);
	if (!newPtr)
		return (prevPtr);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		newPtr[oldSize] = ((char *)prevPtr)[oldSize];
	free(prevPtr);
	return (newPtr);
}
