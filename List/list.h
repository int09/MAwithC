#ifndef	LIST_H
#define LIST_H

#include <stdlib.h>

/* Define a structure for linked list elements */
typedef struct ListElmt_
{
	void	*data;
	struct	ListElmt_	*next;
} ListElmt;

/* Define a structure for linked lists. */
typedef struct List_
{
	int		size;
	int		(*match)(const void *key1, const void *key2);
	void	(*destroy)(void *data);

	ListElmt	*head;
	List 		*tail;
} List;

/* Public Interface */

/*	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-
 list_init(List *list, void (*destroy)(void *data))
 Return Value : NULL
 Descriptions : Initial the List specified by arg"list". While invoke 
 				list_destroy to destroy the list, if arg"destroy" is 
				not NULL, destroy every element by func"destroy"
-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	*/
void 	list_init(List *list, void (*destroy)(void *data));

/*	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-
 list_destroy(List *list)
 Return Value : NULL
 Descriptions : Destroy the list which specified by arg"list", if 
 				the arg"destroy" is NOT NULL. When remove all elements
				invoke func"destroy" one time.
-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	*/
void	list_destroy(List *list);

/*	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-
 list_ins_next(List *list, ListElmt *element, const void *data)
 Return Value : If insert successed, return 0, else return -1
 Descriptions : Insert an element next to the arg"element", if arg"ele
 				ment" is NULL, insert it to the head of the list. the
				new element which pointed from a pointer by arg"data"
-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	*/
int	 	list_ins_next(List *list, ListElmt *element, const void *data);

/*	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-
 list_rem_next(List *list, ListElmt *element, void **data)
 Return Value : If remove successed, return 0, else return -1
 Descriptions : Remove the element which specificed by arg"element",
 				and the removed element is pointed by arg"data", it is
				a pointer point to a pointer which point to a void
				memory.
-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	*/
int		list_rem_next(List *list, ListElmt *element, void **data);

/*	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-
 These are some micro, they designed to the micro because the feature
 and complex degree not very high. You can recognize them by their 
 names. Use them effectively.
-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	*/
#define	list_size(list)		((list)->size)
#define	list_head(list)		((list)->head)
#define	list_tail(list)		((list)->tail)
#define	list_is_head(list, element)		((element) == (list)->head ? 1 : 0)
#define	list_is_tail(element)			((element)->next == NULL ? 1 : 0)
#define	list_data(element)	((element)->data)
#define	list_next(element)	((element)->next)

#endif
