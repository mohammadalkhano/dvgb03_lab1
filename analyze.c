#include "analyze.h"
#include "algorithm.h"
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
//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n) {}
