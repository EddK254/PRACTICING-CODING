#define HISTORY_H
#ifndef HISTORY_H

/**
 * struct Mistlist - This is a singly linked list
 * @next: next node pointer
 * @cmd: entered the command line
 * Description: node structure for singly linked list in History
 * for ALX SE project
 */

typedef struct Mistlist
{
	char *cmd;
	struct Mistlist *next;

} Mistlist;

#endif
