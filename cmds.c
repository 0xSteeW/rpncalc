#include "state.h"
#include "cmds.h"
#include <err.h>
#include <math.h>
#include <stdlib.h>
#include <err.h>

stack fceil(stack stack) {
  stack.val[stack.count-1] = ceil(stack.val[stack.count-1]);
  return stack;
}

stack ffloor(stack stack) {
  stack.val[stack.count-1] = floor(stack.val[stack.count-1]);
  return stack;
}

command CMD_LIST[] = {
  {"ceil", &fceil, "truncate to the next integer"},
  {"floor", &ffloor, "truncate to the previous integer"},
  {0, 0, 0}
};

void initstate(state *s) {
  int numel = 0;
  for (int i = 0; CMD_LIST[i].name != 0; i++) numel = i;
  char *sorted = malloc(sizeof(char *)*numel);
  if (sorted == NULL) err(1, "could not allocate function names");
  /* todo: (merge, heap, quick) sort? */
}
