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
    if (n < 2)
        return;

    int pivot = a[n / 2];   // copy the pivot value, don't move it
    int i = 0;
    int j = n - 1;

    while (i <= j)
    {
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i <= j)
        {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    }

    // after the loop, j < i and the array is split into two parts:
    // a[0..j] and a[i..n-1]
    quick_sort(a, j + 1);
    quick_sort(a + i, n - i);
}
    


bool linear_search(const int *a, int n, int v)
{
    for (int i=0; i <= n; i++)
    {
        if (a[i] == v)
        {
            return true; // Found the value
        }
    }
    return false; 
}

bool binary_search(const int *a, int n, int v)
{
    int low =0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int value = a[mid];
        if (value < v)
        {
            low = mid + 1;
        }
        else if (value > v)
        {
            high = mid - 1;
        }
        else
        {
            return true; // Found the value
        }
    }
    
    return false; // TODO: binary search
}
