#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void sort(int*,int);
int find_max(int*,int);

int main(int argc, const char *argv[]){
  int *arr;
  size_t arr_len;
  int i;
  char *line;
  FILE *fp;
  size_t len;
  ssize_t read;

  if(argc == 1){ /* no arg => use default array */
    arr_len = 16;
    arr = malloc(sizeof(int)*arr_len);
    srand(time(NULL));
    for(i=0; i<arr_len; ++i)
      arr[i] = rand() % 32;
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
  int max_val;
  int *count_arr;
  int i;
  int j;

  max_val = find_max(arr, len);
  count_arr = malloc(sizeof(int)*max_val);

  for(i=0; i<max_val; ++i)
    count_arr[i] = 0;

  for(i=0; i<len; ++i)
    count_arr[arr[i]] += 1;

  i=0;
  j=0;
  while(i<len){
    while(count_arr[j] != 0){
      arr[i++] = j;
      --count_arr[j];
    }
    ++j;
  }
}

int find_max(int *arr, int len){
  int i;
  int max;

  max = arr[0];

  for(i=1; i<len; ++i)
    if(arr[i] > max)
      max = arr[i];
  return max;
}
