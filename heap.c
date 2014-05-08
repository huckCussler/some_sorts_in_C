#include<stdio.h>
#include<stdlib.h>

void heapify(int*,int,int);
void build_heap(int*,int);
int get_max(int*,int,int);
void swap(int*,int,int);
void sort(int*,int);
int heap_pop(int*,int);

int main(int argc, const char *argv[]){
  int *in_arr;
  int arr_len;
  int i;
  char *line;
  FILE *fp;
  size_t len;
  ssize_t read;
  int two_pow;

  if(argc == 1){ /* no args, use default array */
    arr_len = 7;
    in_arr = malloc(sizeof(int)*arr_len);
    for(i=0; i<arr_len; i++)
      in_arr[i] = i+1;
  }
  else {         /* read the array to be sorted from the file */
    fp = fopen(argv[1], "r");
    line = NULL;
    len = 0;
    if(fp == NULL)
      exit(EXIT_FAILURE);
    arr_len = 0;
    while((read=getline(&line, &len, fp)) != -1)
      ++arr_len;
    fclose(fp);
    in_arr = malloc(sizeof(int)*arr_len);
    fp = fopen(argv[1], "r");
    line = NULL;
    len = 0;
    i = 0;
    while((read=getline(&line, &len, fp)) != -1)
      sscanf(line, "%d", &in_arr[i++]);
    fclose(fp);
  }

  build_heap(in_arr, arr_len);

  two_pow = 1;
  printf("\nheap:\n");
  for(i=0; i<arr_len; ++i){
    if(i == two_pow){
      printf("\n");
      two_pow = 2*two_pow + 1;
    }
    printf("%d\t", in_arr[i]);
  }
  printf("\n\n");
  
  sort(in_arr, arr_len);

  printf("sorted array:\n");
  for(i=0; i<arr_len; ++i)
    printf("%d\t", in_arr[i]);
  printf("\n\n");
}

int heap_pop(int *arr, int len){
  swap(arr, 0, --len);
  build_heap(arr, len);
}

void sort(int *arr, int len){
  while(len > 0)
    heap_pop(arr, len--);
}

void heapify(int *arr, int len, int idx){
  int max_child_idx;

  if(idx*2+1 < len){ /* node has left child */
    if(idx*2+2 < len){ /* node has right child */
      max_child_idx = get_max(arr, idx*2+1, idx*2+2);
      if(arr[max_child_idx] > arr[idx]){
	swap(arr, max_child_idx, idx);
	heapify(arr, len, max_child_idx);
      }
    }
    else if(arr[idx*2+1] > arr[idx])
      swap(arr, idx*2+1, idx);
  }
}

void build_heap(int *arr, int len){
  int i;

  for(i=len/2; i>=0; --i)
    heapify(arr, len, i);
}

int get_max(int *arr, int i, int j){
  return arr[i]>arr[j] ? i : j;
}

void swap(int *arr, int i, int j){
  int tmp;

  tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}
