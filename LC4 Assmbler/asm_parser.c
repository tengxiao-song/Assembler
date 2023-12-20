#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int read_asm_file (char* filename, char program [ROWS][COLS] ){
  FILE *my_file;
  my_file = fopen(filename, "r");                           //open file reading mode
  if (my_file == NULL){                                     //if file does not exist, return with error message
    printf("error2: read_asm_file() failed\n");
    return 2;
  }
  int index = 0;
  char line[COLS];
  while (fgets(line, COLS, my_file) != NULL){       //copy the file into line until EOF
    if (line[0] == ';'){                            //ignore lines starts with comments
      continue;
    }
    char* comment  = strchr(line, ';');             //ignore parts of lines after the comment
    if (comment != NULL){
      *comment = '\0';
    }
    char* newline = strchr(line, '\n');           //replace newline chracter with null
    if (newline != NULL) {
      *newline = '\0';
    }
    strcpy(program[index], line);                 //copy line into 2d array
    index ++;
  }
  fclose(my_file);                                          //close file
  return 0;
}

int parse_instruction 	(char* instr, char* instr_bin_str){           //check for opcode
  char* token = strtok(instr, " ,");
  if (strcmp(token,"ADD") == 0){
    if (parse_add(instr, instr_bin_str) != 0){return 3;}
  }else if (strcmp(token,"MUL") == 0){
    if (parse_mul(instr, instr_bin_str) != 0){return 3;}
  }else if (strcmp(token, "SUB") == 0){
    if (parse_sub(instr, instr_bin_str) != 0){return 3;}
  }else if (strcmp(token, "DIV") == 0){
    if (parse_div(instr, instr_bin_str) != 0){return 3;}
  }else if (strcmp(token, "AND") == 0){
    if (parse_and(instr, instr_bin_str) != 0){return 3;}
  }else if (strcmp(token, "OR") == 0){
    if (parse_or(instr, instr_bin_str) != 0){return 3;}
  }else if (strcmp(token, "XOR") == 0){
    if (parse_xor(instr, instr_bin_str) != 0){return 3;}
  }else{
    printf("error3: parse_instruction() failed.\n");
    return 3;
  }
  return 0;
}

int parse_add(char* instr, char* instr_bin_str ){
  strcpy(instr_bin_str, "0001");                                  //save opcode
  int count = 0;
  instr += 4;                                                     //forward 4 char
  instr_bin_str += 4;
  const char s[3] = " ,";                                         //set delimeter
  char* token = strtok(instr, " ,");                              //get token 
  while (token != NULL){                                          //loop
    count ++;                                                     //keep token count
    if (strlen(token) != 2 || *token != 'R' || count > 3){        //if token does not match format R# or more than 3 tokens, erros
      printf("error4: parse_add() failed.\n");
      return 4;
    }
    if (count == 2){                                              //if reach second token, advance three char
      instr_bin_str += 3;
    }else if (count == 3){                                        //if reach thrid token, advance three char, set sub-opcode, then advance three char again
      instr_bin_str += 3;
      strcpy(instr_bin_str, "000"); 
      instr_bin_str += 3;
    }
    if (parse_reg(*(token+1), instr_bin_str) != 0){return 4;}                        //save resgister #
    token = strtok(NULL, s);
  }
  if (count < 3){
    printf("error4: parse_add() failed.\n");                      //if count < 3, less than three reg, errors
    return 4;
  }
  return 0;
}

int parse_mul(char* instr, char* instr_bin_str ){
  strcpy(instr_bin_str, "0001");                                  //save opcode
  int count = 0;
  instr += 4;                                                     //forward 4 char
  instr_bin_str += 4;
  const char s[3] = " ,";                                         //set delimeter
  char* token = strtok(instr, " ,");                              //get token 
  while (token != NULL){                                          //loop
    count ++;                                                     //keep token count
    if (strlen(token) != 2 || *token != 'R' || count > 3){        //if token does not match format R# or more than 3 tokens, erros
      printf("error4: parse_mul() failed.\n");
      return 4;
    }
    if (count == 2){                                              //if reach second token, advance three char
      instr_bin_str += 3;
    }else if (count == 3){                                        //if reach thrid token, advance three char, set sub-opcode, then advance three char again
      instr_bin_str += 3;
      strcpy(instr_bin_str, "001"); 
      instr_bin_str += 3;
    }
    if (parse_reg(*(token+1), instr_bin_str) != 0){return 4;}                         //save resgister #
    token = strtok(NULL, s);
  }
  if (count < 3){
    printf("error4: parse_mul() failed.\n");                      //if count < 3, less than three reg, errors
    return 4;
  }
  return 0;
}

