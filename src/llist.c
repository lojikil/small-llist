#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

/* Memory allocation methods */

#ifdef LIB_USE_MMAP

#include <sys/mman.h>

#endif /* LIB_USE_MMAP */


/* Memory allocation wraper call */

static void    *_memalloc(size_t size) {

        void *p = NULL;

        if (size == 0)
                return NULL;

#ifdef LIB_USE_MMAP
        p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (p == MAP_FAILED)
                p = NULL;
#else
        p = malloc(size);
#endif /* LIB_USE_MMAP */


        return p;
}


/* Memory free wraper call */

static void    _memfree(void *ptr, size_t size) {

        if (ptr == NULL)
                return;

#ifdef LIB_USE_MMAP
        munmap(ptr, size);
#else
        free(ptr);
#endif /* LIB_USE_MMAP */
        return;
}


/* Inits the list */

void	list_init(llist_t *list) {

	list->next = NULL;
	list->prev = NULL;
	list->data = NULL;
	list->size = 0;

	return;
}


/* Adds a node to the list
*  Returns a pointer to the new node
*/
llist_t	*list_add(llist_t *list, void *data, size_t size) {

	llist_t *node;
	llist_t *new;

	if ((list == NULL) || (data == NULL))
		return NULL;

	node = list;

	while (node->next != NULL)
		node = node->next;

	if ((node->prev == NULL) && (node->data == NULL))
		new = node;
	else
		new = _memalloc(sizeof(llist_t));

	new->data = _memalloc(size);
	new->size = size;
	new->next = NULL;
	memcpy(new->data, data, size);

	if (new != list)  {
		node->next = new;
		new->prev = node;
	}
	
	return new;
}

/* Inserts a new node after the node "list"
*  "list" can be any node including the root
*/
llist_t *list_insert(llist_t *list, void *data, size_t size) {

	llist_t *new;
	llist_t *next;

	if ((list == NULL) || (data == NULL) || (list->next == NULL))
		return NULL;

	next = list->next;

	new = _memalloc(sizeof(llist_t));
	new->data = _memalloc(size);
	new->size = size;
	memcpy(new->data, data, size);

	new->next = next;
	new->prev = list;

	list->next = new;
	next->prev = new;

	return new;
}

/* Copy node's data to user buffer
*  Returns the next node
*/
llist_t *list_get(llist_t *list, void *data) {

	if ((list == NULL) || (data == NULL))
		return NULL;

	memcpy(data, list->data, list->size);

	return list->next;
}

/* Copy max n bytes from node's data to user buffer
*  Returns next node
*/
llist_t *list_nget(llist_t *list, void *data, size_t max_size) {

	size_t size;

	if ((list == NULL) || (data == NULL))
		return NULL;

	if (max_size == 0)
		size = list->size;
	else
		size = max_size > list->size ? list->size : max_size;

	memcpy(data, list->data, size);

	return list->next;
}

/* Deletes the node "list"
*  "list" can be any node including the root
*  Returns the previous node
*/
llist_t*	list_del(llist_t *list) {

	llist_t *node, *node2;
	llist_t *next;
	llist_t *prev;

	if (list == NULL)
		return;

	node = list;
	next = node->next;
	prev = node->prev;

	/* check if this is the root node */

	if (list->prev == NULL) {
		_memfree(list->data, list->size);
		if (list->next != NULL) {
			memcpy(list, next, sizeof(llist_t));
			list->prev = NULL;
			node2 = list->next;
			if (node2 != NULL)
				node2->prev = list;
			_memfree(next, sizeof(llist_t));
			
		}
		return NULL;
	}

	prev->next = next;
	if (list->next != NULL)
		next->prev = prev;

	_memfree(node->data, node->size);
	_memfree(node, sizeof(llist_t));

	return prev;
}

/* Returns the data pointer of the node "list" */
void	*list_get_data(llist_t *list) {

	if (list == NULL)
		return NULL;

	return list->data;
}

/* Returns data size of the node list */
size_t	list_get_size(llist_t *list) {

	if (list == NULL)
		return 0;

	return list->size;
}

/* Returns the number of node "list" after the root node */
unsigned long list_to_index(llist_t *list) {

	unsigned long count;
	llist_t *node;

	if (list == NULL)
		return 0;

	count = 1;
	node = list;

	while (node->prev != NULL) {
		node = node->prev;
		count++;
	}
	
	return count;
}

/* Returns the node address from "index" after the root node */
llist_t	*list_from_index(llist_t *list, unsigned long index) {

	unsigned long count;
	llist_t *node;

	if ((list == NULL) || (index == 0))
		return NULL;

	if (index == 1)
		return list;

	node = list;
	count = 1;

	while (node->next != NULL) {
		if (count == index)
			return node;
		count++;
		node = node->next;
	}

	if (count == index)
		return node;

	return NULL;
}
	

/* Destroy all nodes */
void	list_destroy(llist_t *list) {

	llist_t *node;
	llist_t *next;

	if (list == NULL)
		return;

	node = list;

	while (node != NULL) {
#ifdef DEBUG
		printf("Del: %s\n", node->data);
#endif
		next = node->next;
		_memfree(node->data, node->size);
		node->data = NULL;
		node->next = NULL;
		node->prev = NULL;
		node->size = 0;
		node = next;
	}

	return;
}
