all: program1

program1: src/radix_sort.c
	gcc -g -Wall -fopenmp src/radix_sort.c -o radix_sort