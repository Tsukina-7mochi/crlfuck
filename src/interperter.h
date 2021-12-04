#ifndef __CRLFUCK_INTERPRETER_H__
#define __CRLFUCK_INTERPRETER_H__

#include <stddef.h>

extern void execute(const char* program, size_t program_length, size_t data_array_length);

#endif // __CRLFUCK_INTERPRETER_H__