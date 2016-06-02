#include <stdio.h>
#include <stdlib.h>


int main(){
	FILE *fp;
	char s[1024];
	if((fp=fopen("./test_file_1.txt","w+"))==NULL){
		fprintf(stderr,"open file error\n");
		exit(1);
	}
	fprintf(fp,"hello,cooper,%d\n",123);
	//fgets(s,1024,fp);
	//puts(s);

	fclose(fp);
	return 0;
}
