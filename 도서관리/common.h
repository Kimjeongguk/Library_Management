#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TRUE 1
#define FALSE 0

typedef struct client{
	int no;
	char pa[100];
	char na[100];
	char ad[500];
	int po;
}Client;

typedef struct{
	char bo[100];
	char pu[100];
	char au[100];
	char ISBN[14];
	char pl[100];
	int no; 
	char lo;
}Book;
typedef struct{
	char id;
	int no;
	char today[200];
	char outday[200];
}Borrow;
#endif
 
