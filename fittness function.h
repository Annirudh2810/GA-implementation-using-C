#include<math.h>
int D=30;
int LB=-100;
int UB=100;
int OV=0;
double Rosenbrock(double *x)
{
	double s=0.0;
	int i=0;
	for(;i<D;i++)
	{
		s=s+(100*pow(pow(x[i+1]-x[i],2),2));
		s=s+pow((x[i]-1),2);
	}
	return s;
}
