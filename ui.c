#include "ui.h"
#include "analyze.h"
#include "io.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>


//
// Private
//
static void ui_invalid_input() { printf("info> bad input\n"); }

static void ui_exit() { printf("info> bye\n"); }

static char ui_get_choice()
{
    char buf[3];

    printf("input> ");
    return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
    while (n-- > 0)
    {
        putchar(c);
    }
    putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
    int i;

    for (i = 0; i < num_options; i++)
    {
        printf("    %c) %s\n", 'a' + i, options[i]);
    }
}

static void ui_menu()
{
    const char *options[] = {
        "Menu",
        "Exit\n",

        "Bubble sort best case",
        "Bubble sort worst case",
        "Bubble sort average case",

        "Insertion sort best case",
        "Insertion sort worst case",
        "Insertion sort average case",

        "Quick sort best case",
        "Quick sort worst case",
        "Quick sort average case",

        "Linear search best case",
        "Linear search worst case",
        "Linear search average case",

        "Binary search best case",
        "Binary search worst case",
        "Binary search average case",
    };

    ui_line('=', MENU_WIDTH);
    ui_menu_options(options, sizeof(options) / sizeof(char *));
    ui_line('-', MENU_WIDTH);
}

// Skriver ut tiden och tiden delad med varje kandidatfunktion f(n).
// Rätt big-O är den kolumn som konvergerar mot en konstant.
void print_result(const result_t *result, int n)
{
    ui_line('=', MENU_WIDTH);
    printf("size \ttime T(s)\tT/log n\tT/n\tT/n log n \tT/n^2\n");
    ui_line('-', MENU_WIDTH);
    for (int i = 0; i < n; i++)
    {
        double size = result[i].size;
        double t = result[i].time;

        if (t == MEASURE_FAILED)
        {
            printf("%d %s\n", result[i].size, "failed");
            continue;
        }
        printf("%d \t %lf %12.3e %12.3e %12.3e %12.3e\n", result[i].size, t, t / log2(size),
               t / size, t / (size * log2(size)), t / (size * size));
    }
    ui_line('=', MENU_WIDTH);
}

static void ui_benchmark(algorithm_t a, case_t c, result_t *result)
{
    benchmark(a, c, result, RESULT_ROWS);
    print_result(result, RESULT_ROWS);
}
//
// Public
//
void ui_run()
{
    bool running, show_menu;
    result_t result[RESULT_ROWS];

    show_menu = true;
    running = true;
    while (running)
    {
        if (show_menu)
        {
            show_menu = false;
            ui_menu();
        }
        switch (ui_get_choice())
        {
        // House keeping
        case 'a':
            show_menu = true;
            break;
        case 'b':
            running = false;
            break;
        // Bubble sort
        case 'c':
            ui_benchmark(bubble_sort_t, best_t, result);
            break;
        case 'd':
            ui_benchmark(bubble_sort_t, worst_t, result);
            break;
        case 'e':
            ui_benchmark(bubble_sort_t, average_t, result);
            break;
            // insertion sort
        case 'f':
            ui_benchmark(insertion_sort_t, best_t, result);
            break;
        case 'g':
            ui_benchmark(insertion_sort_t, worst_t, result);
            break;
        case 'h':
            ui_benchmark(insertion_sort_t, average_t, result);
            break;
        // insertion sort
        case 'i':
            ui_benchmark(quick_sort_t, best_t, result);
            break;
        case 'j':
            ui_benchmark(quick_sort_t, worst_t, result);
            break;
        case 'k':
            ui_benchmark(quick_sort_t, average_t, result);
            break;
        // linear search
        case 'l':
            ui_benchmark(linear_search_t, best_t, result);
            break;
        case 'm':
            ui_benchmark(linear_search_t, worst_t, result);
            break;
        case 'n':
            ui_benchmark(linear_search_t, average_t, result);
            /*int n = 5;
            int v = 3;
            int a[] = {1, 2, 3, 4, 5};
            int i = linear_search(a, n, v);
            printf("info> found value %d at index %d\n", v, i);*/
            break;
        // Invalid input
        default:
            show_menu = false;
            ui_invalid_input();
            break;
        }
    }
    ui_exit();
}
