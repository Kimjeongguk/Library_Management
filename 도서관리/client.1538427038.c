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
		printf("�й��� �Է��ϼ���:");
		fscanf(stdin, "%d",&pClient->no);
		
		if(!isIdcheck(pClient->no)){
			printf("���԰���\n");
			break;
		}
		else {
			printf("������ �й�����\n");
		}
	}
	fflush(stdin);
	printf("��й�ȣ�� �Է��ϼ���:");
	fgets(pClient->pa, sizeof(pClient->pa), stdin);
	pClient->pa[strlen(pClient->pa)-1]='\0';
	
	fflush(stdin);
	printf("�̸��� �Է��ϼ���:");
	fgets(pClient->na, sizeof(pClient->na), stdin); 
	pClient->na[strlen(pClient->na)-1]='\0';
	
	printf("�ּҸ� �Է��ϼ���:");
	fflush(stdin);
	fgets(pClient->ad,sizeof(pClient->ad),stdin); 
	pClient->ad[strlen(pClient->ad)-1]='\0';

	printf("��ȭ��ȣ�� �Է��ϼ���:");
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
	
	printf("���� �ο�: %d\n", numofclient); 
	fclose(ip);
}


Client *tokenData(char *tmpStr){
	
	char *res1;
	Client *pTmp=(Client*)malloc(sizeof(Client));
		
	res1=strtok(tmpStr,"|");
	while(res1!=NULL){
		printf("�й�:%d\t",atoi(res1));
		pTmp->no=atoi(res1);
		res1=strtok(NULL,"|");
		printf("��й�ȣ:%s\t",res1);
		strcpy(pTmp->pa,res1);
		res1=strtok(NULL,"|");
		printf("�̸�:%s\t",res1);
		strcpy(pTmp->na,res1);
		res1=strtok(NULL,"|");
		printf("�ּ�:%s\t",res1);
		strcpy(pTmp->ad,res1);
		res1=strtok(NULL,"|");
		printf("��ȭ��ȣ:%d\n",atoi(res1));
		pTmp->po=atoi(res1);
		res1=strtok(NULL,"|");
	} 
	
	return pTmp;
}
int menushow(){
	int a;
	printf("<<============>>\n");
	printf("1.�����˻�\n");
	printf("2.�� �뿩���\n");
	printf("3.������������\n");
	printf("4.ȸ��Ż��\n"); 
	printf("5.�α׾ƿ�\n");
	printf("6.���α׷�����\n");
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
	printf("���̵� �Ǵ� ��й�ȣ���ٸ�.\n");
	return FALSE;
}

void login(){
	char id[50];
	int i;
	char pa[50];
	
	printf("�й��Է�:");
	scanf("%s",id);
	printf("��й�ȣ�Է�:");
	scanf("%s",pa); 
	if(strcmp(id,"z")==0&&strcmp(pa,"z")==0){
		printf(">>�����ڿ�<<\n");
		admin(); 
		return; 
	}
	if(islogincheck(id,pa)==TRUE){
		printf("�α���\n");
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
			printf("�й� :%d\t",client[i]->no);
			printf("��й�ȣ:%s\t",client[i]->pa);
			printf("�̸�:%s\t",client[i]->na);
			printf("�ּ�:%s\t",client[i]->ad);
			printf("��ȭ��ȣ:%d\n",client[i]->po);
			c=i;
		}
	}
	printf("������ ��й�ȣ:");
	scanf("%s",client[c]->pa);
	printf("�������ּ�:");
	scanf("%s",client[c]->ad);
	printf("������ ��ȭ��ȣ:");
	scanf("%d",&client[c]->po); 
	printf("�������� ����Ϸ�!\n");
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
					printf("������ȣ:%d  ������:%s  �뿩��:%s  �ݳ���:%s\n",borrow[i]->no,temp,borrow[i]->today,borrow[i]->outday);
					c++;
				}
			}
		}
	}
	if(c==0){
		printf("�뿩��å�̾����ϴ�!\n");
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
				printf("Ż���Ͻðڽ��ϱ�?(y/n)");
				fflush(stdin);
				scanf("%c",&c);
				if(c=='y'){
					for(j=i;j<numofclient;j++){
						client[j]=client[j+1];	
					}
					printf("Ż��Ǿ����ϴ�.\n");
					numofclient--;
					return;			
				}
				else if(c=='n'){
					return;
				}
				else {printf("�߸��Է���.\n");
					return;
				}
			}
			printf("�ݳ����������������ֽ��ϴ�.\n");
		}
	}
}
