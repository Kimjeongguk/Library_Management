#include "borrow.h"
#include "etc.h"

extern Client **client;
extern int numofclient;

extern Book **book;
extern numofbook;

extern Borrow **borrow;
extern int numofborrow;

void inbook(){
	int a;
	while(a!=3){
		printf(">>�����뿩<<\n");
		printf("1.������ �˻�\n");
		printf("2.ISBN �˻�\n");
		printf("3.������\n");
		scanf("%d",&a);
		switch(a){
			case 1:inbook1();
				break;
			case 2:inbook2();
				break;
			case 3:break;
			default : break;
		}
		borrowlist();
	} 
}
void inbook1(){
	
	char a[50];
	int i,j,c;
	int b,bb;
	c=0;
	printf("�������Է�>>");
	scanf("%s",a);
	for(i=0; i<numofbook; i++){
		if(strcmp(book[i]->bo,a)==0){
			c++;
			printf("|%s|%s|%s|%s|%s|%d|%c|\n",book[i]->bo,book[i]->pu,book[i]->au,book[i]->pl,book[i]->ISBN,book[i]->no,book[i]->lo); 
		}
	}
	if(c!=0){
		printf("�뿩���� �л� �й�>>");
		fflush(stdin);
		scanf("%d",&bb);
		for(i=0; i<numofclient;i++){
			if(client[i]->no==bb){
				printf("�뿩���� å��ȣ>>");
				scanf("%d",&b);
				for(j=0;j<numofbook;j++){
					if(book[j]->no==b){
						borrow[numofborrow++]=join2(bb,b);
						return;
					}
				}
			}
		}
		printf("�߸��Է�!\n");
		return;
	}
		
	else if(c==0){
		printf("�߸��Է�!\n");
		return;
	}
}
void inbook2(){
	
	char a[50];
	int i,j,c;
	int b,bb;
	c=0;
	printf("ISBN�Է�>>");
	scanf("%s",a);
	for(i=0; i<numofbook; i++){
		if(strcmp(book[i]->ISBN,a)==0){
			c++;
			printf("|%s|%s|%s|%s|%s|%d|%c|\n",book[i]->bo,book[i]->pu,book[i]->au,book[i]->pl,book[i]->ISBN,book[i]->no,book[i]->lo); 
		}
	}
	if(c!=0){
		printf("�뿩���� �л� �й�>>");
		fflush(stdin);
		scanf("%d",&bb);
		for(i=0; i<numofclient;i++){
			if(client[i]->no==bb){
				printf("�뿩���� å��ȣ>>");
				scanf("%d",&b);
				for(j=0;j<numofbook;j++){
					if(book[j]->no==b){
						borrow[numofborrow++]=join2(bb,b);
						return;
					}
				}
			}
		}
		printf("�߸��Է�!\n");
		return;
	}
		
	else if(c==0){
		printf("�߸��Է�!\n");
		return;
	}
}

Borrow *join2(int a,int b){
	struct tm *t;
	time_t timer;
	
	timer=time(NULL);
	t=localtime(&timer);
	Borrow *p;
	p=(Borrow*)malloc(sizeof(Borrow));
	char temp[500];
	int i;
	
	p->id=a;
	p->no=b;
	
	sprintf(temp,"%d:%d:%d:%d:%d:%d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	strcpy(p->today,temp);
	t->tm_mday+=30;
	if(t->tm_mday>30){
		t->tm_mday-=30;
		t->tm_mon++;
		if(t->tm_mon>12){
			t->tm_mon-=12;
			t->tm_year++;
		}
	}
	sprintf(temp,"%d:%d:%d:%d:%d:%d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	strcpy(p->outday,temp);
	
	for(i=0;i<numofbook;i++){
		if(book[i]->no==b){
			book[i]->lo='N';
		}
	}
	
	return p;
}
void borrowlist(){
	int i;
	FILE *ip;
	ip=fopen("borrowlist.txt","w");
	if(ip==NULL){
		printf("xxxx");
		return;
	}
	
	for(i=0;i<numofborrow;i++){
		fprintf(ip,"|%d|%d|%s|%s|\n", borrow[i]->id, borrow[i]->no, borrow[i]->today, borrow[i]->outday);
	}
	fclose(ip);
}
void borrowload(){
	char tmpStr[500];
	char *res;
	FILE *ip;
	ip=fopen("borrowlist.txt","r");
	if(ip==NULL){
		return;
	}
	while(1){
		
		if(numofborrow==0){
			borrow[0]=(Borrow*)malloc(sizeof(Borrow));
		}
		else {
			borrow=(Borrow**)realloc(borrow, (numofborrow+1)*sizeof(Borrow*));
		}
		
		res=fgets(tmpStr,sizeof(tmpStr),ip);
		if(res==NULL)break;
		tmpStr[strlen(tmpStr)-1]='\0';
		
		borrow[numofborrow++]=token(tmpStr);
	}
	printf("���� �뿩Ƚ��: %d\n", numofborrow); 
	fclose(ip);
}
Borrow *token(char*a){
	char *res1;
	Borrow *pTmp=(Borrow*)malloc(sizeof(Borrow));
		
	res1=strtok(a,"|");
	while(res1!=NULL){
		printf("�й�:%s\t",res1);
		pTmp->id=atoi(res1);
		res1=strtok(NULL,"|");
		
		printf("������ȣ:%d\t",atoi(res1));
		pTmp->no=atoi(res1);
		res1=strtok(NULL,"|");
		
		printf("������:%s\t",res1);
		strcpy(pTmp->today,res1);
		res1=strtok(NULL,"|");
		
		printf("�ݳ���:%s\n",res1);
		strcpy(pTmp->outday,res1);
		res1=strtok(NULL,"|");
	} 
	return pTmp;
}
void outbook(){
	int a,i,j,c,aa;
	c=0;
	printf("�й��� �Է��ϼ���>>");
	scanf("%d",&a);
	for(i=0; i<numofborrow; i++){
		if(borrow[i]->id==a){
			printf("�й�:%d  ������ȣ:%d  �뿩��:%s  �ݳ���:%s\n", borrow[i]->id, borrow[i]->no, borrow[i]->today, borrow[i]->outday);
			c++;
		}
	}
	if(c==0){
		printf("�뿩����å�̾����ϴ�.\n");
		return;
	}
	printf("�ݳ��� ������ȣ �Է�>>");
	scanf("%d",&aa);
	for(i=0; i<numofborrow; i++){
		if(borrow[i]->no==aa){
			for(j=0;j<numofbook;j++){
				if(borrow[i]->no==book[j]->no){
					book[j]->lo='Y';
				}
			}
			for(j=i;j<numofborrow;j++){
				borrow[j]=borrow[j+1];
			}
			numofborrow--;
			printf("�����ݳ��Ϸ�!\n");
			return;
		}
	}
	printf("������ȣ �߸��Է�!\n");
	return;
}
