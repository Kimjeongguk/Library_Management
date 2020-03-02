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
		printf("1.�������\n");
		printf("2.��������\n");
		printf("3.�����뿩\n");
		printf("4.�����ݳ�\n");
		printf("5.�����˻�\n");
		printf("6.ȸ�����\n");
		printf("7.�α׾ƿ�\n");
		printf("8.���α׷�����\n");
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
		printf("1.������˻�\n");
		printf("2.ISBN �˻�\n");
		printf("3.������\n");
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
	printf("�������Է�>>");
	scanf("%s",a);
	for(i=0; i<numofbook; i++){
		if(strcmp(book[i]->bo,a)==0){
			c++;
			printf("|%s|%s|%s|%s|%s|%d|%c|\n",book[i]->bo,book[i]->pu,book[i]->au,book[i]->pl,book[i]->ISBN,book[i]->no,book[i]->lo);
			printf("�����Ͻðڽ��ϱ�?(y/n)");
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
				printf("�����Ұ�.\n");
			}
			else if(b!='n'){printf("�߸��Է�!\n");}
		}
	}
	if(c==0){
		printf("�������� �߸��Է��Ͽ��ų� ������ �����ϴ�.\n");
	}
}
void bookISBN(){
	char b;
	int a, i,j,c;
	c=0;
	printf("ISBN�Է�>>");
	scanf("%d",&a);
	for(i=0; i<numofbook; i++){
		
		if(atoi(book[i]->ISBN)==a){
		     printf(">> %s,  %d\n\n",book[i]->ISBN,atoi(book[i]->ISBN));
			c++;
			printf("|%s|%s|%s|%s|%s|%d|%c|\n",book[i]->bo,book[i]->pu,book[i]->au,book[i]->pl,book[i]->ISBN,book[i]->no,book[i]->lo);
			printf("�����Ͻðڽ��ϱ�?(y/n)");
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
				printf("�����Ұ�.\n");
			}
			else if(b!='n'){printf("�߸��Է�!\n");}
		}
	}
	if(c==0){
		printf("�������� �߸��Է��Ͽ��ų� ������ �����ϴ�.\n");
	}
}
void look(){
	int a,i,c;
	char b[50];
	
	while(a!=4){
		printf("1.�̸��˻�\n");
		printf("2.�й��˻�\n");
		printf("3.��ü�˻�\n");
		printf("4.������\n");
		printf(">>");
		scanf("%d",&a);
		switch(a){
			case 1:printf(">>");
					scanf("%s",b);
					for(i=0;i<numofclient;i++){
						if(strcmp(client[i]->na,b)==0){
							printf("�й�:%d\n�̸�:%s\n�ּ�:%s\n��ȭ��ȣ:%d\n",client[i]->no,client[i]->na,client[i]->ad,client[i]->po);
						}
					}
				break;
			case 2:printf(">>");
					scanf("%d",&c);
					for(i=0;i<numofclient;i++){
						if(client[i]->no==c){
							printf("�й�:%d\n�̸�:%s\n�ּ�:%s\n��ȭ��ȣ:%d\n",client[i]->no,client[i]->na,client[i]->ad,client[i]->po);
						}
					}
				break;
			case 3:for(i=0;i<numofclient;i++){
						printf("�й�:%d  �̸�:%s  �ּ�:%s  ��ȭ��ȣ:%d\n",client[i]->no,client[i]->na,client[i]->ad,client[i]->po);
					}
				break;
			case 4:break;
			default:break;
		}
	} 
}
