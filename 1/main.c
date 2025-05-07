#include "func_merge.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  // enter data(array, size, thread_count)
  int32_t size;
  printf("Enter array size:\n");
  scanf("%d", &size);
  int32_t *array = (int32_t *)malloc(sizeof(int32_t) * size);
  int32_t thread_count;
  printf("Enter threads count:\n");
  scanf("%d", &thread_count);
  printf("Enter array:\n");
  for (int32_t i = 0; i < size; i++)
    scanf("%d", array + i);
  // create array is thread and tm_array for sort
  pthread_t threads[thread_count];
  tm_array thread_data[thread_count];

  int32_t part_size = size / thread_count;
  for (int32_t i = 0; i < thread_count; i++) {
    thread_data[i].array = array;
    thread_data[i].left = i * part_size;
    thread_data[i].right = (i + 1) * part_size - 1;

    if (i == thread_count - 1) {
      thread_data[i].right = size - 1;
    }
    // create threads
    pthread_create(&threads[i], NULL, thread_merge_sort, &thread_data[i]);
  }

  for (int32_t i = 0; i < thread_count; i++) {
    // wait result of thread
    pthread_join(threads[i], NULL);
  }
  final_merge(array, size, thread_count);

  printf("array:\n");
  for (int32_t i = 0; i < size; i++)
    printf("%d ", array[i]);
  printf("\n");
  free(array);
  return 0;
}
