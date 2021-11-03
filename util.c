#include "util.h"
#include <math.h>

char OPERATOR_LIST[] = {
  '+',
  '-',
  '*',
  '/',
  0
};

int is_decimal(char *s) {
  for (int i = 0; s[i] != 0; i++) {
    if (s[i] == ',' || s[i] == '.') return 1;
  }
  return 0;
}

int is_operator(char *s) {
  for (int i = 0; OPERATOR_LIST[i] != 0; i++) {
    if (s[0] == OPERATOR_LIST[i]) return 1;
  }
  return 0;
}

TYPE discriminate(char *s) {
  if (is_operator(s)) {
    return OPERATOR;
  } else return DOUBLE;
}
