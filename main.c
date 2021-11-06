#include <math.h>
#include <stdio.h>
#include "state.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include "cmds.h"
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
  s.stk = stack;
  s.command_count = 0;
  init_state(&s);
  
  /* start reading from defbuf */
  char buf[BUF_SIZE];
  while(1){
    fprintf(s.defout, s.prompt, s.command_count, s.last_op);
    s.last_op = 0;
    char *endptr = NULL;
    if (s.stk.count == STACK_SIZE) err(1, "exceeded stk size");
    fgets(buf, BUF_SIZE, s.defbuf);
    buf[strcspn(buf, "\n")] = 0;
    double interpreted = strtod(buf, &endptr);
    if (interpreted == (double)0 && endptr == buf) { /* strtod returned the char it could not read */
      TYPE t = discriminate(buf);
      if (t == OPERATOR ) {
	printf("func\n");
	if (s.stk.count <= 1) {
	  fprintf(s.defout, "not enough arguments\n");
	  continue;
	}
	char operator = buf[0];
	if (operator == '+') {
	  s.stk.val[s.stk.count-2] = s.stk.val[s.stk.count-1]+s.stk.val[s.stk.count-2];
	  s.stk.val[s.stk.count--] = 0; /* lower count by 1 */
	  s.last_op = '+';
	} else if (operator == '-') {
	  s.stk.val[s.stk.count-2] = s.stk.val[s.stk.count-2]-s.stk.val[s.stk.count-1];
	  s.stk.val[s.stk.count--] = 0; /* lower count by 1 */
	  s.last_op = '-';
	} else if (operator == '*') {
	  s.stk.val[s.stk.count-2] = s.stk.val[s.stk.count-2]*s.stk.val[s.stk.count-1];
	  s.stk.val[s.stk.count--] = 0; /* lower count by 1 */
	  s.last_op = '*';
	} else if (operator == '/') {
	  s.stk.val[s.stk.count-2] = s.stk.val[s.stk.count-2]/s.stk.val[s.stk.count-1];
	  s.stk.val[s.stk.count--] = 0; /* lower count by 1 */
	  s.last_op = '/';
	} else;
      } else if (t == FUNCTION) {
	if (strcmp(buf, "quit") == 0) {
	  fprintf(s.defout, "quitting, bye!\n");
	  exit(0);
	} else exec(buf, &s);
      }
    } else { /* we found a number */
      printf("number\n");
      s.stk.val[s.stk.count++] = interpreted;
    }
    
    s.command_count++;
    for (int i = 0; i < s.stk.count; i++) {
      fprintf(s.defout,"%d → %f\n",i, s.stk.val[i]);
    }
  }
  /* free stuff */
  free (s.sorted);
}

