#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_memory.h"
#include "lc4_loader.h"
#include "lc4_disassembler.h"

/* program to mimic pennsim loader and disassemble object files */

int main (int argc, char** argv) {

	/**
	 * main() holds the linked list &
	 * only calls functions in other files
	 */

	/* step 1: create head pointer to linked list: memory 	*/
	row_of_memory* memory = NULL ;


	/* step 2: determine filename, then open it		*/
	/*   TODO: extract filename from argv, pass it to open_file() */
	FILE* file;
	if (argc == 2 && strcmp(argv[1]+strlen(argv[1])-4,".obj") == 0){
			file = open_file(argv[1]);
	}else{
		printf("error1: usage: ./lc4 %s\n",argv[1]);					//if can't open file print error return 1 
		return 1;
	}
	if (file == NULL){
		printf("error1: usage: ./lc4 %s\n",argv[1]);
		return 1;
	}

	/* step 3: call function: parse_file() in lc4_loader.c 	*/
	/*   TODO: call function & check for errors		*/
	if (parse_file(file, &memory)!= 0){
		delete_list(&memory);
		printf("error2: parse_file()\n");
		return 2;								//if error & free mem and return 2
	}

	/* step 4: call function: reverse_assemble() in lc4_disassembler.c */
	/*   TODO: call function & check for errors		*/
	if (reverse_assemble(memory)!=0){
		delete_list(&memory);
		printf("error3: reverse_assemble()\n");
		return 3;
	}

	/* step 5: call function: print_list() in lc4_memory.c 	*/
	/*   TODO: call function 				*/
	print_list(memory);
	/* step 6: call function: delete_list() in lc4_memory.c */
	/*   TODO: call function & check for errors		*/
	delete_list(&memory);

	/* only return 0 if everything works properly */
	return 0 ;
}
