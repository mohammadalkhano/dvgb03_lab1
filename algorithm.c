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
    return false; // TODO: binary search
}
