#include "client.h"
#include "admin.h"


extern Client **client;
extern int numofclient;

extern Borrow **borrow;
extern int numofborrow;

extern Book **book;
extern numofbook;

int  isIdcheck(int a){
	int i;
	
	for(i=0; i<numofclient-1;i++){
		if(client[i]->no==a){
			return TRUE;	
		}
	}
	return FALSE;	
}

Client *join(){
    Client *pClient;
    int i;
    pClient=(Client*)malloc(sizeof(Client));
   	
   	while(1){
		printf("학번을 입력하세요:");
		fscanf(stdin, "%d",&pClient->no);
		
		if(!isIdcheck(pClient->no)){
			printf("가입가능\n");
			break;
		}
		else {
			printf("가입한 학번있음\n");
		}
	}
	fflush(stdin);
	printf("비밀번호를 입력하세요:");
	fgets(pClient->pa, sizeof(pClient->pa), stdin);
	pClient->pa[strlen(pClient->pa)-1]='\0';
	
	fflush(stdin);
	printf("이름을 입력하세요:");
	fgets(pClient->na, sizeof(pClient->na), stdin); 
	pClient->na[strlen(pClient->na)-1]='\0';
	
	printf("주소를 입력하세요:");
	fflush(stdin);
	fgets(pClient->ad,sizeof(pClient->ad),stdin); 
	pClient->ad[strlen(pClient->ad)-1]='\0';

	printf("전화번호를 입력하세요:");
	fscanf(stdin, "%d",&pClient->po);
	
	return pClient;
}

void clientListAll(){
	int i,j;
	Client *c;
	FILE *ip;
	
	ip=fopen("list.txt","w");
	if(ip==NULL){
		printf("xxxx");
		return;
	}
	
	for(i=0; i<numofclient;i++){
		for(j=0; j<numofclient;j++){
			if((client[i]->no)<(client[j]->no)){
				c=client[i];
				client[i]=client[j];
				client[j]=c;
			}
		}	
	}
	
	for(i=0;i<numofclient;i++){
		fprintf(ip,"|%d|%s|%s|%s|%d|\n", client[i]->no, client[i]->pa, client[i]->na, client[i]->ad, client[i]->po);
	}
	
	fclose(ip);
}
void LoadDatafromFile(){

	char tmpStr[500];
	char *res;
	FILE *ip;
	
	ip=fopen("list.txt","r");
	if(ip==NULL){
		return;
	}

	while(1){

		if(numofclient==0){
			client[0]=(Client*)malloc(sizeof(Client));
		}
		else {
			client=(Client**)realloc(client, (numofclient+1)*sizeof(Client*));
		}
		
		res=fgets(tmpStr,sizeof(tmpStr),ip);
		if(res==NULL)break;
		tmpStr[strlen(tmpStr)-1]='\0';
		
		client[numofclient++]=tokenData(tmpStr);
	}
	
	printf("현재 인원: %d\n", numofclient); 
	fclose(ip);
}


Client *tokenData(char *tmpStr){
	
	char *res1;
	Client *pTmp=(Client*)malloc(sizeof(Client));
		
	res1=strtok(tmpStr,"|");
	while(res1!=NULL){
		printf("학번:%d\t",atoi(res1));
		pTmp->no=atoi(res1);
		res1=strtok(NULL,"|");
		printf("비밀번호:%s\t",res1);
		strcpy(pTmp->pa,res1);
		res1=strtok(NULL,"|");
		printf("이름:%s\t",res1);
		strcpy(pTmp->na,res1);
		res1=strtok(NULL,"|");
		printf("주소:%s\t",res1);
		strcpy(pTmp->ad,res1);
		res1=strtok(NULL,"|");
		printf("전화번호:%d\n",atoi(res1));
		pTmp->po=atoi(res1);
		res1=strtok(NULL,"|");
	} 
	
	return pTmp;
}
int menushow(){
	int a;
	printf("<<============>>\n");
	printf("1.도서검색\n");
	printf("2.내 대여목록\n");
	printf("3.개인정보수정\n");
	printf("4.회원탈퇴\n"); 
	printf("5.로그아웃\n");
	printf("6.프로그램종료\n");
	printf("<<============>>\n");
	printf(">>"); 
	scanf("%d",&a);
	return a;
}
int islogincheck(char*a,char *b){
	int i;
	for(i=0; i<numofclient; i++){
		if(client[i]->no==atoi(a)&&strcmp(client[i]->pa,b)==0){
			return TRUE;
		}
	}
	printf("아이디 또는 비밀번호가다름.\n");
	return FALSE;
}

void login(){
	char id[50];
	int i;
	char pa[50];
	
	printf("학번입력:");
	scanf("%s",id);
	printf("비밀번호입력:");
	scanf("%s",pa); 
	if(strcmp(id,"z")==0&&strcmp(pa,"z")==0){
		printf(">>관리자용<<\n");
		admin(); 
		return; 
	}
	if(islogincheck(id,pa)==TRUE){
		printf("로그인\n");
		Servis a;
		while((a=menushow())!=LOGOUT){	
			switch(a){
				case BOOK:search();
					break;
				case LIST:mybook(id);
					break;
				case INFORMATION:revise(id);
					break;
				case UNREGISTER:pdelete(id);
					return;
				case LOGOUT:break;
				case OUT: exit(1);
					break;
				default:break;
			}
		}
	}
}
void revise(char *a){
	int i,c;
	
	for(i=0; i<numofclient; i++){
		if(client[i]->no==atoi(a)){
			printf("학번 :%d\t",client[i]->no);
			printf("비밀번호:%s\t",client[i]->pa);
			printf("이름:%s\t",client[i]->na);
			printf("주소:%s\t",client[i]->ad);
			printf("전화번호:%d\n",client[i]->po);
			c=i;
		}
	}
	printf("변경할 비밀번호:");
	scanf("%s",client[c]->pa);
	printf("변경할주소:");
	scanf("%s",client[c]->ad);
	printf("변경할 전화번호:");
	scanf("%d",&client[c]->po); 
	printf("개인정보 변경완료!\n");
}

void mybook(char *a){
	int i,j,c;
	c=0;
	char temp[50];
	for(i=0;i<numofborrow; i++){
		if(borrow[i]->id==atoi(a)){
			for(j=0;j<numofbook;j++){
				if(borrow[i]->no==book[j]->no){
					strcpy(temp,book[j]->bo);
					printf("도서번호:%d  도서명:%s  대여일:%s  반납일:%s\n",borrow[i]->no,temp,borrow[i]->today,borrow[i]->outday);
					c++;
				}
			}
		}
	}
	if(c==0){
		printf("대여한책이없습니다!\n");
	}
}
void pdelete(char *a){
	int i,j,l,o;
	char c;
	o=0;
	for(i=0; i<numofclient;i++){
		if(client[i]->no==atoi(a)){
			for(l=0;l<numofborrow;l++){
				if(borrow[l]->id==atoi(a)){
					o++;
				}
			}
			if(o==0){
				printf("탈퇴하시겠습니까?(y/n)");
				fflush(stdin);
				scanf("%c",&c);
				if(c=='y'){
					for(j=i;j<numofclient;j++){
						client[j]=client[j+1];	
					}
					printf("탈퇴되었습니다.\n");
					numofclient--;
					return;			
				}
				else if(c=='n'){
					return;
				}
				else {printf("잘못입력함.\n");
					return;
				}
			}
			printf("반납하지않은도서가있습니다.\n");
		}
	}
}
