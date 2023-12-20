#include <stdio.h>
#include "lc4_memory.h"
#include <stdlib.h>
#include <string.h>

/* declarations of functions that must defined in lc4_loader.c */


/**
 * opens up name of the file passed in, returns a pointer
 * to the open file
 *
 * returns the FILE pointer upon success, else NULL.
 */
FILE* open_file(char* file_name){
   FILE* file_ptr = fopen(file_name, "rb");           //read binary mode
   return file_ptr;
}



/**
 * parses the given input file into an ordered (by memory address)
 * linked list with the passed in row_of_memory as the head.
 *
 * returns 0 upon successs, non-zero if an error occurs.
 */
int parse_file (FILE* my_obj_file, row_of_memory** memory){
   short unsigned int type;
   short unsigned int addr;
   short unsigned int n;
   short unsigned int content;
   row_of_memory* node;
   while (fread(&type,sizeof(type),1,my_obj_file)==1){            //looks for and read header field
      fread(&addr,sizeof(addr),1,my_obj_file);                    
      addr = (addr << 8) | ((addr >> 8) & 0xFF);                  //read address field with endianess
      fread(&n,sizeof(n),1,my_obj_file);
      n = (n << 8) | ((n >> 8) & 0xFF);                           //read n field with endianess
      if (type == 0xDECA || type == 0xDADA){                      //check header = CODE/DATA?
         for (int i = 0; i < n; i++){                             //read n word body with endianess
            fread(&content,sizeof(content),1,my_obj_file);
            content = (content << 8) | ((content >> 8) & 0xFF);
            node = search_address(*memory, addr+i);               //check if node exists,
            if (node == NULL){
               add_to_list(memory, addr+i, content);               //if not, add new node
            }else{
               node->contents = content;                           //if yes, modify existing node
            }
         }
      }else if (type == 0xB7C3){                                  //if header = symbol, read n byte body 
         node = search_address(*memory, addr);                    //search list for address
         if (node == NULL){
            add_to_list(memory, addr, 0);  
            node = search_address(*memory, addr);                 //if node does not exist, add new node
         }
         node->label = malloc(sizeof(char)*n+1);
         for (int i = 0; i < n; i++) {                            //update node to have ascii label from body
            fread(&node->label[i], 1,1,my_obj_file);
         }
         node->label[n] = '\0';                                   //include null                
      }
   }
   if (fclose(my_obj_file)!=0){                                   //if close file error, print error
      return 2;
   }
   return 0;
}
