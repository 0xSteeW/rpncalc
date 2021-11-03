#include <stdio.h>
#include "state.h"
#include "util.h"
#include <stdlib.h>
#include <err.h>

#define BUF_SIZE 50

/* rpncalc: a simple reverse polish notation calculator */
int main() {
  
  /* initialize state struct and its values */
  state s;
  /* default input buffer is stdin */
  s.defbuf = stdin;
  /* default output buffer is stdout */
  s.defout = stdout;
  s.last_op = 0;
  /* set default interactive prompt */
  s.prompt = "[%d]> ";
  stack stack = {{0}, 0};
  /* initialize value stack */
  s.stack = stack;
  s.command_count = 0;
  
  /* start reading from defbuf */
  char buf[BUF_SIZE];
  while(1){
    fprintf(s.defout, s.prompt, s.command_count, s.last_op);
    s.last_op = 0;
    if (s.stack.count == STACK_SIZE) err(1, "exceeded stack size");
    fgets(buf, BUF_SIZE, s.defbuf);
    TYPE t = discriminate(buf);
    if (t == OPERATOR ) {
      if (s.stack.count == 1) {
	fprintf(s.defout, "not enough arguments\n");
	continue;
      }
      char operator = buf[0];
      if (operator == '+') {
	s.stack.val[s.stack.count-2] = s.stack.val[s.stack.count-1]+s.stack.val[s.stack.count-2];
	s.stack.val[s.stack.count--] = 0; /* lower count by 1 */
	s.last_op = '+';
      } else if (operator == '-') {
	s.stack.val[s.stack.count-2] = s.stack.val[s.stack.count-2]-s.stack.val[s.stack.count-1];
	s.stack.val[s.stack.count--] = 0; /* lower count by 1 */
	s.last_op = '-';
      } else if (operator == '*') {
	s.stack.val[s.stack.count-2] = s.stack.val[s.stack.count-2]*s.stack.val[s.stack.count-1];
	s.stack.val[s.stack.count--] = 0; /* lower count by 1 */
	s.last_op = '*';
      } else if (operator == '/') {
	s.stack.val[s.stack.count-2] = s.stack.val[s.stack.count-2]/s.stack.val[s.stack.count-1];
	s.stack.val[s.stack.count--] = 0; /* lower count by 1 */
	s.last_op = '/';
      }
    } else {
      s.stack.val[s.stack.count++]=strtod(buf, NULL);
    }
    s.command_count++;
    for (int i = 0; i < s.stack.count; i++) {
      fprintf(s.defout,"%d → %f\n",i, s.stack.val[i]);
    }
  }
}
