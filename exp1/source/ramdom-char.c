#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"


int main()
{
	int i,j,m = pow(2,17),n = 0;
	char **str;
	str = (char**)malloc(sizeof(char*)*m);
	for(i =0;i < m;i++)
		str[i] = (char*)malloc(sizeof(char)*33);
	srand((unsigned)time(NULL));//以系统时间作为随机数种子 
	for(i = 0;i < m;i++)
	{
		n = 1 + rand() % 32;//字符串长1~32 
		for(j = 0;j < n;j++)
		{
			str[i][j] = 'a' + rand() % 26;//生成只有小写的随机字符串 
			str[i][j + 1] = '\0';
		}
	}
		FILE *fp;
		if((fp = fopen("../input/data.txt","w"))== NULL)
		{
			printf("error");
		}
		else
		{
			for(i = 0;i < m;i++)
			{
				fprintf(fp,"%s\n",str[i]);
			}
			printf("successful!");
			fclose(fp);
		}
	return 0;
}
