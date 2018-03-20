#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "string.h" 
#include "windows.h"

#define len 33 

LARGE_INTEGER nFreq;//时钟频率 
LARGE_INTEGER t1;//开始 
LARGE_INTEGER t2;//结束 
double dt[6]; //时间差 

int compare(char a[],char b[])
{
	if(strlen(a) > strlen(b) ||strlen(a) == strlen(b) && strcmp(a,b) > 0)
		return 1;
	return 0;
}//字符串比较函数

void exchange(char a[],char b[])
{
	char ch[len];
	strcpy(ch,a);
	strcpy(a,b);
	strcpy(b,ch);
}//交换函数 

void INSERTION_SORT(char *a[len],int n)
{
	int i,j;
	char ch[len];
	for(j = 1;j < n;j++)
	{
		strcpy(ch,a[j]);
		i = j -1;
		while(i >= 0 && compare(a[i],ch))
		{
			strcpy(a[i+1],a[i]);
			i = i -1;
		}
		strcpy(a[i+1],ch);
	}
}//插入排序 

int PARTITION(char *a[len],int p,int r)
{
	int i,j;
	char ch[len];
	strcpy(ch,a[r]);
	i = p - 1;
	for(j = p;j < r;j++)
	{
		if(!compare(a[j],ch))
		{
			i = i + 1;
			exchange(a[i],a[j]);
		}
	}
	exchange(a[i+1],a[r]);
	return i + 1;
}//划分函数 

void QUICKPORT(char *a[len],int p,int r)
{
	int q;
	if(p < r)
	{
		q = PARTITION(a,p,r);
		QUICKPORT(a,p,q - 1);
		QUICKPORT(a,q + 1,r);
	}
}//快速排序 

void MAX_HEAPIFY(char *a[len],int i,int n)
{
	int l,r,largest;
	l = 2*i + 1;
	r = 2*i + 2;
	if(l < n && compare(a[l],a[i]))
		largest = l;
	else
		largest = i;
	if(r < n && compare(a[r],a[largest]))
		largest = r;
	if(largest != i)
	{
		exchange(a[i],a[largest]);
		MAX_HEAPIFY(a,largest,n);
	}
}//最大堆函数 

void BUILD_MAX_HEAP(char *a[len],int n)
{
	 int i;
	 for(i = floor(n/2) - 1;i >= 0;i--)
	 	MAX_HEAPIFY(a,i,n);
}//建最大堆函数 

void HEAPSORT(char *a[len],int n)
{
	int i;
	BUILD_MAX_HEAP(a,n);
	for(i = n - 1;i >= 1;i--)
	{
		exchange(a[0],a[i]);
		n--;
		MAX_HEAPIFY(a,0,n);
	}
}//堆排序 

void MERGE(char *a[len],int p,int q,int r)
{
	int n1 = q - p + 1,n2 = r - q;
	int i,j,k = p;
	char **L,**R;
	L = (char**)malloc(sizeof(char*)*n1);
	R = (char**)malloc(sizeof(char*)*n2);
	for(i = 0;i < n1;i++)
		L[i] = (char*)malloc(sizeof(char)*len);
	for(j = 0;j < n2;j++)
		R[j] = (char*)malloc(sizeof(char)*len);
	for(i = 0;i < n1;i++)
		strcpy(L[i],a[p + i]);
	for(j = 0;j < n2;j++)
		strcpy(R[j],a[q + j + 1]);
	i = 0;
	j = 0;
	while(i < n1 && j < n2)
	{
		if(!compare(L[i],R[j]))
		{
			strcpy(a[k],L[i]);
			i++;
			k++;
		}
		else
		{
			strcpy(a[k],R[j]);
			j++;
			k++;
		}
	}
	while(i < n1)
	{
		strcpy(a[k],L[i]);
			i++;
			k++;
	}
	while(j < n2)
	{
		strcpy(a[k],R[j]);
			j++;
			k++;
	}
}//归并函数 

