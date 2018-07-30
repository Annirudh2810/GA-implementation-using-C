#include<math.h>
double Schumer(double *x,int D)
{
	int i;double s=0;
	int d=D;
	for(i=0;i<d;i++)
	{
		s=s+pow(x[i],4);
	}
	return s;
}
double Greiwank(double *x,int D)
{
	int i,d=D;
	double p=0.0,s=0.0,z=0.0;
	for(i=0;i<d;i++)
	{
		s=s+(pow(x[i],2))/4000;
		p=p*(cos(x[i]/i+1));
	}
	z=s-p+1;
	return z;
}
double FirstHolder(double *x)
{
	const double pi = 4.0 * atan(1.0);
	double s=0;
	s=-fabs(cos(x[0]*cos(x[1]*exp(fabs(1-(pow((fabs(x[0]+x[1])),0.5))/pi)))));
	return s;	
}
double Rosenbrock(double *x,int D)
{
	double s=0.0;
	int i,d=D;
	for(i=0;i<d;i++)
	{
		s=s+(100*pow((x[i+1]-x[i*2]),2));
		s=s+pow((x[i]-1),2);
		return s;
	}
}
