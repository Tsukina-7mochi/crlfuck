#ifndef __CRLFUCK_INTERPRETER_C__
#define __CRLFUCK_INTERPRETER_C__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void execute(const char* program, size_t program_length, size_t data_array_length) {
  uint8_t* data_array = (uint8_t*) calloc(data_array_length, sizeof(uint8_t));
  uint8_t* the_pointer = data_array;
  size_t program_counter = 0;

  memset(data_array, 0, data_array_length * sizeof(uint8_t));

  while(program_counter < program_length) {
    uint8_t instraction = ((program[program_counter] & 1) << 2) + ((program[program_counter + 1] & 1) << 1) + ((program[program_counter + 2] & 1));

    if(instraction == 0b111) {
      // CR CR CR := '>'
      the_pointer += 1;
    } else if(instraction == 0b110) {
      // CR CR LF := '<'
      the_pointer -= 1;
    } else if(instraction == 0b101) {
      // CR LF CR := '+'
      (*the_pointer) += 1;
    } else if(instraction == 0b100) {
      // CR LF LF := '-'
      (*the_pointer) -= 1;
    } else if(instraction == 0b011) {
      // LF CR CR := '.'
      putchar(*the_pointer);
    } else if(instraction == 0b010) {
      // LF CR LF := ','
      (*the_pointer) = getchar();
    } else if(instraction == 0b001) {
      // LF LF CR := '['
      if((*the_pointer) == 0) {
        size_t block_depth = 1;
        uint8_t instraction_ = 0;

        while(block_depth > 0) {
          program_counter += 3;

          instraction_ = ((program[program_counter] & 1) << 2) + ((program[program_counter + 1] & 1) << 1) + ((program[program_counter + 2] & 1));
          if(instraction_ == 0b001) {
            block_depth += 1;
          } else if(instraction_ == 0b000) {
            block_depth -= 1;
          }
        }
      }
    } else if(instraction == 0b000) {
      // LF LF LF := ']'
      if((*the_pointer) != 0) {
        size_t block_depth = 1;
        uint8_t instraction_ = 0;

        while(block_depth > 0) {
          program_counter -= 3;

          instraction_ = ((program[program_counter] & 1) << 2) + ((program[program_counter + 1] & 1) << 1) + ((program[program_counter + 2] & 1));
          if(instraction_ == 0b001) {
            block_depth -= 1;
          } else if(instraction_ == 0b000) {
            block_depth += 1;
          }
        }
      }
    }

    program_counter += 3;
  }

  free(data_array);
}

#endif // __CRLFUCK_INTERPRETER_C__