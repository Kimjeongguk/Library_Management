#include "common.h"
#include "menu.h"
#include "client.h"
#include "book.h"
/* 전역변수  */

Client **client;
Book **book;
Borrow **borrow;
int numofborrow=0;
int numofbook=0;
int numofclient=0;

int main()
{
	MainMenu m;
	client=(Client**)malloc(sizeof(Client*));
	book=(Book**)malloc(sizeof(Book*));
	borrow=(Borrow**)malloc(sizeof(Borrow*));
	
	borrowload();
	loadbook();
	LoadDatafromFile();
	while((m=MainMenuShow())!=QUIT){
		
		
		
		switch(m){
			case JOIN:
				  if(numofclient==0){
					client[0]=(Client*)malloc(sizeof(Client));
				  }
				  else {
					client=(Client**)realloc(client, (numofclient+1)*sizeof(Client*));
				  }
				  client[numofclient++]=join();
				  
			      break;
			case LOGIN:
			          printf("로그인\n"); 
			          login();
			          break;
			default: break;
		}
		
		printf("\n----------------------\n");
		clientListAll();
	}
	
	return 0;
}
