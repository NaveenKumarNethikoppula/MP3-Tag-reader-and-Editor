#ifndef HEADER
#define HEADER

#include<stdio.h>
#include<string.h>


typedef enum {
    e_failure,
    e_success,
}Status;

Status tag_reader(FILE *fptr,char * version);
Status copy_remain(FILE * src, FILE *dest,char * user_tag,char * user_string);
#endif
