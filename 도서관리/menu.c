#include "menu.h"

int MainMenuShow(){
	
	int m;
	
	printf("<< 도서관 서비스 >>\n\n"); 
	printf("1.회원가입		2.로그인	3.종료\n"); 
	printf(">> "); 
	scanf("%d", &m);
	return m;
	
}
