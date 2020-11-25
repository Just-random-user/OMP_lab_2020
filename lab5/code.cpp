#include <iostream>
#include <omp.h>
#include <time.h>

using namespace std;

int* initialize(int* arr, int size);

int main()
{
	int size = 0;
	cout << "Enter the size: ";
	cin >> size;
	int* A = new int[size];
	int* B = new int[size];
	int* C = new int[size];
#pragma omp parallel
	{
		initialize(A, size);
		initialize(B, size);
		initialize(C, size);
	}

	double res = 1;
	int i = 0;
	double under_res = 1;
	clock_t start = clock();
#pragma omp parallel
	{
#pragma omp sections private(i, under_res) reduction(*:res)
		{
#pragma omp section
			for (i = 0; i < size; i++)
			{
				if (A[i] % 2 == 0)
				{
					if (C[i])
						under_res = B[i] / C[i];
					else
						continue;
					if (under_res)
						res *= under_res;
				}
			}
#pragma omp section
			for (i = 0; i < size; i++)
			{
				if (A[i] % 2 != 0)
				{
					under_res = long long(B[i]) + A[i];
					if (under_res)
						res *= under_res;
				}
			}
		}
	}
	clock_t stop = clock();
	cout << "Passed time: " << double((stop - start) * 1000) / CLOCKS_PER_SEC << "ms";
}

int* initialize(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand();
	}
	return arr;
}
