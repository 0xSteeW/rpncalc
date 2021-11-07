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
#define NEW stack.val[stack.count++]

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

stack fpi(stack stack) {
  NEW = M_PI;
  return stack;
}

stack fe(stack stack) {
  NEW = M_E;
  return stack;
}

stack fsin(stack stack) {
  LAST = sin(LAST);
  return stack;
}

stack fcos(stack stack) {
  LAST = cos(LAST);
  return stack;
}

command CMD_LIST[] = {
  {"ceil", &fceil, "truncate to the next integer", 1},
  {"cos", &fcos, "calculate the cosine", 1},
  {"e", &fe, "return number e", 0},
  {"floor", &ffloor, "truncate to the previous integer", 1},
  {"inv", &finv, "invert last number", 1},
  {"log", &flogB, "calculate logarithm using last element as a base and the previous as the argument", 2},
  {"neg", &fnegate, "change last element's sign", 1},
  {"p", &fpop, "pop last element", 1},
  {"pi", &fpi, "return number pi", 0},
  {"sin", &fsin, "calculate the sine", 1},
  {"sqrt", &fsqrt, "calculate the square root", 1},
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
