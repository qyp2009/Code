#include<stdio.h>
#include<stdlib.h>
#include <time.h>
int main()
{
		srand((int)time(NULL));
        int i;
        for(i=0; i<10; i++)  //随机产生10个数。
        {
            printf("%d\n", rand());
        }
        return 0;
}
