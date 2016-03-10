#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	FILE *fp;
	char *buffer;
	int size,ret;

	if(argc<3){
		printf("eg:%s <filename> <textsize>\n",argv[0]);
		exit(0);
	}
	fp=fopen(argv[1],"w+");
	if(fp==NULL){
		printf("create or write file error\n");
		exit(0);
	}
	
	size=atoi(argv[2]);
	if(size<6){
		printf("text size error\n");
		exit(0);
	}
	buffer=(char *)malloc(sizeof(size+1));
	sprintf(buffer,"%s","begin");
	memset(buffer+5,'o',size-8);
	sprintf(buffer+size-3,"%s","end");
	
	ret = fprintf(fp,"%s",buffer);
	printf("write size:%d,%s\n",ret,ret==size?"success":"fail");

	return 0;
}
