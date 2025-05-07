#pragma once
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct {
  int32_t *array;
  int32_t left;
  int32_t right;
} tm_array;

void merge(int32_t *array, int32_t left, int32_t midle, int32_t right);
void final_merge(int32_t *array, int32_t n, int32_t thread_count);
void merge_sort(int32_t *array, int32_t left, int32_t right);
void *thread_merge_sort(void *arg);
void final_merge(int32_t *array, int32_t n, int32_t parts);
