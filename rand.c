#include<stdio.h>
#include<stdlib.h>
int main()
{
        int i;
		//default call:srand(0);
		for(i=0; i<10; i++)  //随机产生10个数。
        {
            printf("%d\n", rand());
        }
        return 0;
}
