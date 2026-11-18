#include "analyze.h"
#include "algorithm.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
//
// Private
//
typedef void (*sort_algorithm)(int *arr, int n);
typedef bool (*search_algorithm)(const int *arr, int n, int v);
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
    }
}
static search_algorithm choose_search_algorithm(algorithm_t a)
{
    switch (a)
    {
    case linear_search_t:
        return linear_search;
    case binary_search_t:
        return binary_search;
    default:
        return NULL;
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
static int generate_target(int n, case_t c)
{
    switch (c)
    {
    case best_t:
        return 0;
        break;
    case worst_t:
        return n - 1;
        break;
    case average_t:
        return (int)((n / 2) + 1);
        break;
    default:
        return -2;
        break;
    }
}

static double timer_now()
{
    struct timespec time_space;

    clock_gettime(CLOCK_MONOTONIC, &time_space);
    return (double)(time_space.tv_sec + time_space.tv_nsec / MILJARD);
}

// Returnerar medeltiden i sekunder över ITERATIONS sorteringar.
static double time_sort(sort_algorithm sort_algoritm, case_t c, int *arr, int n)
{
    double total = 0.0;

    for (int i = 0; i < ITERATIONS; i++)
    {
        generate_casebased_data(arr, n, c); // ny indata varje gång, eftersom sorteringen ändrar arr
        double start = timer_now();         // Starta mätningen (arrival)
        sort_algoritm(arr, n);
        total += timer_now() - start;

        // long delta = (stopp.tv_sec*MILJARD+stopp.tv_nsec) - (start.tv_sec*MILJARD+start.tv_nsec);
    }
    return total / ITERATIONS;
}

static double time_search(search_algorithm search, case_t c, int *arr, int n)
{
    double total = 0.0;

    for (int i = 0; i < ITERATIONS; i++)
    {
        generate_casebased_data(arr, n, c);
        int target = generate_target(n, c);
        double start = timer_now(); // Starta mätningen (arrival)
        search(arr, n, target);
        total += timer_now() - start;
    }
    return total / ITERATIONS;
}

//
// Public
//
void benchmark(algorithm_t a, case_t c, result_t *result, int n)
{
    sort_algorithm sort_algorithm = choose_algorithm(a);
    search_algorithm search_algorithm = choose_search_algorithm(a);
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        int size = SIZE_START * (pow(2, i)); // storleken dubblas för varje rad (start * 2^i)
        int *arr = malloc(size * sizeof(*arr));

        result[i].size = size;
        if (arr != NULL && sort_algorithm != NULL)
        {
            result[i].time = time_sort(sort_algorithm, c, arr, size);
        }
        // new
        else if (arr != NULL && search_algorithm != NULL)
        {
            result[i].time = time_search(search_algorithm, c, arr, size);
        }

        else
        {
            result[i].time = MEASURE_FAILED;
        }
        free(arr);
    }
}
