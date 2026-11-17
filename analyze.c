#include "analyze.h"
#include "algorithm.h"
#include <stdlib.h>
#include <time.h>
//
// Private
//
typedef void (*sort_algorithm)(int *arr, int n);
// Returnerar sorterings algoritmen, eller NULL om a inte är en sortering.
static sort_algorithm choose_algorithm(algorithm_t a)
{
    switch (a)
    {
    case bubble_sort_t:
        return bubble_sort;
    case insertion_sort_t:
        return insertion_sort;
    case quick_sort_t:
        return quick_sort;
    default:
        return NULL;
        // TODO: sökalgoritmerna
    }
}
// Fyller arr med indata.
static void generate_casebased_data(int *arr, int n, case_t c)
{
    for (int i = 0; i < n; i++)
    {
        switch (c)
        {
        case best_t:
            arr[i] = i;
            break; // sorterad
        case worst_t:
            arr[i] = n - i;
            break; // omvänt sorterad
        case average_t:
            arr[i] = rand() % n;
            break; // slumpmässig
        }
    }
}

static double now()
{
    struct timespec time_space;

    clock_gettime(CLOCK_MONOTONIC, &time_space);
    return time_space.tv_sec + time_space.tv_nsec / 1E9;
}

// Returnerar medeltiden i sekunder över ITERATIONS sorteringar.
static double time_sort(sort_algorithm sort, case_t c, int *arr, int n)
{
    double total = 0.0;

    for (int i = 0; i < ITERATIONS; i++)
    {
        generate_casebased_data(arr, n, c); // ny indata varje gång, eftersom sorteringen ändrar arr
        double start = now();
        sort(arr, n);
        total += now() - start;
    }
    return total / ITERATIONS;
}

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{
    //
    sort_algorithm sort = choose_algorithm(a);

    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        int size = SIZE_START << i; // storleken dubblas för varje rad
        int *arr = malloc(size * sizeof(*arr));

        buf[i].size = size;
        if (arr != NULL && sort != NULL)
        {
            buf[i].time = time_sort(sort, c, arr, size);
        }
        else
        {
            buf[i].time = MEASURE_FAILED;
        }
        free(arr);
    }
}
