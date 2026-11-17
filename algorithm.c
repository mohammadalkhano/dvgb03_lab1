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
    // TODO: Refactoring --> swap func??
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
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
    for (int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key) // I bästa fall hoppa över while (det är redan sorterad (a[j] !> key)).
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key; // Välj en ny key
    }
    /*

    */
}

void quick_sort(int *a, int n)
{
    // TODO: quick sort

        int i, j, x, y, z, pivot, temp;

    if (n < 2)
        return;                       /* 0 or 1 element: already sorted */

     x = a[0];
    y = a[n / 2];
    z = a[n - 1];
    if ((x <= y && y <= z) || (z <= y && y <= x))
        pivot = y;
    else if ((y <= x && x <= z) || (z <= x && x <= y))
        pivot = x;
    else
        pivot = z;

}
    


bool linear_search(const int *a, int n, int v)
{
    return false; // TODO: linear search
}

bool binary_search(const int *a, int n, int v)
{
    return false; // TODO: binary search
}
