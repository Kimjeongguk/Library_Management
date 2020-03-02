#include "admin.h"
#include "book.h"
#include "borrow.h"

extern Book**book;
extern numofbook;

extern Client **client;
extern int numofclient;

extern Borrow **borrow;
extern int numofborrow;
void admin(){
	int ch;
	
	while(ch!=7){
		printf(">>=============<<\n");
		printf("1.도서등록\n");
		printf("2.도서삭제\n");
		printf("3.도서대여\n");
		printf("4.도서반납\n");
		printf("5.도서검색\n");
		printf("6.회원목록\n");
		printf("7.로그아웃\n");
		printf("8.프로그램종료\n");
		printf(">>=============<<\n");
		printf(">>");
		scanf("%d",&ch);
		switch(ch){
			case 1:
				if(numofbook==0){
					book[0]=(Book*)malloc(sizeof(Book));
				}
				else{
					book=(Book**)realloc(book,(numofbook+1)*sizeof(Book*));
				}
				book[numofbook++]=join1();
				break;
				
			case 2:bookdelete();
				break;
			case 3:
				if(numofbook==0){
					borrow[0]=(Borrow*)malloc(sizeof(borrow));
				}
				else{
					borrow=(Borrow**)realloc(borrow,(numofborrow+1)*sizeof(Borrow*));
				}
				inbook();
				break;
			case 4:outbook();
				break;
			case 5:search();
				break;
			case 6:look();
				break;
			case 7:break;
			case 8:exit(1);
				break; 
			default :break;			
		}
		booklist();
		borrowlist();
	}
}
void bookdelete(){
	int i,a;
	while(a!=3){
		printf("1.도서명검색\n");
		printf("2.ISBN 검색\n");
		printf("3.나가기\n");
		scanf("%d",&a);
		switch(a){
			case 1:bookbo();
				break;
			case 2:bookISBN();
				break;
			case 3:break;
			default:break;
		}
	}
}
void bookbo(){
	char a[50],b;
	int i,j,c;
	c=0;
	printf("도서명입력>>");
	scanf("%s",a);
	for(i=0; i<numofbook; i++){
		if(strcmp(book[i]->bo,a)==0){
			c++;
			printf("|%s|%s|%s|%s|%s|%d|%c|\n",book[i]->bo,book[i]->pu,book[i]->au,book[i]->pl,book[i]->ISBN,book[i]->no,book[i]->lo);
			printf("삭제하시겠습니까?(y/n)");
			fflush(stdin);
			scanf("%c",&b);
			if(b=='y'&&book[i]->lo=='Y'){
				for(j=i; j<numofbook-1; j++){
					book[j]=book[j+1];
					book[j]->no--;
				}			
				numofbook--;
				break;
			}
				else if(b=='y'&&book[i]->lo=='N'){
				printf("삭제불가.\n");
			}
			else if(b!='n'){printf("잘못입력!\n");}
		}
	}
	if(c==0){
		printf("도서명을 잘못입력하였거나 도서가 없습니다.\n");
	}
}
void bookISBN(){
	char b;
	int a, i,j,c;
	c=0;
	printf("ISBN입력>>");
	scanf("%d",&a);
	for(i=0; i<numofbook; i++){
		
		if(atoi(book[i]->ISBN)==a){
		     printf(">> %s,  %d\n\n",book[i]->ISBN,atoi(book[i]->ISBN));
			c++;
			printf("|%s|%s|%s|%s|%s|%d|%c|\n",book[i]->bo,book[i]->pu,book[i]->au,book[i]->pl,book[i]->ISBN,book[i]->no,book[i]->lo);
			printf("삭제하시겠습니까?(y/n)");
			fflush(stdin);
			scanf("%c",&b);
			if(b=='y'&&book[i]->lo=='Y'){
				for(j=i; j<numofbook-1; j++){
					book[j]=book[j+1];
					book[j]->no--;
				}			
				numofbook--;
				break;
			}
				else if(b=='y'&&book[i]->lo=='N'){
				printf("삭제불가.\n");
			}
			else if(b!='n'){printf("잘못입력!\n");}
		}
	}
	if(c==0){
		printf("도서명을 잘못입력하였거나 도서가 없습니다.\n");
	}
}
void look(){
	int a,i,c;
	char b[50];
	
	while(a!=4){
		printf("1.이름검색\n");
		printf("2.학번검색\n");
		printf("3.전체검색\n");
		printf("4.나가기\n");
		printf(">>");
		scanf("%d",&a);
		switch(a){
			case 1:printf(">>");
					scanf("%s",b);
					for(i=0;i<numofclient;i++){
						if(strcmp(client[i]->na,b)==0){
							printf("학번:%d\n이름:%s\n주소:%s\n전화번호:%d\n",client[i]->no,client[i]->na,client[i]->ad,client[i]->po);
						}
					}
				break;
			case 2:printf(">>");
					scanf("%d",&c);
					for(i=0;i<numofclient;i++){
						if(client[i]->no==c){
							printf("학번:%d\n이름:%s\n주소:%s\n전화번호:%d\n",client[i]->no,client[i]->na,client[i]->ad,client[i]->po);
						}
					}
				break;
			case 3:for(i=0;i<numofclient;i++){
						printf("학번:%d  이름:%s  주소:%s  전화번호:%d\n",client[i]->no,client[i]->na,client[i]->ad,client[i]->po);
					}
				break;
			case 4:break;
			default:break;
		}
	} 
}
