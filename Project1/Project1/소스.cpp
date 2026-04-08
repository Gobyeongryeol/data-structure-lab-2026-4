#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


struct employee {
	char name[10];
	int year;
	int pay;

};


void main() {
	struct employee Lee;
	struct employee* sptr = &Lee;
	strcpy(sptr->name, "이순신");
	sptr->year = 2023;
	sptr->pay = 5900;

	printf("\n 이름 : %s", sptr->name);
	printf("\n 입사 : %d", sptr->year);
	printf("\n 연봉 : %d", sptr->pay);

	getchar();

}