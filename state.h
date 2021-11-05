#ifndef STATE_H
#define STATE_H

#include <stdio.h>

#define STACK_SIZE 100

typedef struct {
  double val[STACK_SIZE];
  int count;
} stack;

typedef struct {
  char *name;
  stack (*exec)(stack);
  char *description;
} command;

typedef struct {
  int command_count;
  FILE *defbuf;
  FILE *defout;
  char last_op;
  char *prompt;
  stack stack;

  /* btree elements */
  
  char **sorted_names; /* sorted function names */
  stack *((*exec)(stack)); /* sorted function calls, same order as above */
} state;

#endif
