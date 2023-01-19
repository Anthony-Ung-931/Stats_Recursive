/*  Stats - Recursive
    
    Takes 10 numbers and prints the arithmetic mean, the smallest,
      and the largest number.

    The purpose of this program is for me to get some practice with
      recursion. */

#include <stdio.h>

/* A switch where I can enable and disable debugging output
     by commenting out "#define DEBUG".
   Borrowed from my heap allocator.*/
/*
#define DEBUG
*/

#ifdef DEBUG
#define dbg_printf(...) printf(__VA_ARGS__)

#else
#define dbg_printf(...)

#endif

int NUM_INTS = 10;

/*  This is a global array of 10 ints.
    I am not allowed to declare a NUM_INTS constant
      and use that to generate the size of the array
      on repl.it.*/
int data[10];

/*  The first entry records the sum of the numbers in the array.
    The second entry records the number of elements found.
    The third entry records the minimum number in the array.
    The fourth entry records the maximum number in the array.*/
int statsHelper[4];

/* Style preference: I use underscore between words in function
                        names and camelCase in variable names
                        so it is easy for me to distinguish the two.*/
void fill_ints(int* array, int index, int size);
void get_stats(int* array, int index, int size);
void print_stats();

int main(void) {
  printf("Please enter %d numbers.\n", NUM_INTS);
  /* 0 is not a "magic number" because 0 is the start of the array. */
  fill_ints(data, 0, NUM_INTS);

  get_stats(data, 0, 10);

  print_stats();
  return 0;
}

/*    Recursively fills an array of ints for the requested size.
      Each method call writes to array[size]. 
      It is the caller's responsibility to make sure that
        size is equal to or smaller than the length of the array. */
void fill_ints(int* data, int index, int size) {
  /*  Base case, when the index is equal to or greater than the size.*/
  /*  Also returns to the caller if index was negative.*/
  if((index >= size) || (index < 0)) {
    return;
  }
  else {
    int* target = (data + index);
    dbg_printf("%p\n", target);
    printf("Please enter an integer: ");
    scanf("%d", target);
    
    index++;
    /*  Program goes into an infinite loop if I try to
          write index++ inside the fillInts call. 
        Program writes to array[0] instead of array[index]
          when I write (index + 1) inside the fillInts call.*/
    fill_ints(data, index, size);
  }

}

/*  Recursively iterates through the array, logging the sum of the entries,
        the number of elements found, the minimum, and the maximum.*/
void get_stats(int* array, int index, int size) {
  /* Rejects any attempt to go outside the bounds of the array.*/
  if(index >= size || index < 0) {
    statsHelper[0] = 0;
    statsHelper[1] = 0;
    statsHelper[2] = 0x7fffffff;  /* min = "INTEGER.MAX_VALUE"*/
    statsHelper[3] = 0x80000000;  /* max = "INTEGER.MIN_VALUE"*/
  }

  /* Base case: Last element*/
  if(index == size - 1) {
    statsHelper[0] = array[index];
    statsHelper[1] = 1;
    statsHelper[2] = array[index];
    statsHelper[3] = array[index];
  }

  else {
    get_stats(array, (index + 1), size);

    statsHelper[0] += array[index];
    statsHelper[1]++;
    if(array[index] < statsHelper[2]) {
      statsHelper[2] = array[index];
    }
    if(array[index] > statsHelper[3]) {
      statsHelper[3] = array[index];
    }
  }
}

void print_stats() {
  float average;
  average = (float) statsHelper[0] / statsHelper[1];

  /*  Whitespace between the number of lines entered and the statistics about
        the numbers.*/
  printf("\n");
  printf("The average of the nubmers entered is: %f\n", average);
  printf("The minimum of the numbers entered is: %d\n", statsHelper[2]);
  printf("The maximum of the numbers entered is: %d\n", statsHelper[3]);
}
