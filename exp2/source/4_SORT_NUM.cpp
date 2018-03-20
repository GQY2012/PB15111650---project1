#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "windows.h"

#define radix 10  //十位数 

LARGE_INTEGER nFreq;//时钟频率 
LARGE_INTEGER t1;//开始 
LARGE_INTEGER t2;//结束 
double dt[6]; //时间差 


void BUBBLESORT(int a[],int n)
{
	int i,j,flag,t;
	for(i = 0;i < n - 1;i++){ 
		flag = 0;
		for(j = n - 1;j > i;j--){
			if(a[j] < a[j-1]){
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
				flag = 1;
			}
		}
		if(flag==0){
			return;
		}
	}
}//冒泡 

int PARTITION(int a[],int p,int r)
{
	int i,j,x,temp;
	x = a[r];
	i = p - 1;
	for(j = p;j < r;j++)
	{
		if(a[j] <= x)
		{
			i = i + 1;
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	temp = a[i+1];
	a[i+1] = a[r];
	a[r] = temp;
	return i + 1;
}

void QUICKPORT(int a[],int p,int r)
{
	int q;
	if(p < r)
	{
		q = PARTITION(a,p,r);
		QUICKPORT(a,p,q - 1);
		QUICKPORT(a,q + 1,r);
	}
}//快排 

void COUNTING_SORT(int a[],int b[],int k,int n)
{
	int c[k+1];
	for(int i = 0;i <= k;i++)
		c[i] = 0;
	for(int j = 0;j < n;j++)
		c[a[j]]++;
	for(int l = 1;l <= k;l++)
		c[l] = c[l] + c[l - 1];
	for(int m = n -1;m >= 0;m--)
	{
		b[c[a[m]] - 1] = a[m];
		c[a[m]]--;
	}
}//计数 

int GetNumIn(int num,int dec)  
{  
    int temp = 1;  
    for (int i = 0; i < dec - 1; i++)  
        temp *= 10;  
  
    return (num / temp) % 10;  
}//取num的dec位的数 

int RADIXSORT(int a[],int n)
{
	int *radixArrays[radix];//分配0~9的序列空间 
	for(int i =0;i < radix;i++)
	{
		radixArrays[i] = (int*)malloc(sizeof(int)*(n + 1));
		radixArrays[i][0] = 0;
	} 
	for(int j = 1;j <= 5;j++)//此处j:待排数据的最大位数 
	{
		for(int i = 0;i < n;i++)//分配 
		{
			int num = GetNumIn(a[i],j);
			int index = ++radixArrays[num][0];
			radixArrays[num][index] = a[i];
		}
		for (int i = 0, j =0; i < radix; i++)     //收集 
        {  
            for (int k = 1; k <= radixArrays[i][0]; k++)  
                a[j++] = radixArrays[i][k];  
            radixArrays[i][0] = 0;  //复位  
        }  
	}
}//基数排序 

int main()
{
	int i = 0,count,m = pow(2,17);//count:六次排序  m:数组最大规模 
	int arr[6] = {2,5,8,11,14,17};//六种规模的数组 
	QueryPerformanceFrequency(&nFreq);//cpu频率 
	int a[m],b[m];//a为操作数组，b为counting_sort的辅助数组 
	char ch;//操作码  
	FILE *fp1,*fp2,*fp3;
	printf("input b q c or r\n");
		ch = getchar();
			switch(ch)
			{
				case 'b':
				for(count = 0;count < 6;count++)
				{
					m = pow(2,arr[count]);
					if((fp1 = fopen("../input/data.txt","r"))== NULL)
			{
				printf("error\n");
			}
			else
			{
				for(i = 0;i < m;i++)
				{
					fscanf(fp1,"%d",&a[i]);
				}
				printf("read successful!\n");
				fclose(fp1);
			}
				QueryPerformanceCounter(&t1);
				BUBBLESORT(a,m);
				QueryPerformanceCounter(&t2);
				switch(count)
				{
					case 0:if((fp2 = fopen("../output/BUBBLESORT/result_2.txt","w"))== NULL)
					printf("error\n");break;
					case 1:if((fp2 = fopen("../output/BUBBLESORT/result_5.txt","w"))== NULL)
					printf("error\n");break;
					case 2:if((fp2 = fopen("../output/BUBBLESORT/result_8.txt","w"))== NULL)
					printf("error\n");break;
					case 3:if((fp2 = fopen("../output/BUBBLESORT/result_11.txt","w"))== NULL)
					printf("error\n");break;
					case 4:if((fp2 = fopen("../output/BUBBLESORT/result_14.txt","w"))== NULL)
					printf("error\n");break;
					case 5:if((fp2 = fopen("../output/BUBBLESORT/result_17.txt","w"))== NULL)
					printf("error\n");break;
				}
				for(i = 0;i < m;i++)
					fprintf(fp2,"%d\n",a[i]);
				printf("write successful!\n");
				dt[count] = (t2.QuadPart - t1.QuadPart )/ (double)nFreq.QuadPart *1000000;    
				fclose(fp2);}
				if((fp3 = fopen("../output/BUBBLESORT/time.txt","w"))== NULL)
					printf("error\n");
				for(count = 0;count < 6;count++)
				{
					fprintf(fp3,"%f\n",dt[count]);
				}	
				fclose(fp3);
				break;
			case 'q':
				for(count = 0;count < 6;count++)
				{
					m = pow(2,arr[count]);
					if((fp1 = fopen("../input/data.txt","r"))== NULL)
			{
				printf("error\n");
			}
			else
			{
				for(i = 0;i < m;i++)
				{
					fscanf(fp1,"%d",&a[i]);
				}
				printf("read successful!\n");
				fclose(fp1);
			}
				QueryPerformanceCounter(&t1);
				QUICKPORT(a,0,m-1);
				QueryPerformanceCounter(&t2);
				switch(count)
				{
					case 0:if((fp2 = fopen("../output/QUICKSORT/result_2.txt","w"))== NULL)
					printf("error\n");break;
					case 1:if((fp2 = fopen("../output/QUICKSORT/result_5.txt","w"))== NULL)
					printf("error\n");break;
					case 2:if((fp2 = fopen("../output/QUICKSORT/result_8.txt","w"))== NULL)
					printf("error\n");break;
					case 3:if((fp2 = fopen("../output/QUICKSORT/result_11.txt","w"))== NULL)
					printf("error\n");break;
					case 4:if((fp2 = fopen("../output/QUICKSORT/result_14.txt","w"))== NULL)
					printf("error\n");break;
					case 5:if((fp2 = fopen("../output/QUICKSORT/result_17.txt","w"))== NULL)
					printf("error\n");break;
				}
				for(i = 0;i < m;i++)
					fprintf(fp2,"%d\n",a[i]);
				printf("write successful!\n");
				dt[count] = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart *1000000;    
				fclose(fp2);}
				if((fp3 = fopen("../output/QUICKSORT/time.txt","w"))== NULL)
					printf("error\n");
				for(count = 0;count < 6;count++)
				{
					fprintf(fp3,"%f\n",dt[count]);
				}
				fclose(fp3);	
				break;
			
			case 'c':
				for(count = 0;count < 6;count++)
				{
					m = pow(2,arr[count]);
					if((fp1 = fopen("../input/data.txt","r"))== NULL)
			{
				printf("error\n");
			}
			else
			{
				for(i = 0;i < m;i++)
				{
					fscanf(fp1,"%d",&a[i]);
				}
				printf("read successful!\n");
				fclose(fp1);
			}
				QueryPerformanceCounter(&t1);
				COUNTING_SORT(a,b,65535,m);
				QueryPerformanceCounter(&t2);
				switch(count)
				{
					case 0:if((fp2 = fopen("../output/COUNTING_SORT/result_2.txt","w"))== NULL)
					printf("error\n");break;
					case 1:if((fp2 = fopen("../output/COUNTING_SORT/result_5.txt","w"))== NULL)
					printf("error\n");break;
					case 2:if((fp2 = fopen("../output/COUNTING_SORT/result_8.txt","w"))== NULL)
					printf("error\n");break;
					case 3:if((fp2 = fopen("../output/COUNTING_SORT/result_11.txt","w"))== NULL)
					printf("error\n");break;
					case 4:if((fp2 = fopen("../output/COUNTING_SORT/result_14.txt","w"))== NULL)
					printf("error\n");break;
					case 5:if((fp2 = fopen("../output/COUNTING_SORT/result_17.txt","w"))== NULL)
					printf("error\n");break;
				}
				for(i = 0;i < m;i++)
					fprintf(fp2,"%d\n",b[i]);
				printf("write successful!\n");
				dt[count] = (t2.QuadPart - t1.QuadPart )/ (double)nFreq.QuadPart *1000000;    
				fclose(fp2);}
				if((fp3 = fopen("../output/COUNTING_SORT/time.txt","w"))== NULL)
					printf("error\n");
				for(count = 0;count < 6;count++)
				{
					fprintf(fp3,"%f\n",dt[count]);
				}	
				fclose(fp3);
				break;
			case 'r':
				for(count = 0;count < 6;count++)
				{
					m = pow(2,arr[count]);
					if((fp1 = fopen("../input/data.txt","r"))== NULL)
			{
				printf("error\n");
			}
			else
			{
				for(i = 0;i < m;i++)
				{
					fscanf(fp1,"%d",&a[i]);
				}
				printf("read successful!\n");
				fclose(fp1);
			}
				QueryPerformanceCounter(&t1);
				RADIXSORT(a,m);
				QueryPerformanceCounter(&t2);
				switch(count)
				{
					case 0:if((fp2 = fopen("../output/RADIXSORT/result_2.txt","w"))== NULL)
					printf("error\n");break;
					case 1:if((fp2 = fopen("../output/RADIXSORT/result_5.txt","w"))== NULL)
					printf("error\n");break;
					case 2:if((fp2 = fopen("../output/RADIXSORT/result_8.txt","w"))== NULL)
					printf("error\n");break;
					case 3:if((fp2 = fopen("../output/RADIXSORT/result_11.txt","w"))== NULL)
					printf("error\n");break;
					case 4:if((fp2 = fopen("../output/RADIXSORT/result_14.txt","w"))== NULL)
					printf("error\n");break;
					case 5:if((fp2 = fopen("../output/RADIXSORT/result_17.txt","w"))== NULL)
					printf("error\n");break;
				}
				for(i = 0;i < m;i++)
					fprintf(fp2,"%d\n",a[i]);
				printf("write successful!\n");
				dt[count] = (t2.QuadPart - t1.QuadPart )/ (double)nFreq.QuadPart *1000000;    
				fclose(fp2);}
				if((fp3 = fopen("../output/RADIXSORT/time.txt","w"))== NULL)
					printf("error\n");
				for(count = 0;count < 6;count++)
				{
					fprintf(fp3,"%f\n",dt[count]);
				}
				fclose(fp3);
				break;
		}
	return 0;
}
