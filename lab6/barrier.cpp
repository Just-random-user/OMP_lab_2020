#include <iostream>
#include <omp.h>
#include <time.h>

using namespace std;

int* initialize(int* arr, int size);

int main()
{
	int size = 0;
	std::cout << "Enter the size: ";
	cin >> size;
	int* A = new int[size];
	int* B = new int[size];
	int* C = new int[size];
	initialize(A, size);
	initialize(B, size);
	initialize(C, size);

	double res = 1;
	int i = 0;
	double under_res = 1;
	double res_thr = 1;
	clock_t start = clock();
#pragma omp parallel private(i) firstprivate(res_thr, under_res)
	{
#pragma omp for
		for (i = 0; i < size; i++)
		{
			if (A[i] % 2 == 0)
			{
				if (C[i])
					under_res = double(B[i]) / C[i];
				else
					continue;
			}
			else
			{
				under_res = long long(B[i]) + A[i];
			}
			if (under_res)
			{
				res_thr *= double(under_res);
			}
		}
#pragma omp barrier
		res *= res_thr;
	}
	clock_t stop = clock();
	std::cout << "Passed time: " << double((stop - start) * 1000) / CLOCKS_PER_SEC << "ms";
}

int* initialize(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand()/100;
	}
	return arr;
}