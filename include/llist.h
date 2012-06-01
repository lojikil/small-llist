/*			Linked List v1.0
*
* This is a simple linked list library. It handles any type of data you want.
* By default it uses malloc() for new nodes and data. If you don't like this
* you can compile with LIB_USE_MMAP to use mmap() instead.
* If you want things to go smootly always use list_init() before using
* and list_destroy() after you are done !
* Be carefull that nothing accesses the list while executing list_destroy()
* For more info check out the example program included.
* 
* 			vlad: octal.s@gmail.com
*/


#ifndef LLIST_H
#define LLIST_H	1

/* list node typedef */
typedef struct {
	void *next;
	void *prev;
	void *data;
	size_t size;
} llist_t;

/* Inits the list. Run this first before using the list !
*
*  list - pointer to a list object
*  Returns: void */
extern void		list_init(llist_t *list);



/* Adds a new node at the end of the list
*
*  list - pointer to a list object. It can be the root node or any other.
*	  It will always add the new node after the last one.
*  data - pointer to user data.
*  size - data size
*
* Return:
*	  pointer to the new node or null on error.
*	  NOTE: If you are using large lists you can save the new node pointer
*		each time you add data and then pass this pointer as the root node
*		for the next add. This will improve speed because rather than starting
*		from the root node it will start from the last ! */
extern llist_t		*list_add(llist_t *list, void *data, size_t size);



/* Inserts a new node after the node pointed by "list"
*
*  list - pointer to a node (it can't be the last node)
*  data - pointer to user data
*  size - data size
*
* Return:
* 	pointer to he new node or null on error. */
extern llist_t		*list_insert(llist_t *list, void *data, size_t size);



/* Copy the data content of a node
*
*  list - pointer to node to get data from
*  data - pointer to buffer to store the data
*
* Return:
*	It will return a pointer to the next node. You can use this in a
*	loop to get many nodes fast.
*	Null on error or end of list */
extern llist_t		*list_get(llist_t *list, void *data);



/* Copy max n bytes from the data content of a node.
*  It works like list_get()
*
*  max_size - maximum bytes to copy */
extern llist_t		*list_nget(llist_t *list, void *data, size_t max_size);



/* Deletes the node "list"
*
*  list - pointer to node to be deleted
*
* Return:
*	the previous node or null on error */
extern llist_t		*list_del(llist_t *list);



/* Returns the data pointer in node "list"
*
*  list - pointer to a node
*
* Return:
*	null on error */
extern void		*list_get_data(llist_t *list);



/* Returns the data size from the node "list"
*
* list - pointer to a node
*
* Return:
*	0 on error */
extern size_t		list_get_size(llist_t *list);



/* Converts the node "list" to number of nodes after the root
*
* list - pointer to the root node
*
* Return:
*	the node number after root
*	0 on error  */
extern unsigned long	list_to_index(llist_t *list);

/* Converts the the number "index" to node on the list
*
*  list - pointer to the root node
*  index - the number of a node after the root
*
* Return:
*	pointer to node that is "index" after the root
*	null on error */
extern llist_t		*list_from_index(llist_t *list, unsigned long index);



/* Deletes all nodes and all data. Call this when you are done with the list.
*  No threads should access the list while executing this !
*
*  list - pointer to the root node
*
* Return:
*	void */
extern void		list_destroy(llist_t *list);

#endif
