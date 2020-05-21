#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void){
	char start[100];
	char end[100];
	char filename[1000];
	char check[100];
	char** list;
	FILE* fp;
	int temp;
	int flag=0;
	int strnum=0;
	int ladnum=0;
	int vocanum=0;
	int i=0;
	int j=0;
	int diff=0; /// store the shortest length path , which is the number of different character between start and end

	list = (char**)malloc(sizeof(char*)*1000000);
	for(i=0;i<1000000;i++){
		list[i] = (char*)malloc(sizeof(char)*100);
	}
	//initializing list with 100 character strings.
	printf("Input start word :");
	scanf("%s",start);
	for(i=0;i<strlen(start);i++){
	    if(start[i]>='A' && start[i]<='Z'){
		start[i] = start[i]-'A'+'a';
	    }
	}
	
	printf("Input end word :");
	scanf("%s",end);
	printf("Input Dictionary files :");
	scanf("%s",filename);
	strnum = strlen(start);
	if(strnum!=strlen(end)){
		printf("Length of start and end are not same\n");
		return 0;
	}
///////////////////////////////////////////////////////
	for(i=0;i<strnum;i++){
		if(start[i]!=end[i]){
			diff++;
		}
	}

	///////////////////////////////////////////////
	fp = fopen(filename,"r");
	if(fp==NULL){
		printf("%s is not a file\n",filename);
		return 0;
	}
	while(EOF!=fscanf(fp,"%s",check)){
		if(strlen(check)==strnum){
		//add into list
			strcpy(list[vocanum],check);
			vocanum++;
		}
	}
	//store every strnum length of words in dictionary
	// to do is get applicant from list

	//////////////
	for(i=0;i<vocanum;i++){
		for(int j=0;j<strnum;j++){
		    if(list[i][j]==start[j] || list[i][j]-'A'+'a'==start[j]){
				flag++;
		    }
		}
		if(flag==strnum-1){
		    printf("%s\n",list[i]);
		    ladnum++;
		}
		flag=0;
	}
	if(ladnum==0){
	    printf("No such words ladder\n");
	}
	for(i=0;i<1000000;i++){
	    free(list[i]);
	}
	free(list);
	return 0;
}














