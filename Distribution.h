#pragma once
class Distribution
{
public:
	double EvenGenerator();
	double EvenGenerator( int start,  int end);
	double ExponentialGenerator( int ave);
	double NormalGenerator(double m, double d);
	double GeometricGenerator(double p);
	int get_kernel();
	Distribution(double kernel);
	~Distribution()=default;
private:
	int kernel_;
	int a_;
	int q_;
	int m_;
	int r_;
};

