#ifndef STATE_H
#define STATE_H

#include <stdio.h>

#define STACK_SIZE 100

typedef struct {
  double val[STACK_SIZE];
  int count;
} stack;

typedef struct {
  int command_count;
  FILE *defbuf;
  FILE *defout;
  char last_op;
  char *prompt;
  stack stack;
  
} state;

#endif
