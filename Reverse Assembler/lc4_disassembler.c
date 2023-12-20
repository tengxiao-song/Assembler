
#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>
#include <string.h>

int reverse_assemble (row_of_memory* memory)
{  
   while (search_opcode(memory, 1) != NULL){
      row_of_memory* curr = search_opcode(memory, 1);                      //search list for opcode=0001 & null assembly filed
      curr->assembly = malloc(sizeof(char)*20);                            //malloc space
      if (curr->assembly == NULL){return 3;}                               //if malloc fails return 
      unsigned short int sub_opcode = (curr->contents >> 3) & 0x07;        //get the sub_opcode content
      char res[20];
      unsigned short int reg_num;;
      switch(sub_opcode){                                                  //set the instructions depending on different sub_opcode
         case 0:
            strcpy(res,"ADD Rx, Rx, Rx");
            break;
         case 1:
            strcpy(res,"MUL Rx, Rx, Rx");
            break;
         case 2:
            strcpy(res,"SUB Rx, Rx, Rx");
            break;
         case 3:
            strcpy(res,"DIV Rx, Rx, Rx");
            break;
         default:
            strcpy(res,"ADD Rx, Rx, #");
      }
      reg_num = (curr->contents >> 9) & 0x07;                              //get the Rd reg num
      res[5] = '0' + reg_num;
      reg_num = (curr->contents >> 6) & 0x07;                              //get the Rs reg num
      res[9] = '0' + reg_num;
      if (sub_opcode <= 3){                                                //if not ADD IMM5, get the Rt reg num
         reg_num = curr->contents & 0x07;
         res[13] = '0' + reg_num;
      }else{
         int num = (curr->contents & 0x1F) >> 0;                           //for ADD IMM5, get the content
         int sign;
         int dec_num;
         if (((num >> 4) & 1)) {                                           //if it's a negative number, filp the bits and +1
            dec_num = -1*((~num & 0b01111) + 1);
         } else {
            dec_num = num & 0b01111;                                       //ignore the sign if postive
         };
         sprintf(&res[13], "%d", dec_num);                                 //write it to char array for strcpy
      }
      strcpy(curr->assembly, res);                                         //copy into assembly filed
   }
	return 0 ;
}