int parse_sub(char* instr, char* instr_bin_str ){
  strcpy(instr_bin_str, "0001");                                  //save opcode
  int count = 0;
  instr += 4;                                                     //forward 4 char
  instr_bin_str += 4;
  const char s[3] = " ,";                                         //set delimeter
  char* token = strtok(instr, " ,");                              //get token 
  while (token != NULL){                                          //loop
    count ++;                                                     //keep token count
    if (strlen(token) != 2 || *token != 'R' || count > 3){        //if token does not match format R# or more than 3 tokens, erros
      printf("error4: parse_sub() failed.\n");
      return 4;
    }
    if (count == 2){                                              //if reach second token, advance three char
      instr_bin_str += 3;
    }else if (count == 3){                                        //if reach thrid token, advance three char, set sub-opcode, then advance three char again
      instr_bin_str += 3;
      strcpy(instr_bin_str, "010"); 
      instr_bin_str += 3;
    }
    if (parse_reg(*(token+1), instr_bin_str) != 0){return 4;}                        //save resgister #
    token = strtok(NULL, s);
  }
  if (count < 3){
    printf("error4: parse_sub() failed.\n");                      //if count < 3, less than three reg, errors
    return 4;
  }
  return 0;
}

int parse_div(char* instr, char* instr_bin_str ){
  strcpy(instr_bin_str, "0001");                                  //save opcode
  int count = 0;
  instr += 4;                                                     //forward 4 char
  instr_bin_str += 4;
  const char s[3] = " ,";                                         //set delimeter
  char* token = strtok(instr, " ,");                              //get token 
  while (token != NULL){                                          //loop
    count ++;                                                     //keep token count
    if (strlen(token) != 2 || *token != 'R' || count > 3){        //if token does not match format R# or more than 3 tokens, erros
      printf("error4: parse_div() failed.\n");
      return 4;
    }
    if (count == 2){                                              //if reach second token, advance three char
      instr_bin_str += 3;
    }else if (count == 3){                                        //if reach thrid token, advance three char, set sub-opcode, then advance three char again
      instr_bin_str += 3;
      strcpy(instr_bin_str, "011"); 
      instr_bin_str += 3;
    }
    if (parse_reg(*(token+1), instr_bin_str) != 0){return 4;}                        //save resgister #
    token = strtok(NULL, s);
  }
  if (count < 3){
    printf("error4: parse_div() failed.\n");                      //if count < 3, less than three reg, errors
    return 4;
  }
  return 0;
}

int parse_and(char* instr, char* instr_bin_str ){
  strcpy(instr_bin_str, "0101");                                  //save opcode
  int count = 0;
  instr += 4;                                                     //forward 4 char
  instr_bin_str += 4;
  const char s[3] = " ,";                                         //set delimeter
  char* token = strtok(instr, " ,");                              //get token 
  while (token != NULL){                                          //loop
    count ++;                                                     //keep token count
    if (strlen(token) != 2 || *token != 'R' || count > 3){        //if token does not match format R# or more than 3 tokens, erros
      printf("error4: parse_and() failed.\n");
      return 4;
    }
    if (count == 2){                                              //if reach second token, advance three char
      instr_bin_str += 3;
    }else if (count == 3){                                        //if reach thrid token, advance three char, set sub-opcode, then advance three char again
      instr_bin_str += 3;
      strcpy(instr_bin_str, "000"); 
      instr_bin_str += 3;
    }
    if (parse_reg(*(token+1), instr_bin_str) != 0){return 4;}                        //save resgister #
    token = strtok(NULL, s);
  }
  if (count < 3){
    printf("error4: parse_and() failed.\n");                      //if count < 3, less than three reg, errors
    return 4;
  }
  return 0;
}

int parse_or(char* instr, char* instr_bin_str ){
  strcpy(instr_bin_str, "0101");                                  //save opcode
  int count = 0;
  instr += 3;                                                     //forward 3 char
  instr_bin_str += 4;
  const char s[3] = " ,";                                         //set delimeter
  char* token = strtok(instr, " ,");                              //get token 
  while (token != NULL){                                          //loop
    count ++;                                                     //keep token count
    if (strlen(token) != 2 || *token != 'R' || count > 3){        //if token does not match format R# or more than 3 tokens, erros
      printf("error4: parse_or() failed.\n");
      return 4;
    }
    if (count == 2){                                              //if reach second token, advance three char
      instr_bin_str += 3;
    }else if (count == 3){                                        //if reach thrid token, advance three char, set sub-opcode, then advance three char again
      instr_bin_str += 3;
      strcpy(instr_bin_str, "010"); 
      instr_bin_str += 3;
    }
    if (parse_reg(*(token+1), instr_bin_str) != 0){return 4;}                        //save resgister #
    token = strtok(NULL, s);
  }
  if (count < 3){
    printf("error4: parse_or() failed.\n");                      //if count < 3, less than three reg, errors
    return 4;
  }
  return 0;
}

