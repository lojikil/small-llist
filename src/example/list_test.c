/*		Linked List v1.0 Example Program
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

#define DATA_SIZE	100

/* Prints the menu */
void	print_menu() {

	printf("\n\n\n-- Linked list example program --\n");
	printf("add      : adds element to the list\n");
	printf("insert   : instert element to the list\n");
	printf("del      : deletes element from the list\n");
	printf("show     : prints the list\n");
	printf("exit     : terminates the program\n");
	printf(": ");

	return;
}

/* Prints the list */
void	print_list(llist_t *list) {

	llist_t *node;
	char user_data[DATA_SIZE];

	node = list;
	while (node != NULL) {
		memset(user_data, 0, DATA_SIZE);
		printf("\n\nNode (%p):\n", node);
		printf("next = %p\n", node->next);
		printf("prev = %p\n", node->prev);

		node = list_get(node, user_data);
		printf("DATA: %s\n\n", user_data);
	}

	return;
}

int	main() {

	int num;
	int is_running;
	llist_t list;
	llist_t *node, *last;
	void *ptr;

	char cmd[20];
	char user_data[DATA_SIZE];

	/* init the list */
	list_init(&list);

	is_running = 1;
	while (is_running) {
		print_menu();
		scanf("%s", cmd);

		if (strcmp(cmd, "exit") == 0)
			break;

		if (strcmp(cmd, "show") == 0) {
			print_list(&list);
			continue;
		}

		if (strcmp(cmd, "add") == 0) {
			printf("\nEnter some data: ");
			scanf("%s", user_data);

			ptr = list_add(&list, user_data, strlen(user_data) + 1); // +1 to include the 0 byte
			printf("\nNew node created at: %p\n", ptr);
			continue;
		}

		if (strcmp(cmd, "insert") == 0) {
			printf("Enter a number after the first node to be inserted: ");
			scanf("%i", &num);
			printf("Enter some data to be inserted: ");
			scanf("%s", user_data);

			ptr = list_insert( list_from_index(&list, num), user_data, strlen(user_data) + 1); 
			printf("\nNew node created at: %p\n", ptr);
			continue;
		}

		if (strcmp(cmd, "del") == 0) {
			printf("Enter a number after the first node to be deleted: ");
			scanf("%i", &num);

			ptr = list_del( list_from_index(&list, num)); 
			printf("Deleted after node %p\n", ptr);
			continue;
		}

	}

	printf("Destroing list...\n");

	/* destroy the list */
	list_destroy(&list);

	return 0;

}
