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

static void generate_quick_best(int *arr, int n, int first)
{
    if (n <= 0)
    {
        return;
    }
    int left = n / 2;         // antal värden mindre än pivoten
    int right = n - 1 - left; // antal värden större än pivoten

    generate_quick_best(arr, left, first);
    generate_quick_best(arr + left + 1, right, first + left + 1);
    arr[left] = arr[n - 1];
    arr[n - 1] = first + left; // pivoten = medianen
}

// Fyller arr med indata.
static void generate_casebased_data(int *arr, int n, algorithm_t a, case_t c)
{
    if (a == quick_sort_t && c == best_t)
    {
        generate_quick_best(arr, n, 0);
        return;
    }
    for (int i = 0; i < n; i++)
    {
        switch (c)
        {
        case best_t:
            // sorterad
            arr[i] = i;
            break;
        case worst_t:
            // omvänt sorterad
            arr[i] = (a == quick_sort_t) ? i : n - i; // Quick = O(n^²) = Sorterad array
            break;
        case average_t:
            arr[i] = rand() % n; // slumpmässigt
            break;
        }
    }
}
static int generate_search_target(algorithm_t a, case_t c, int n)
{
    switch (c)
    {
    case best_t:
        return a == linear_search_t ? 0 : 2 * ((n - 1) / 2);
    case average_t:
        return 2 * (rand() % n);
    case worst_t:
    default:
        return 2 * (rand() % n) + 1;
    }
}

static double timer_now()
{
    struct timespec time_space;

    clock_gettime(CLOCK_MONOTONIC, &time_space);
    return (double)(time_space.tv_sec + time_space.tv_nsec / MILJARD);
}

// Returnerar medeltiden i sekunder över ITERATIONS sorteringar av en sortering algorithm.
static double time_sort(sort_algorithm sort_algoritm, algorithm_t a, case_t c, int *arr, int n)
{
    double total = 0.0;
    double start = 0.0;

    for (int i = 0; i < ITERATIONS; i++)
    {
        // ny indata varje gång eftersom sorteringen ändrar arrayen
        generate_casebased_data(arr, n, a, c);
        start = timer_now(); // Starta mätningen (process arrival)
        sort_algoritm(arr, n);
        total += timer_now() - start;

        // long delta = (stopp.tv_sec*MILJARD+stopp.tv_nsec) - (start.tv_sec*MILJARD+start.tv_nsec);
    }
    return total / ITERATIONS;
}
// Returnerar medeltiden i sekunder över ITERATIONS sökningar av en sökning algorithm.
static double time_search(search_algorithm search_algorithm, algorithm_t a, case_t c,
                          const int *arr, int n)
{
    int *targets = malloc(SEARCH_REPEATS * sizeof(*targets));
    double total = 0.0;

    if (targets == NULL)
    {
        return MEASURE_FAILED;
    }
    for (int i = 0; i < ITERATIONS; i++)
    {
        for (int k = 0; k < SEARCH_REPEATS; k++)
        {
            targets[k] = generate_search_target(a, c, n);
        }
        double start = timer_now();
        for (int k = 0; k < SEARCH_REPEATS; k++)
        {
            search_algorithm(arr, n, targets[k]);
        }
        total += timer_now() - start;
    }
    free(targets);
    return total / ((double)ITERATIONS * SEARCH_REPEATS); // SEARCH_REPEATS sökningar mäts
    // åt gången, ITERATIONS gånger. Sökvärdena tas fram före tidtagningen.
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
            result[i].time = time_sort(sort_algorithm, a, c, arr, size);
        }
        // new
        else if (arr != NULL && search_algorithm != NULL)
        {
            result[i].time = time_search(search_algorithm, a, c, arr, size);
        }
        else
            result[i].time = MEASURE_FAILED;
        free(arr);
    }
}
