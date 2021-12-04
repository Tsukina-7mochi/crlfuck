#include <stdio.h>
#include <stdlib.h>
#include "./interperter.h"

#define DATA_ARRAY_LENGTH 30000

int main(int argc, char* argv[]) {
  FILE* input_fp = NULL;
  size_t program_length = 0;
  char* program = NULL;

  if(argc < 2) {
    printf("no input file.\n");

    return 0;
  }

  input_fp = fopen(argv[1], "rb");
  if(input_fp == NULL) {
    printf("\"%s\" cannot be opened.'n", argv[1]);

    return 0;
  }


  fseek(input_fp, 0, SEEK_END);
  program_length = ftell(input_fp);
  fseek(input_fp, 0, SEEK_SET);

  program = (char*) calloc(program_length, sizeof(char));
  fread(program, sizeof(char), program_length, input_fp);

  fclose(input_fp);


  execute(program, program_length, DATA_ARRAY_LENGTH);

  return 0;
}