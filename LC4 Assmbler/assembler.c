#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int main(int argc, char** argv) {
	if (argc != 2){
		printf("error1: usage: ./assembler <assembly_file.asm>\n");				//check whether the # of arg is 2, if not return immediately
		return 1;
	}
	int length = strlen(argv[1]);
	if (strcmp(argv[1] + length -4, ".asm") != 0){
		printf("error1: usage: ./assembler <assembly_file.asm>\n");			//check whether the input file is an .asm file, if not return immediately
		return 1;
	}
	char* filename = argv[1] ;					// name of ASM file
	char  program [ROWS][COLS] ; 			// ASM file line-by-line
	if (read_asm_file (filename, program) != 0){return 1;} 
	char  program_bin_str [ROWS][17] ; 		// instructions converted to a binary string
	int row = 0;
	unsigned short int program_bin [ROWS] ; 													// instructions in binary (HEX)
	while (program[row][0] != '\0'){																	//loop through the instruction and save the binary 
		if (parse_instruction(program[row], program_bin_str[row]) != 0){return 1;} 	
		program_bin[row] = str_to_bin (program_bin_str[row]);						//convert binary to hex
		row++;
	}
	if (write_obj_file(filename, program_bin) != 0){return 1;}														//write the obj file
	return 0;
}
