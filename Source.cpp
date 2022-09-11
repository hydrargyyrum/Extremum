#include <iostream>
using namespace std;


const double goldenRatio = (1 + sqrt(5)) / 2;



float f(float x)
{
	return  ((x - 2) * (x - 2));

}


///////////////////////////////////// ‘ибоначчи ///////////////////////////////////////////////
float fib(int n)
{
	if (n <= 0) return 0;
	if (n == 1) return 1;
	return fib(n - 1) + fib(n - 2);
}

int findN(float a, float b, float l)
{
	int n = 1;
	while (fib(n) < ((b - a) / l)) n++;
	return n;
}

float metodFib(float a, float b, float eps, float (*f)(float))
{
	
	int n = findN(a, b, eps);

	float   y = a + fib(n - 2) / fib(n) * (b - a), 
		z = a + fib(n - 1) / fib(n) * (b - a); 

	for (int k = 0; k < n; k++)
	{
		if (f(y) <= f(z))
		{
			b = z;
			z = y;
			y = a + fib(n - k - 3) / fib(n - k - 1) * (b - a);
		}
		else
		{
			a = y;
			y = z;
			z = a + fib(n - k - 2) / fib(n - k - 1) * (b - a);
		}

		if (k == n - 3)
		{
			y = (a + b) / 2;
			z = y + eps;

			if (f(y) <= f(z)) b = z;
			else a = y;
			return ((a + b) / 2);
		}
	}
}




/////////////////////////////////////////////  золотое сечение ///////////////////////////////////////////////////

float gold(float a, float b, float eps, float (*p)(float))
{
	double y, z;
	while (fabs(b-a) > eps)
	{
		y = a + 0.38196 * (b - a);
		z = a + b - y;
		if (f(y) <= f(z)) {

			b = z;
			y = a +b - y;
			z = y;
		}
		else {
			a = y;
			y = z;
			z = a + b - z;
		}

	}
	return (b + a) / 2;
}

//////////////////////////////////// метод равномерного поиска /////////////////////////////////////////////////
float x_(float a, float b, int N, int i)
{
	float x;
	if (i > 0) {
		 x = a + i * (b - a) / (N + 1);
	}
	else x = a;
	return x;
}
float rav(float a, float b, int N, float (*p)(float))
{
	float x, xmin;
	for (int i = 0; i < N; i++)
	{
		if (f(x_(a, b, N, i)) < f(x_(a, b, N, i - 1))) {
			xmin = x_(a, b, N, i);
		}
	}
	return xmin;
}

/////////////////////////////////////////метод делени€ интервала пополам///////////////////////////////////////
float del(float a, float b, float eps, float (*p)(float))
{	double x, y, z, l;
	while (fabs(b - a) > eps) {
		x = (a + b) / 2;
		l = fabs(b - a);
		y = a + l / 4;
		z = b - l / 4;
		if (f(y) < f(x)) {
			b = x;
			x = y;
		}
		else {
			if (f(z) < f(x)) {
				a = x;
				x = z;
			}
			else {
				a = y;
				b = z;
			}
		}

	}
	return x;
}

///////////////////////////////////////метод дихотомии//////////////////////////////////////////////////////////
float dih(float a, float b, float eps, float l, float (*p)(float))
{
	float y, z;
	while (fabs(b-a)>l)
	{
		y = (a + b - eps) / 2;
		z = (a + b + eps) / 2;
		if (f(y) <= f(z))
		{
			b = z;
		}
		else {
			a = y;
		}
	}
	return (a + b) / 2;
}

int main()
{
	float a = -11;
	float b = 10;
	float eps = 0.00001;
	float l = 0.001;
	int N = 200;
	cout.setf(ios::fixed);
	cout << "extr min=" << metodFib(a, b, eps, f) << " f(extr)=" << f(metodFib(a, b, eps, f)) << endl;
	cout << "extr min=" << gold(a, b, eps, f) << " f(extr)=" << f(gold(a, b, eps, f)) << endl;
	cout << "extr min=" << rav(a, b, N, f) << " f(extr)=" << f(rav(a, b, N, f)) << endl;
	cout << "extr min=" << del(a, b, eps, f) << " f(extr)=" << f(del (a, b, eps, f)) << endl;
	cout << "extr min=" << dih(a, b, eps,l, f) << " f(extr)=" << f(dih(a, b, eps,l, f)) << endl;

	return 0;
}
