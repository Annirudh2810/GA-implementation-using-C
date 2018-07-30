#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<omp.h>
#include"fittness function.h"
#define NUM_THREADS 2
int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}
double cross(double a1[][150],double f1[150],FILE * fp1)
{
	FILE * fp;
	fp=fp1;
	int i,j;
	double c=0.0;
	c=(rand()%(150 - 1 + 1)+1);
	//copyng array
	//#pragma omp parallel
	//{
		int I,J;
		double e[250][150],f2[150];
	//#pragma omp parallel for
		for(I=0;I<250;I++)
		{
			for(J=0;J<150;J++)
			{
				e[I][J]=a1[I][J];
			}
		}
		for(J=0;J<2;J++)
		{
			f2[J]=f1[J];
		}
	//}
	//crossover selection
	for(i=0;i<c;i++)
	{		
		e[1][i]=a1[1][i];
	}
	for(i=c+1;i<150;i++)
	{
		e[1][i]=a1[2][i];
	}
	for(i=0;i<c;i++)
	{		
		e[2][i]=a1[2][i];
	}
	for(i=c+1;i<150;i++)
	{
		e[2][i]=a1[1][i];
	}
	f2[1]=Rosenbrock(*e);
	f2[2]=Rosenbrock(*e);
	if(f2[1]>f1[1])
	{
		for(i=0;i<150;i++)
		{
			a1[1][i]=e[1][i];
		}
		fprintf(fp,"Chromosomes  **********************************************\n");
		for(i=0;i<250;i++)
		{
			for(j=0;j<150;j++)
			{
				fprintf(fp,"%lf  ",a1[i][j]);
			}
			fprintf(fp,"\n");
		}
		fprintf(fp,"\n");
		fprintf(fp,"Fitness ***************************************************\n");
		for(j=0;j<150;j++)
		{
			fprintf(fp,"%lf\n",f1[j]);
		}
	}
	else if(f2[2]>f1[2])
	{
		for(i=0;i<150;i++)
		{
			a1[2][i]=e[2][i];
		}
		fprintf(fp,"Chromosomes  **********************************************\n");
		for(i=0;i<250;i++)
		{
			for(j=0;j<150;j++)
			{
				fprintf(fp,"%lf  ",a1[i][j]);
			}
			fprintf(fp,"\n");
		}
		fprintf(fp1,"Fitness ***************************************************\n");
		for(j=0;j<150;j++)
		{
			fprintf(fp,"%lf\n",f1[j]);
		}
	}	
	/*else if( f2[1]==f1[1] && f2[2]==f1[2] )
	{
		fprintf(fp1,"sab same hai ;-) ");
	}*/
}
double mutate(double a1[250][150],double f1[150],FILE * fp2)
{
	FILE * fp;
	fp=fp2;
	double r,p,fit=0.0;
		int i,j;
		double ar[250][150],fi[150];
			for(i=0;i<250;i++)
			{
				for(j=0;j<150;j++)
				{
					ar[i][j]=a1[i][j];
				}
			}
			for(j=0;j<150;j++)
			{
				fi[j]=f1[j];
			}
	r=(rand()%(250 - 1 + 1)+1);
	p=rand()%(150 - 1 + 1)+1;
	ar[(int) r][(int) p]=round((rand()%(UB - LB + 1)+LB));
	fit=Rosenbrock(*ar);
	if(fit>fi[(int) p])
	a1[(int) r][(int) p]=ar[(int) r][(int) p];
	fprintf(fp,"After mutation **********************************************\n\n");
	fprintf(fp,"Chromosomes  **********************************************\n");
		for(i=0;i<250;i++)
		{
			for(j=0;j<150;j++)
			{
				fprintf(fp,"%lf  ",a1[i][j]);
			}
			fprintf(fp,"\n");
		}
		fprintf(fp,"\n");
		fprintf(fp,"Fitness ***************************************************\n");
		for(j=0;j<150;j++)
		{
			fprintf(fp,"%lf\n",f1[j]);
		}
}
int main()
{
	FILE * fp;
	fp=fopen("D:\\result11.txt","w");
	clock_t t=clock();
	//double start, end;
	double a[250][150];
	double f[150];
	int i,j,itr=100;
	//start = omp_get_wtime();
	#pragma omp parallel
	{
		int I,J;
		#pragma omp parallel for
		for(I=0;I<250;I++)
		{
			for(J=0;J<150;J++)
			{
				a[I][J]=round((rand()%(UB - LB + 1)+LB));
				f[J]=Rosenbrock(*a);
			}
		}
	}
	//end = omp_get_wtime()-start;

	qsort(f,150,sizeof(double),comp);
	for(i=0;i<itr;i++)
	{
		cross(a,f,fp);
		mutate(a,f,fp);
	}
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	fprintf(fp,"*************************************************");
	fprintf(fp,"Time taken = %lf\n",time_taken);
	//fprintf(fp,"Compute Time: %f seconds\n", end);
	fclose(fp);
	printf("NOW OPEN FILE");
	getch();
	return 0;
}
