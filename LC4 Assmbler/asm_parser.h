#define ROWS 100
#define COLS 255

int read_asm_file 		(char* filename, char program [ROWS][COLS] ) ;
int parse_instruction 	(char* instr, char* instr_bin_str) ;
int parse_reg 			(char reg_num, char* instr_bin_str) ;
int parse_add 			(char* instr, char* instr_bin_str ) ;
int parse_mul 			(char* instr, char* instr_bin_str ) ;
int parse_sub 			(char* instr, char* instr_bin_str ) ;
int parse_div 			(char* instr, char* instr_bin_str ) ;
int parse_and 			(char* instr, char* instr_bin_str ) ;
int parse_or 			(char* instr, char* instr_bin_str ) ;
int parse_xor 			(char* instr, char* instr_bin_str ) ;
unsigned short int str_to_bin (char* instr_bin_str) ;
int write_obj_file 			  (char* filename, unsigned short int program_bin[ROWS] ) ;