void MERGE_SORT(char *a[len],int p,int r)
{
	if(p < r)
	{
		int q;
		q = floor((p + r)/2);
		MERGE_SORT(a,p,q);
		MERGE_SORT(a,q+1,r);
		MERGE(a,p,q,r);
	}
}//归并排序 

int main()
{
	int i,j,count,m,n = pow(2,17) ;
	char **str;
	str = (char**)malloc(sizeof(char*)*m);
	for(i =0;i < m;i++)
		str[i] = (char*)malloc(sizeof(char)*33);
	int arr[6] = {2,5,8,11,14,17};//排序规模 
	char ch;
	QueryPerformanceFrequency(&nFreq);//获取CPU频率 
	FILE *fp1,*fp2,*fp3;
	printf("input i q h or m\n");
	ch = getchar();
	switch(ch)
	{
		case 'i':
			for(count = 0;count < 6;count++)
			{
				m = pow(2,arr[count]);
			if((fp1 = fopen("../input/data.txt","r"))== NULL)
			{
				printf("error");
			}
			else
			{
				for(i = 0;i < m;i++)
				{
					fscanf(fp1,"%s",str[i]);
				}
				printf("read successful!\n");
				fclose(fp1);
			}
			QueryPerformanceCounter(&t1);//开始时间 
			INSERTION_SORT(str,m);
			QueryPerformanceCounter(&t2);//结束时间 
			switch(count)
				{
					case 0:if((fp2 = fopen("../output/INSERTION_SORT/result_2.txt","w"))== NULL)
					printf("error\n");break;
					case 1:if((fp2 = fopen("../output/INSERTION_SORT/result_5.txt","w"))== NULL)
					printf("error\n");break;
					case 2:if((fp2 = fopen("../output/INSERTION_SORT/result_8.txt","w"))== NULL)
					printf("error\n");break;
					case 3:if((fp2 = fopen("../output/INSERTION_SORT/result_11.txt","w"))== NULL)
					printf("error\n");break;
					case 4:if((fp2 = fopen("../output/INSERTION_SORT/result_14.txt","w"))== NULL)
					printf("error\n");break;
					case 5:if((fp2 = fopen("../output/INSERTION_SORT/result_17.txt","w"))== NULL)
					printf("error\n");break;
				}
			for(i = 0;i < m;i++)
				fprintf(fp2,"%s\n",str[i]);
			printf("write successful!\n");
			dt[count] = (t2.QuadPart - t1.QuadPart )/ (double)nFreq.QuadPart *1000000;  //时间差  
			fclose(fp2);
			}
			if((fp3 = fopen("../output/INSERTION_SORT/time.txt","w"))== NULL)
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
				printf("error");
			}
			else
			{
				for(i = 0;i < m;i++)
				{
					fscanf(fp1,"%s",str[i]);
				}
				printf("read successful!\n");
				fclose(fp1);
			}
			QueryPerformanceCounter(&t1);
			QUICKPORT(str,0,m-1);
			QueryPerformanceCounter(&t2);
			switch(count)
				{
					case 0:if((fp2 = fopen("../output/QUICKPORT/result_2.txt","w"))== NULL)
					printf("error\n");break;
					case 1:if((fp2 = fopen("../output/QUICKPORT/result_5.txt","w"))== NULL)
					printf("error\n");break;
					case 2:if((fp2 = fopen("../output/QUICKPORT/result_8.txt","w"))== NULL)
					printf("error\n");break;
					case 3:if((fp2 = fopen("../output/QUICKPORT/result_11.txt","w"))== NULL)
					printf("error\n");break;
					case 4:if((fp2 = fopen("../output/QUICKPORT/result_14.txt","w"))== NULL)
					printf("error\n");break;
					case 5:if((fp2 = fopen("../output/QUICKPORT/result_17.txt","w"))== NULL)
					printf("error\n");break;
				}
			for(i = 0;i < m;i++)
				fprintf(fp2,"%s\n",str[i]);
			printf("write successful!\n");
			dt[count] = (t2.QuadPart - t1.QuadPart )/ (double)nFreq.QuadPart *1000000;    
			fclose(fp2);
			}
			if((fp3 = fopen("../output/QUICKPORT/time.txt","w"))== NULL)
					printf("error\n");
				for(count = 0;count < 6;count++)
				{
					fprintf(fp3,"%f\n",dt[count]);
				}
			fclose(fp3);	
			break;
		case 'h':
			for(count = 0;count < 6;count++)
			{
				m = pow(2,arr[count]);
			if((fp1 = fopen("../input/data.txt","r"))== NULL)
			{
				printf("error");
			}
			else
			{
				for(i = 0;i < m;i++)
				{
					fscanf(fp1,"%s",str[i]);
				}
				printf("read successful!\n");
				fclose(fp1);
			}
			QueryPerformanceCounter(&t1);
			HEAPSORT(str,m);
			QueryPerformanceCounter(&t2);
			switch(count)
				{
					case 0:if((fp2 = fopen("../output/HEAPSORT/result_2.txt","w"))== NULL)
					printf("error\n");break;
					case 1:if((fp2 = fopen("../output/HEAPSORT/result_5.txt","w"))== NULL)
					printf("error\n");break;
					case 2:if((fp2 = fopen("../output/HEAPSORT/result_8.txt","w"))== NULL)
					printf("error\n");break;
					case 3:if((fp2 = fopen("../output/HEAPSORT/result_11.txt","w"))== NULL)
					printf("error\n");break;
					case 4:if((fp2 = fopen("../output/HEAPSORT/result_14.txt","w"))== NULL)
					printf("error\n");break;
					case 5:if((fp2 = fopen("../output/HEAPSORT/result_17.txt","w"))== NULL)
					printf("error\n");break;
				}
			for(i = 0;i < m;i++)
				fprintf(fp2,"%s\n",str[i]);
			printf("write successful!\n");
			dt[count] = (t2.QuadPart - t1.QuadPart )/ (double)nFreq.QuadPart *1000000;    
			fclose(fp2);
			}
			if((fp3 = fopen("../output/HEAPSORT/time.txt","w"))== NULL)
					printf("error\n");
				for(count = 0;count < 6;count++)
				{
					fprintf(fp3,"%f\n",dt[count]);
				}
			fclose(fp3);	
			break;
		case 'm':
			for(count = 0;count < 6;count++)
			{
				m = pow(2,arr[count]);
			if((fp1 = fopen("../input/data.txt","r"))== NULL)
			{
				printf("error");
			}
			else
			{
				for(i = 0;i < m;i++)
				{
					fscanf(fp1,"%s",str[i]);
				}
				printf("read successful!\n");
				fclose(fp1);
			}
			QueryPerformanceCounter(&t1);
			MERGE_SORT(str,0,m-1);
			QueryPerformanceCounter(&t2);
			switch(count)
				{
					case 0:if((fp2 = fopen("../output/MERGE_SORT/result_2.txt","w"))== NULL)
					printf("error\n");break;
					case 1:if((fp2 = fopen("../output/MERGE_SORT/result_5.txt","w"))== NULL)
					printf("error\n");break;
					case 2:if((fp2 = fopen("../output/MERGE_SORT/result_8.txt","w"))== NULL)
					printf("error\n");break;
					case 3:if((fp2 = fopen("../output/MERGE_SORT/result_11.txt","w"))== NULL)
					printf("error\n");break;
					case 4:if((fp2 = fopen("../output/MERGE_SORT/result_14.txt","w"))== NULL)
					printf("error\n");break;
					case 5:if((fp2 = fopen("../output/MERGE_SORT/result_17.txt","w"))== NULL)
					printf("error\n");break;
				}
			for(i = 0;i < m;i++)
				fprintf(fp2,"%s\n",str[i]);
			printf("write successful!\n");
			dt[count] = (t2.QuadPart - t1.QuadPart )/ (double)nFreq.QuadPart *1000000;    
			fclose(fp2);
			}
			if((fp3 = fopen("../output/MERGE_SORT/time.txt","w"))== NULL)
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
