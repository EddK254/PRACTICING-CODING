#define HISTORY_H
#ifndef HISTORY_H

/**
 * struct HistList - This is a singly linked list
 * @next: next node pointer
 * @cmd: entered the command line
 * Description: node structure for singly linked list in History
 * for ALX SE project
 */

typedef struct HistList
{
	char *cmd;
	struct HistList *next;

} HistList;

#endif
