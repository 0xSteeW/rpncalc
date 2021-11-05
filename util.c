#include "util.h"
#include <math.h>
#include <string.h>

const char OPERATOR_LIST[] = {
  '+',
  '-',
  '*',
  '/',
  0
};

const command COMMAND_LIST[] = {
  {'c', "clear stack"},
  {'p', "pop last element"},
  {0, 0},
};

int is_operator(char *s) {
  for (int i = 0; OPERATOR_LIST[i] != 0; i++) {
    if (s[0] == OPERATOR_LIST[i]) return 1;
  }
  return 0;
}

TYPE discriminate(char *s) {
  if (is_operator(s)) {
    return OPERATOR;
  } else return FUNCTION;
}
