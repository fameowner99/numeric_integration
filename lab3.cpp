#include <iostream>
#include <exception>
#include <cmath>
#include <chrono>

double f(const double x)
{
	return (sin(x) * sin(x) * cos(x));
}

double	simpson(const int a, const int b, int n)
{
	if (n % 2 != 0)
		throw std::runtime_error("n should be even!");

	const double dx = (double)(b - a) / n;
	double x = a;
	double sum = 0;
	int v = 4;

	sum += f(a) + f(b);
	for (int i = 1; i < n - 1; ++i)
	{
		x += dx;
		sum += v * f(x);
		v = (v == 2) ? 4 : 2;
	}
	sum = (sum * dx) / 3;
	return (sum);
}

double	rungeRule(const int a, const int b, int n, double (*integral)(const int, const int, int))
{
	double i1;
	double i2;
	bool s = false;
	const double epsilon = 0.000001;
	do
	{
		i1 = s ? i2 : integral(a, b, n) ;
		i2 = integral(a, b, n * 2);
		n *= 2;
		s = true;
	}
	while (abs(i2 - i1) > epsilon);
	return (i2);
}

double	leftRectangle(const int a, const int b, int n)
{
	const double dx = (double)(b - a) / n;
	double x = a;
	double sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += f(x);
		x += dx;
	}
	return (sum * dx);
}

int main()
{
	const int a = -10;
	const int b = 5;
	const int n = 200;
	double integral1;
	double integral2;
	using namespace std::chrono;
	high_resolution_clock::time_point t1, t2;

	try
	{

		t1 = high_resolution_clock::now();
		integral1 = rungeRule(a, b, n, simpson);
		t2 = high_resolution_clock::now();
		auto duration1 = duration_cast<milliseconds>( t2 - t1 ).count();
		t1 = high_resolution_clock::now();
		integral2 = rungeRule(a, b, n, leftRectangle);
		t2 = high_resolution_clock::now();
		auto duration2 = duration_cast<milliseconds>( t2 - t1 ).count();

		std::cout << "Simpson:" << std::endl;
		std::cout << "result = " << integral1 << ", time = " << duration1 << "ms" << std::endl;

		std::cout << "Left rectangles:" << std::endl;
		std::cout << "result = " << integral2 << ", time = " << duration2 << "ms" << std::endl;
		
	}
	catch(std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
	}

	
	return (0);
}