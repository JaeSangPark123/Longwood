#include<stdio.h>
int main(int argc,char** argv){
	printf("%s --> %s\n",argv[2],argv[1]);
	printf("%s --> %s\n",argv[1],argv[0]);
	printf("child done\n");
	return 0;
}
