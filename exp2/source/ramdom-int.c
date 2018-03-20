#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

int main()
{
	int i,m = pow(2,17),n = 0;
	int array[m];
	srand((unsigned)time(NULL));//系统时间作为随机数种子 
	for(i = 0;i < m;i++)
	{
		array[i] = (1+rand()%65535) | ((rand() % 2) << 15);//左移15位作为产生二进制数的第十六位
	}
		FILE *fp;
		if((fp = fopen("../input/data.txt","w"))== NULL)
		{
			printf("error");
		}
		else
		{
			 for(i = 0;i < m; i++) 
			 {
        		fprintf(fp, "%d\n", array[i]);  
        	}
				printf("successful!");
				fclose(fp);
		}
	return 0;
}
