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
	srand((unsigned)time(NULL));//��ϵͳʱ����Ϊ��������� 
	for(i = 0;i < m;i++)
	{
		n = 1 + rand() % 32;//�ַ�����1~32 
		for(j = 0;j < n;j++)
		{
			str[i][j] = 'a' + rand() % 26;//����ֻ��Сд������ַ��� 
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
