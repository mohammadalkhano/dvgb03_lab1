#include "algorithm.h"
//
// Private
//
static void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
//
// Public
//

void bubble_sort(int *a, int n)
{
    // TODO: Refactoring --> Done :)
    for (int i = 0; i < n - 1; i++) {
        int swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

void insertion_sort(int *a, int n)
{
    // TODO: insertion sort
    for (int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 &&
               a[j] > key) // I bästa fall hoppa över while (det är redan sorterad (a[j] !> key)).
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key; // Välj en ny key
    }
    /*

    */
}

static int partition(int *a, int lo, int hi)
{
    int pivot = a[hi];
    int i = lo; // element mindre än pivoten

    for (int j = lo; j < hi; j++)
    {
        if (a[j] < pivot)
        {
            swap(&a[i], &a[j]);
            i++;
        }
    }
    swap(&a[i], &a[hi]);
    return i;
}

void quick_sort(int *a, int n)
{
    // TODO: quick sort
    int last = n - 1;
    if (0 < last)
    {
        int p = partition(a, 0, last);

        quick_sort(a, p);
        quick_sort(a + p + 1, last - p);
    }
}

bool linear_search(const int *a, int n, int v)
{
    for (int i = 0; i < n; i++)
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
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (a[mid] == v)
        {
            return true;
        }
        else if (a[mid] < v)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return false; // not found aka out of bounds
}