int parse_xor(char* instr, char* instr_bin_str ){
  strcpy(instr_bin_str, "0101");                                  //save opcode
  int count = 0;
  instr += 4;                                                     //forward 4 char
  instr_bin_str += 4;
  const char s[3] = " ,";                                         //set delimeter
  char* token = strtok(instr, " ,");                              //get token 
  while (token != NULL){                                          //loop
    count ++;                                                     //keep token count
    if (strlen(token) != 2 || *token != 'R' || count > 3){        //if token does not match format R# or more than 3 tokens, erros
      printf("error4: parse_xor() failed.\n");
      return 4;
    }
    if (count == 2){                                              //if reach second token, advance three char
      instr_bin_str += 3;
    }else if (count == 3){                                        //if reach thrid token, advance three char, set sub-opcode, then advance three char again
      instr_bin_str += 3;
      strcpy(instr_bin_str, "011"); 
      instr_bin_str += 3;
    }
    if (parse_reg(*(token+1), instr_bin_str) != 0){return 4;}                        //save resgister #
    token = strtok(NULL, s);
  }
  if (count < 3){
    printf("error4: parse_xor() failed.\n");                      //if count < 3, less than three reg, errors
    return 4;
  }
  return 0;
}

int parse_reg(char reg_num, char* instr_bin_str){
  if (reg_num < '0' || reg_num > '7'){
    printf("error5: parse_reg() failed.\n");      //errors when access non exist register
    return 5;
  }
  switch (reg_num){                             //copy the register # into array case by case
    case '0':
      strcpy(instr_bin_str, "000");
      break;
    case '1':
      strcpy(instr_bin_str, "001");
      break;
    case '2':
      strcpy(instr_bin_str, "010");
      break;
    case '3':
      strcpy(instr_bin_str, "011");
      break;
    case '4':
      strcpy(instr_bin_str, "100");
      break;
    case '5':
      strcpy(instr_bin_str, "101");
      break;
    case '6':
      strcpy(instr_bin_str, "110");
      break;
    case '7':
      strcpy(instr_bin_str, "111");
      break;
  }
  return 0;
}

unsigned short int str_to_bin (char* instr_bin_str){
  unsigned short int res = (unsigned short int)strtol(instr_bin_str, NULL, 2);    //convert string to unsigned short
  if (res == 0){
    printf("error6: str_to_bin() failed.\n");                               //errors when strtol returns 0
    return 6;
  }  
  return res;
}

int write_obj_file(char* filename, unsigned short int program_bin[ROWS] ){
  char* temp = filename + strlen(filename) - 3;                               //change the last 3 letters to obj 
  strcpy(temp,"obj");
  FILE *the_file = fopen(filename, "wb");                                     //Open up that file for writing and in “BINARY” format
  if (the_file == NULL){
    printf("error7: write_obj_file() failed.\n");                             //if not enough space for write file, errors
    return 7;
  }
  unsigned short int header_value = 0xDECA;
  fwrite(&header_value, sizeof(unsigned short int), 1, the_file);           //Write out the first word in the header: 0xCADE with endian
  unsigned short int loading_address = 0x0000;
  fwrite(&loading_address, sizeof(unsigned short int), 1, the_file);        //program should be loaded at: 0x0000
  unsigned short int count = 0;
  while (program_bin[count] != '\0'){
    program_bin[count] = ((program_bin[count] >> 8) & 0x00FF) | ((program_bin[count] << 8) & 0xFF00);   //change the endianness
    count ++;                                                                                         //Count the number of rows
  }
  unsigned short int count_rev = ((count >> 8) & 0x00FF) | ((count << 8) & 0xFF00);         
  fwrite(&count_rev, sizeof(unsigned short int), 1, the_file);                               //write out <n>              
  fwrite(program_bin, sizeof(unsigned short int), count, the_file);                         // write out the <n> rows of data with endian
  fclose(the_file);
  return 0;
}
