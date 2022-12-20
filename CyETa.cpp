#include <iostream>
#include<fstream>
using namespace std;
void create(ifstream& f,int m, double** A, double** B, double* z) 
{
	if (!f)
	{
		cout << "Невозможно открыть файл";
		system("pause");
		exit(-1);
	}
	else 
	{
		int i, j;
		for (i = 0; i < m; i++)
			for (j = 0; j < m; j++)
				f >> A[i][j];
		for (i = 0; i < m; i++)
			for (j = 0; j < m; j++)
				f >> B[i][j];
		for (i = 0; i < m; i++)
			f >> z[i];
	}
}

void show(ofstream& f, int m, double* z)
{
	int i;
	f << "y = ";
	for (i = 0; i < m; i++)
		f << z[i]<<" ";
}
double F(double* a, int m) 
{
	int i;
	double p = 1;
	for (i = 0; i < m; i++)
		p *= (1 + a[i]) / (1 + a[i] * a[i]);
	return p;
}

double* multiplication(double** D, double* b, int m) 
{
	double* c = new double[m];
	int i, j;
	for (i = 0; i < m; i++) {
		c[i] = 0;
		for (j = 0; j < m; j++)
			c[i] += D[i][j] * b[j];
	}
	return c;
}

double* function(int i, int m, double c, double** A, double** B, double* z) 
{
	if (i < 5) {
		if (F(z, m) > c)
			z = multiplication(A, z, m);
		else
			z = multiplication(B, z, m);
		return function(i + 1, m, c, A, B, z);
	}
	else
		return z;
}

int main() 
{
	setlocale(LC_ALL, "RUS");
	ifstream in("arb.txt");
	ofstream out("out.txt");
	int m;
	double c;
	in >> m;
	in >> c;
	double* z = new double[m];
	double* ans = new double[m];
	double** A = new double* [m];
	double** B = new double* [m];
	for (int i = 0; i < m; i++)
	{
		A[i] = new double[m];
		B[i] = new double[m];
	}
	create(in, m, A, B, z);
	ans = function(0, m, c, A, B, z);
	show(out, m, ans);
	system("pause");
	return 0;
}