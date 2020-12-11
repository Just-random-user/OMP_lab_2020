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
	clock_t start = clock();
	omp_lock_t lock1;
	omp_init_lock(&lock1);
#pragma omp parallel
	{
#pragma omp for private(i, under_res)
		for (i = 0; i < size; i++)
		{
			if (A[i] % 2 == 0)
			{
				if (C[i])
					under_res = B[i] / C[i];
				else
					continue;
			}
			else
			{
				under_res = long long(B[i]) + A[i];
			}
			if (under_res)
			{
				omp_set_lock(&lock1);
				res *= under_res;
				omp_unset_lock(&lock1);
			}
		}
	}
	clock_t stop = clock();
	omp_destroy_lock(&lock1);
	std::cout << "Passed time: " << double((stop - start) * 1000) / CLOCKS_PER_SEC << "ms";
}

int* initialize(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand();
	}
	return arr;
}