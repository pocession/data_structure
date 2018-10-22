// linked_data.c
#include <stdlib.h>
#include <stdio.h>

//create a singly linked list struct to store values;
typedef struct sllist
{
    int val;
    struct sllist* next;
}node;

int create(struct sllist **head, int val)
{
    *head = malloc(sizeof(node)); //allocate memory chunk for head, it is a struct node by our definition
    if (!*head) //check whether head is NULL
    {
        fprintf(stderr, "Failed to create the list\n");
        return 1;
    }
    (*head) -> val = val; //initiate head with val, it is an int by our definition
    (*head) -> next = NULL; //head point to NULL, *next = NULL
    return 0;
}

int add_node(struct sllist **head, int val)
{
    struct sllist *current = *head; // create a node current, equeal to the head
    struct sllist *temp = NULL; // create a node temp = NULL
    do // create a loop to scan every elements unti it reach to the end of the linked list
    {
        temp = current;
        current = current -> next; //temp - current
    }
    while(current); //the last node is temp
    struct sllist *new_node = malloc(sizeof(node));
    if (! new_node)
    {
        fprintf(stderr, "Failed to add a new element\n");
        return 1;
    }
    new_node -> val = val; // create a new node new_node to save input values
    new_node -> next = NULL;
    temp -> next = new_node; //link the new_node with temp. now: temp - new_node
    return 0;
}

int delete_node(struct sllist **head, int val)
{
    struct sllist *current = *head;
    struct sllist *prev = NULL;
    do
    {
        if (current -> val == val)
        {
            break;
        }
        prev = current;
        current = current -> next;
    }
    while(current);
    // if the first element is deleted
    if (current == *head)
    {
        prev = *head;
        *head = current -> next;
        free(prev);
        return 0;
    }
    // if the last element is deleted
    if (current -> next == NULL)
    {
        prev -> next = NULL;
        free(current);
        return 0;
    }
    prev -> next = current -> next;
    free(current);
    return 0;
}

void print_node(struct sllist **head)
{
    struct sllist *current = *head;
    while(current)
    {
        printf("current data: %d, address:, %p\n", current -> val, current);
        current = current -> next;
    }
    return;
}

int free_node(struct sllist **head)
{
    struct sllist *current = *head;
    do
    {
        struct sllist *temp; //create a temp-current to scan all elements
        temp = current;
        current = current -> next;
        free(temp); //free memory form all elements
    }
    while(current);
    return 0;
}

int main()
{
    struct sllist *head;
    if (create(&head, 25) != 0)
    {
        fprintf(stderr, "Failed to create the first element\n");
        return EXIT_FAILURE;
    }
    for (int i = 30; i < 55; i += 5)
    {
        add_node(&head, i);
        puts("print the linked list:\n");
        print_node(&head);
    }
    delete_node(&head, 25);
    puts("\nNow delete the first element\n");
	print_node(&head);
	delete_node(&head, 50);
	puts("\nNow delete the last element\n");
	print_node(&head);
	delete_node(&head, 40);
    delete_node(&head, 35);
    puts("\nNow delete 40 and 35 from the linked list:\n"); //delete 40 and 35 from the linked list
    print_node(&head);
    printf("\n");

    free_node(&head); //release the memory used for the linked list

    return EXIT_SUCCESS;
}
