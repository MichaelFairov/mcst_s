#include "func_merge.h"

void merge(int32_t *array, int32_t left, int32_t midle, int32_t right) {
  int32_t i, j, k;
  int32_t n1 = midle - left + 1;
  int32_t n2 = right - midle;

  int32_t *L = malloc(n1 * sizeof(int32_t));
  int32_t *R = malloc(n2 * sizeof(int32_t));

  for (i = 0; i < n1; i++)
    L[i] = array[left + i];
  for (j = 0; j < n2; j++)
    R[j] = array[midle + 1 + j];

  i = 0;
  j = 0;
  k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      array[k] = L[i];
      i++;
    } else {
      array[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    array[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    array[k] = R[j];
    j++;
    k++;
  }

  free(L);
  free(R);
}

void merge_sort(int32_t *array, int32_t left, int32_t right) {
  if (left < right) {
    int32_t mid = left + (right - left) / 2; // not overflow
    merge_sort(array, left,
               mid); // recursion start merge_sort
    merge_sort(array, mid + 1, right);
    merge(array, left, mid, right); // mergt array
  }
}

// функция для передачи треду
void *thread_merge_sort(void *arg) {
  tm_array *data = (tm_array *)arg;
  merge_sort(data->array, data->left, data->right); // start sort
  pthread_exit(NULL);
}
// финально сливаем остальные части
void final_merge(int32_t *array, int32_t n, int32_t parts) {
  int32_t part_size = n / parts;
  int32_t *bounds = malloc((parts + 1) * sizeof(int));
  for (int32_t i = 0; i < parts; i++)
    bounds[i] = i * part_size;
  bounds[parts] = n;

  for (int32_t i = 1; i < parts; i++) {
    merge(array, 0, bounds[i] - 1, bounds[i + 1] - 1);
  }

  free(bounds);
}
