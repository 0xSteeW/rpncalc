#include "state.h"
#include "cmds.h"
#include <err.h>
#include <math.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#define LAST stack.val[stack.count-1]
#define PREV stack.val[stack.count-2]
#define REDUCE stack.val[--stack.count] = 0

stack fceil(stack stack) {
  LAST = ceil(LAST);
  return stack;
}

stack ffloor(stack stack) {
  LAST = floor(LAST);
  return stack;
}

stack flogB(stack stack) {
  PREV = log2(PREV)/log2(LAST);
  REDUCE;
  return stack;
}

stack fnegate(stack stack) {
  LAST *= -1;
  return stack;
}

stack fpop(stack stack) {
  REDUCE;
  return stack;
}

stack fsqrt(stack stack) {
  LAST = sqrt(LAST);
  return stack;
}

stack finv(stack stack) {
  LAST = 1/LAST;
  return stack;
}

command CMD_LIST[] = {
  {"p", &fpop, "pop last element", 1},
  {"ceil", &fceil, "truncate to the next integer", 1},
  {"floor", &ffloor, "truncate to the previous integer", 1},
  {"log", &flogB, "calculate logarithm using last element as a base and the previous as the argument", 2},
  {"neg", &fnegate, "change last element's sign", 1},
  {"sqrt", &fsqrt, "calculate the square root", 1},
  {"inv", &finv, "invert last number", 1},
};

int compare(const void *s1, const void *s2) {
  char *left = *(char **)s1;
  char *right = *(char **)s2;
  return strcmp(left, right);
}

int search(const void *s1, const void *s2) {
  char *name = *(char **)s1;
  command c = *(command *)s2;
  return (strcmp(name, c.name));
}

void init_state(state *s) {
  int numel = sizeof(CMD_LIST)/sizeof(CMD_LIST[0]);
  qsort(&CMD_LIST, numel, sizeof(CMD_LIST[0]), compare);
  s->numel = numel;
  s->sorted = CMD_LIST;
}

void exec(char *buf, state *s) {
  command *c = bsearch(&buf, s->sorted, s->numel, sizeof(s->sorted[0]), search);
  if (c == NULL) {
    fprintf(s->defout, "error: function '%s' not found\n", buf);
    return;
  }
  if (c->required_args > s->stk.count) {
    fprintf(s->defout,"this function requires %d arguments\n", c->required_args);
    return;
  }
  fprintf(s->defout, "executing function: %s\n", c->name);
  s->stk = c->exec(s->stk);

}
