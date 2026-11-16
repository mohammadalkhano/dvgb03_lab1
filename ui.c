#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>
#include <time.h>


//delete this
#include "algorithm.h"
#include "mockdata.h"


//
// Private
//
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i=0; i<num_options; i++) {
		printf("    %c) %s\n", 'a'+i, options[i]);
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

		"Linear sort best case",
		"Linear sort worst case",
		"Linear sort average case",

		"Binary sort best case",
		"Binary sort worst case",
		"Binary sort average case",
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

//
// Public
//
void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];
	clock_t start_time, end_time;
	

	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
			// House keeping
			case 'a':
				show_menu = true;
				break;
			// Exit
			case 'b':
				running = false;
				break;
			//  Bubble BEST case
			case 'c':
				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
				
				//test bubble sort to delete later
				//printf("innan sortering... \n");
				 start_time = clock();
				ui_print_result(mockdata_best);
				bubble_sort(mockdata_best, MOCKDATA_SIZE);
				ui_print_result(mockdata_best);
				end_time = clock();
				printf("Bubble sort best case time: %f seconds\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);
				printf("todo> implemenet BE + present results in FE\n");
				break;
			// BUBBLE WORST CASE
			case 'd':
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
				start_time = clock();

				//test bubble sort to delete later
				//printf("innan sortering... \n");
				ui_print_result(mockdata_worst);
				bubble_sort(mockdata_worst, MOCKDATA_SIZE);
				ui_print_result(mockdata_worst);
				end_time = clock();
				printf("Bubble sort worst case time: %f seconds\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);
				printf("todo> implemenet BE + present results in FE\n");
				break;

			// Bubble average case
			case 'e':
				benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
				start_time = clock();
				//test bubble sort to delete later
				//printf("innan sortering... \n");
				ui_print_result(mockdata_average);
				bubble_sort(mockdata_average, MOCKDATA_SIZE);
				ui_print_result(mockdata_average);
				end_time = clock();
				printf("Bubble sort average case time: %f seconds\n", ((double)(end_time - start_time)) / CLOCKS_PER_SEC);
				printf("todo> implemenet BE + present results in FE\n");
				break;






				//Insertion sort best case
				case 'f':
				benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
				//test insertion sort to delete later
				printf("innan sortering... \n");
				ui_print_result(mockdata_best);
				insertion_sort(mockdata_best, MOCKDATA_SIZE);
				ui_print_result(mockdata_best);
				printf("todo> implemenet BE + present results in FE\n");
				break;

				//quick sort best case
				case 'i':
				benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
				//test quick sort to delete later
				printf("innan sortering... \n");
				ui_print_result(mockdata_best);
				quick_sort(mockdata_best, MOCKDATA_SIZE);
				ui_print_result(mockdata_best);
				printf("todo> implemenet BE + present results in FE\n");
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
void ui_print_result(int *a)
{
	for (int i = 0; i < 10; i++) {
		printf("%d  ,", a[i]);
	}
	printf("\n");
}
