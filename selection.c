#include<stdio.h>
#include<stdlib.h>

void sort(int*,int);
int find_min(int*,int,int);
void swap(int*,int,int);

int main(int argc, const char *argv[]){
  int *arr;
  size_t arr_len;
  int i;
  char *line;
  FILE *fp;
  size_t len;
  ssize_t read;

  if(argc == 1){ /* no arg => use default array */
    arr_len = 8;
    arr = malloc(sizeof(int)*arr_len);
    for(i=0; i<arr_len; ++i)
      arr[i] = arr_len-i;
  }
  else{          /* read array from file */
    fp = fopen(argv[1], "r");
    line = NULL;
    len = 0;
    if(fp == NULL)
      exit(EXIT_FAILURE);
    arr_len = 0;
    while((read=getline(&line, &len, fp)) != -1)
      ++arr_len;
    fclose(fp);
    arr = malloc(sizeof(int)*arr_len);
    fp = fopen(argv[1], "r");
    line = NULL;
    len = 0;
    i = 0;
    while((read=getline(&line, &len, fp)) != -1)
      sscanf(line, "%d", &arr[i++]);
    fclose(fp);
  }

  printf("\nunsorted:\n");
  for(i=0; i<arr_len; ++i)
    printf("%d\t", arr[i]);
  printf("\n\n");

  sort(arr, arr_len);

  printf("\nsorted:\n");
  for(i=0; i<arr_len; ++i)
    printf("%d\t", arr[i]);
  printf("\n\n");
}

void sort(int *arr, int len){
  int min_idx;
  int i;

  for(i=0; i<len; ++i){
    min_idx = find_min(arr, i, len);
    swap(arr, i, min_idx);
  }
}

int find_min(int *arr, int start, int len){
  int i;
  int min_idx;

  min_idx = start;

  for(i=start; i<len; ++i)
    if(arr[i] < arr[min_idx])
      min_idx = i;

  return min_idx;
}

void swap(int *arr, int i, int j){
  int tmp;

  tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}
