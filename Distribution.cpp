#include "stdafx.h"
#include "Distribution.h"
#include <cmath>



Distribution::Distribution(double kernel):kernel_(kernel)
{
	a_ = 16807;
	q_ = 127773;
	m_ = 2147483647;
	r_ = 2836;
}
int Distribution::get_kernel()
{
	return kernel_;
}




double Distribution::EvenGenerator()
{
	
	int const  h =kernel_/q_;
	kernel_ = a_ * (kernel_ - q_ * h) - r_ * h;
	if (kernel_ < 0) kernel_ = kernel_ + (m_);
	return (static_cast<double>(kernel_)/ m_);
}
double Distribution::EvenGenerator(const int start, const int end)
{
	return (EvenGenerator()*(end - start) + start);
}

double Distribution::ExponentialGenerator(const int ave)
{
	double lambda=1.0/ave;
	double e = EvenGenerator();		//metoda odwróconej dystrybuanty
	return (-ave*log(e));

}
double Distribution::NormalGenerator(const double m, const double d)
{/*
	double w = 0;
	double ERF = 0;
	ERF= erf(2 * EvenGenerator() - 1);	//dlaczego tu jest b³¹d dla 5896 iteracji
	w= (d * sqrt(2)*pow(ERF, -1)+ m);
	return w;*/
	
	double u2;
	double x;
	do
	{
		double u1 = EvenGenerator();
		u2 = EvenGenerator();
		x = -log(u1);
	} while (!(u2 <= exp(-(pow(x - 1, 2) / 2))));
	if (EvenGenerator() < 0.5) x = x * -1.0;
	return (x*d +m);
}

double Distribution::GeometricGenerator(double p)
{
	int i = 0;
	while((1/p) < EvenGenerator())
	{
		i++;
	}
	return i + 1;
}
