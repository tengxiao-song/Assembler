#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_memory.h"


/*
 * adds a new node to linked list pointed to by head - MUST keep list in order by address
 */
int add_to_list (row_of_memory** head,
		 short unsigned int address,
		 short unsigned int contents)
{

	/* allocate memory for a single node */
	row_of_memory* temp = malloc(sizeof(row_of_memory));
	if (temp == NULL){return -1;}
	/* populate fields in newly allocated node w/ address&contents (it's ok if CONTENTS=NULL) */
	temp -> address = address;
	temp -> contents = contents;
	temp -> label = NULL;
	temp -> assembly = NULL;
	temp -> next = NULL;
	/* if head==NULL, node created is the new head of the list! */
	if (*head == NULL){
		*head = temp;
		return 0;
	}
	/* otherwise, traverse linked list until you reach an address before the address passed in */
	row_of_memory* pre = NULL;
	row_of_memory* curr = *head;
	while (curr != NULL && curr->address < address){
		pre = curr;
		curr = curr->next;
	}
	/* insert node into the list - perform necessary "surgery" on this list */
	if (pre == NULL){
		temp->next = *head;
		*head = temp;
	}else{
		temp->next = pre->next;
		pre->next = temp;
	}
	/* REMEMBER, .OBJ file can be out of ORDER!  Make certain to insert incoming node in order by address!! */

	/* return 0 for success, -1 if malloc fails */

	return 0 ;
}


/*
 * search linked list by address field, returns node if found
 */
row_of_memory* search_address (row_of_memory* head,
			       short unsigned int address )
{
	/* traverse linked list, searching each node for "address"  */
	while (head != NULL){
		if (head->address == address){
			return head;
		}
		head = head->next;
	}
	/* return pointer to node in the list if item is found */

	/* return NULL if list is empty or if "address" isn't found */

	return NULL ;
}

/*
 * search linked list by opcode field, returns node if found
 */
row_of_memory* search_opcode  (row_of_memory* head,
				      short unsigned int opcode  )
{
	/* traverse linked list until node is found with matching opcode
	   AND "assembly" field of node is empty */
	while (head != NULL){
		short unsigned int temp_opcode = head->contents >> 12;
		if (temp_opcode == opcode && head->assembly == '\0'){
			return head;
		}
		head = head->next;
	}
	/* return pointer to node in the list if item is found */

	/* return NULL if list is empty or if no matching nodes */

	return NULL ;
}


void print_list (row_of_memory* head )
{
	/* make sure head isn't NULL */
	if (head == NULL){return;}
	/* traverse linked list, print contents of each node */
	int width = 7;
	row_of_memory* curr = head;
	while (curr != NULL){
		if (curr->label != NULL && strlen(curr->label) > width){
			width = strlen(curr->label);												//get the longest label width for alignment
		}
		curr = curr->next;
	}
	/* print out a header */
	printf("%-*s    <address>    <contents>    <assembly>\n", width, "<label>");
	char temp_label[width+1];
	char temp_asm[20];
	while (head != NULL){
		if (head->label != NULL){
			strcpy(temp_label, head->label);									//printing the empty string if label does not exist
		}else {
			strcpy(temp_label, "");
		}
		if (head->assembly != NULL){
			strcpy(temp_asm, head->assembly);								//printing the empty assembly if label does not exist
		}else{
			strcpy(temp_asm, "");
		}
		printf("%-*s    %04X         %04X          %s\n", width,temp_label, head->address, head->contents, temp_asm);
		head = head->next;
	}
	return ;
}

/*
 * delete entire linked list
 */
void delete_list    (row_of_memory** head )
{
	/* delete entire list node by node */
	/* if no errors, set head = NULL upon deletion */
	row_of_memory* curr = *head;
	row_of_memory* next;
	while (curr != NULL){
		next = curr->next;
		if (curr->label != NULL){
			free(curr->label);
		}
		if (curr->assembly != NULL){
			free(curr->assembly);
		}
		free(curr);
		curr = next;
	}
	*head = NULL;
	/* return 0 if no error, -1 for any errors that may arise */
}
