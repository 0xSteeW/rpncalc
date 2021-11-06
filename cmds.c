#include "state.h"
#include "cmds.h"
#include <err.h>
#include <math.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

stack fceil(stack stack) {
  stack.val[stack.count-1] = ceil(stack.val[stack.count-1]);
  return stack;
}

stack ffloor(stack stack) {
  stack.val[stack.count-1] = floor(stack.val[stack.count-1]);
  return stack;
}

stack flogB(stack stack) {
  stack.val[stack.count-2] = log2(stack.val[stack.count-2])/log2(stack.val[stack.count-1]);
  stack.val[--stack.count] = 0;
  return stack;
}

stack fnegate(stack stack) {
  stack.val[stack.count-1] *= -1;
  return stack;
}

stack fpop(stack stack) {
  stack.val[--stack.count] = 0;
  return stack;
}

command CMD_LIST[] = {
  {"p", &fpop, "pop last element"},
  {"ceil", &fceil, "truncate to the next integer"},
  {"floor", &ffloor, "truncate to the previous integer"},
  {"log", &flogB, "calculate logarithm in base LAST_NUM of LAST_NUM-1"},
  {"neg", &fnegate, "change last element's sign"},
  {0, 0, 0}
};

void init_state(state *s) {
  int numel = 0;
  for (int i = 0; CMD_LIST[i].name != 0; i++) numel = i;
  command *sorted = malloc(sizeof(command *)*numel);
  if (sorted == NULL) err(1, "could not allocate function names");
  /* todo: (merge, heap, quick) sort? */
  for (int i = 0; CMD_LIST[i].name != 0; i++) {
    sorted[i] = CMD_LIST[i];
  }
  s->sorted = sorted;
}

void exec(char *buf, state *s) {
  /* change this to a binary tree search */
  for (int i = 0; s->sorted[i].name != 0; i++) {
    if (strcmp(buf, s->sorted[i].name) == 0) {
      fprintf(s->defout, "executing function: %s\n", s->sorted[i].name);
      s->stk = s->sorted[i].exec(s->stk);
      return;
    }
  }
  fprintf(s->defout, "error: function '%s' not found\n", buf);
}
