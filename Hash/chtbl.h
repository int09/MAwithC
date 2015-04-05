#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>

#include "./List/list.h"

/* Define a structure for chained hash tables. */
typedef struct CHTbl_
{
	int		buckets;

	/* A hash function pointer. */
	int		(*h)(const void *key);
	int		(*match)(const void *key1, const void *key2);
	void	(*destroy)(void *data);

	int		size;
	/* This a a chained table, use Linked List. */
	List	*table;

} CHTbl;

/* Public Interface. */
int		chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key),
			int (*mathc)(const void *key1, const void *key2), void (*destroy)(void *data));

void	chtbl_destroy(CHTbl *htbl);

int		chtbl_insert(CHTbl *htbl, const void *data);
int		chtbl_remove(CHTbl *htbl, void **data);

int		chtbl_lookup(CHTbl *htbl, void **data);

#define	chtbl_size(htbl)	((htbl)->size)

#endif
