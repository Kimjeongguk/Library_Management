#include "book.h"

extern Book **book;
extern numofbook;

Book *join1(){
	int i,j,co;
	Book *inbook;
	char str[14];
	co=0;
	
	inbook=(Book*)malloc(sizeof(Book));
	fflush(stdin);
	printf("도서명입력:");
	gets(inbook->bo);
	for(i=0; i<numofbook-1;i++){
		if(strcmp(inbook->bo,book[i]->bo)==0){
			strcpy(inbook->bo,book[i]->bo);
			strcpy(inbook->pu,book[i]->pu);
			strcpy(inbook->au,book[i]->au);
			strcpy(inbook->pl,book[i]->pl);
			strcpy(inbook->ISBN,book[i]->ISBN);
			inbook->no=book[i]->no+1;
		for(j=i+1;j<numofbook-1;j++){
			book[j]->no+=1;
		}
		inbook->lo='Y';
		return inbook;
		}
	}
	printf("출판사입력:");
	gets(inbook->pu);
	
	printf("저자명입력:");
	gets(inbook->au);
	
	printf("소장처정보입력:");
	gets(inbook->pl);
	
	printf("ISBN입력:");
	gets(str);
	
	strcpy(inbook->ISBN,"0000000000000");
	for(i=0;i<strlen(str);i++){
		inbook->ISBN[strlen(inbook->ISBN)-i-1]=str[strlen(str)-i-1];
	}
	inbook->no=1000000+numofbook;
	inbook->lo='Y';
	printf(">>>|%s|%s|%s|%s|%s|%d|%c|\n",inbook->bo,inbook->pu,inbook->au,inbook->pl,inbook->ISBN,inbook->no,inbook->lo);
	return inbook;
}
void booklist(){
	FILE *fp;
	int i,j;
	Book *c;
	
	fp=fopen("booklist.txt","w");
	if(fp==NULL){
		printf("xxxxx");
		return;
	}
	for(i=0; i<numofbook;i++){
		for(j=0; j<numofbook;j++){
			if((book[i]->no)<(book[j]->no)){
				c=book[i];
				book[i]=book[j];
				book[j]=c;
			}
		}	
	}
	for(i=0;i<numofbook;i++){
		fprintf(fp,"|%s|%s|%s|%s|%s|%d|%c|\n",book[i]->bo,book[i]->pu,book[i]->au,book[i]->pl,book[i]->ISBN,book[i]->no,book[i]->lo);
	}
	fclose(fp);
}
void loadbook(){
	FILE *fp;
	char aaa[100];
	char *res;
	fp=fopen("booklist.txt","r");
	if(fp==NULL){
		printf("xxxxxxx");
		return;
	}
	
	while(1){
		if(numofbook==0){
			book[0]=(Book*)malloc(sizeof(Book));
		}
		else{
			book=(Book**)realloc(book,(numofbook+1)*sizeof(Book*));
		}
		
		res=fgets(aaa,sizeof(aaa),fp);
		if(res==NULL){break;}
		
		aaa[strlen(aaa)-1]='\0';
		
		book[numofbook++]=bookdate(aaa);
	}
	printf("현재책권수:%d\n",numofbook);
	fclose(fp);
}

Book *bookdate(char *a){
	
	char *res;
	
	Book *re=(Book*)malloc(sizeof(Book));
	
	res=strtok(a,"|");
	while(res!=NULL){
		printf("도서명:%s\t",res);
		strcpy(re->bo,res);
		res=strtok(NULL,"|");
		printf("출판사:%s\t",res);
		strcpy(re->pu,res);
		res=strtok(NULL,"|");
		printf("저자:%s\t",res);
		strcpy(re->au,res);
		res=strtok(NULL,"|");
		printf("소장처:%s\t",res);
		strcpy(re->pl,res);
		res=strtok(NULL,"|");
		printf("ISBN:%s\t",res);
		strcpy(re->ISBN,res);
		res=strtok(NULL,"|");
		printf("도서번호:%d\t",atoi(res));
		re->no=atoi(res);
		res=strtok(NULL,"|");
		printf("대여가능여부:%s\n",res);
		re->lo=*res;
		res=strtok(NULL,"|");
	}
	
	return re;
}
void search(){
	int a;
	while(a!=6){ 
	
		printf(">>==도서검색===<<\n");
		printf("1.도서명 검색\n");
		printf("2.출판사명 검색\n");
		printf("3.ISBN 검색\n");
		printf("4.저자명 검색\n");
		printf("5.전체 검색\n");
		printf("6.나가기\n");
		printf(">>=============<<\n");
		scanf("%d",&a);
		switch(a){
			case 1:bobo();
				break;
			case 2:bopu();
				break;
			case 3:isbn();
				break;
			case 4:boau();
				break;
			case 5:bookall();
				break;
			case 6:break;
			default :printf("잘못입력함!\n");
		}
	}
}
void bobo(){
	char a[50];
	int i,c;
	c=0;
	printf("도서명입력:");
	scanf("%s",a);
	for(i=0; i<numofbook; i++){
		if(strcmp(book[i]->bo,a)==0){
			printf("도서명:%s 출판사:%s 저자명:%s 소장처:%s ISBN:%s 도서번호:%d 대여여부:%c\n",book[i]->bo,book[i]->pu,book[i]->au,book[i]->pl,book[i]->ISBN,book[i]->no,book[i]->lo);
			c++;	
		}
	}
	if(c==0){printf("잘못입력하였습니다.\n");}
}
void bopu(){
char a[50];
	int i,c;
	c=0;
	printf("출판사입력:");
	scanf("%s",a);
	for(i=0; i<numofbook; i++){
		if(strcmp(book[i]->pu,a)==0){
			printf("도서명:%s 출판사:%s 저자명:%s 소장처:%s ISBN:%s 도서번호:%d 대여여부:%c\n",book[i]->bo,book[i]->pu,book[i]->au,book[i]->pl,book[i]->ISBN,book[i]->no,book[i]->lo);
			c++;	
		}
	}
	if(c==0){printf("잘못입력하였습니다.\n");}
}
void isbn(){
	char a[50];
	int i,c;
	c=0;
	printf("ISBN입력:");
	scanf("%s",a);
	for(i=0; i<numofbook; i++){
		if(strcmp(book[i]->ISBN,a)==0){
			printf("도서명:%s 출판사:%s 저자명:%s 소장처:%s ISBN:%s 도서번호:%d 대여여부:%c\n",book[i]->bo,book[i]->pu,book[i]->au,book[i]->pl,book[i]->ISBN,book[i]->no,book[i]->lo);
			c++;	
		}
	}
	if(c==0){printf("잘못입력하였습니다.\n");}
}
void boau(){
char a[50];
	int i,c;
	c=0;
	printf("저자명입력:");
	scanf("%s",a);
	for(i=0; i<numofbook; i++){
		if(strcmp(book[i]->au,a)==0){
			printf("도서명:%s 출판사:%s 저자명:%s 소장처:%s ISBN:%s 도서번호:%d 대여여부:%c\n",book[i]->bo,book[i]->pu,book[i]->au,book[i]->pl,book[i]->ISBN,book[i]->no,book[i]->lo);
			c++;	
		}
	}
	if(c==0){printf("잘못입력하였습니다.\n");}
}
void bookall(){
	int i;
	for(i=0; i<numofbook; i++){
		printf("도서명:%s 출판사:%s 저자명:%s 소장처:%s ISBN:%s 도서번호:%d 대여여부:%c\n",book[i]->bo,book[i]->pu,book[i]->au,book[i]->pl,book[i]->ISBN,book[i]->no,book[i]->lo);
	}
}
