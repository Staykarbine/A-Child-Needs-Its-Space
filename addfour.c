#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_ARR_LENGTH 10000

int main(int argc, char*argv[])
{
  if (argc < 2)
  {
    printf("Please! Pass the path to input file as the cmdline argument.\n");
    exit(-1);
  }

  // File Handling
  FILE *input_file;

  // Computing time for algorithm
  clock_t p_start_time, p_end_time;
  double p_total_time;

  //Child Process
  int p_id;

  
  input_file = fopen(argv[1], "r");
  if (input_file == NULL)
  {
    perror("Error Opening File!\n Please Provide an input file\n");
    exit(-1);
  }
  fclose(input_file);
  p_id = fork();

  if (p_id == 0)
  {
    printf("Child Process: START\n");
    int file_data[MAX_ARR_LENGTH];
    int counter;
    int file_data_len;
    int sum;
    clock_t c_start_time, c_end_time;
    double c_total_time;
    
    c_start_time = clock();
    input_file = fopen(argv[1], "r");
    counter = 0;
    while (!feof(input_file)&& counter < MAX_ARR_LENGTH) 
    {
      fscanf(input_file,"%d,", &file_data[counter]);
      //printf("%d ",file_data[counter]);
      counter++;
    }
    printf("Executing Four Sum Algorithm for file size %d\n",counter);
    file_data_len = counter;
    for (size_t i = 0; i < file_data_len && i < MAX_ARR_LENGTH; i++)
    {
      for (size_t j = i+1; j < file_data_len && j < MAX_ARR_LENGTH; j++)
      {
        for (size_t k = j+1; k < file_data_len && k < MAX_ARR_LENGTH; k++)
        {
          for (size_t l = k+1; l < file_data_len && l < MAX_ARR_LENGTH; l++)
          {
            sum = file_data[i]+file_data[j]+file_data[k]+file_data[l];
          }
        }
      }
    }
    

    c_end_time = clock();
    c_total_time = (double)(c_end_time - c_start_time)/CLOCKS_PER_SEC;
    printf("Child Process: END\n");
    printf("Total time taken by Child: %lf\n", c_total_time);
  }
  else
  {
    printf("Parent Process: START\n");
    p_start_time = clock();
    wait(NULL);
    p_end_time = clock();
    p_total_time = (double)(p_end_time - p_start_time)/CLOCKS_PER_SEC;
    printf("Parent Process: END\n");
    printf("Total time taken by Parent: %lf\n", p_total_time);
  }
  
  
  
  return 0;
}