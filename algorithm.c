#include "algorithm.h"

//
// Private
//

//
// Public
//
void bubble_sort(int *a, int n)
{
	int i, j, tmp;

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1 - i; j++){
			if (a[j] > a[j + 1]) {
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
		
	}
}

void insertion_sort(int *a, int n)
{
	// TODO: insertion sort
	for ( int i=1; i<n; i++){
		int temp = a[i];
		int j = i - 1;

		while (j >= 0 && a[j] > temp) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;
	}
	
}

void quick_sort(int *a, int n)
{
	// TODO: quick sort
	int i, j, pivot, tmp;
        if (n <= 1)
        return;
	pivot = a[n - 1];
    i = 0;

	for (j = 0; j < n - 1; j++)
    {
        if (a[j] < pivot)
        {
            i++;

            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }

    tmp = a[i];
    a[i] = a[n - 1];
    a[n - 1] = tmp;

    quick_sort(a, i);
    quick_sort(a + i + 1, n - i - 1);

    }
}

bool linear_search(const int *a, int n, int v)
{
	return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{
	return false; // TODO: binary search
}
