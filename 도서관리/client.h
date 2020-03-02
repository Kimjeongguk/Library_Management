#ifndef CLIENT_H
#define CLIENT_H

#include "common.h"



Client *join();
void clientListAll();
void LoadDatafromFile();
Client *tokenData(char *);
int isIdcheck(int);
int islogincheck(char*,char*);
int master(char*,char*);
void login();
int menushow();
typedef enum{ BOOK = 1, LIST, INFORMATION, UNREGISTER, LOGOUT, OUT }Servis;
void revise(char*);
void mybook(char*);
void pdelete(char*);
#endif
