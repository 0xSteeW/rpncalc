#include "state.h"

void push(state *s, double d) {
  s->stack.val[s->stack.count+1] = d;
  s->stack.count += 1;
}
