#include <math.h>
#include <stdio.h>
#include "state.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include "cmds.h"
#include <err.h>
#include <errno.h>

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


  fprintf(s.defout,"welcome to rpncalc! type 'list' to see a list of commands, or 'quit' to leave.\n");
  
  
  /* start reading from defbuf */
  char buf[BUF_SIZE];
  while(1){
    fprintf(s.defout, s.prompt, s.command_count, s.last_op);
    s.last_op = 0;
    char *endptr = NULL;
    fgets(buf, BUF_SIZE, s.defbuf);
    buf[strcspn(buf, "\n")] = 0;
    double interpreted = strtod(buf, &endptr);
    if (errno == ERANGE) {
      fprintf(s.defout,"sorry, this number is too big\n");
      continue;
    }
    if (interpreted == (double)0 && endptr == buf) { /* strtod returned the char it could not read */
      TYPE t = discriminate(buf);
      if (t == OPERATOR ) {
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
	/* check for special commands, else pass to exec() */
	if (strcmp(buf, "quit") == 0) {
	  fprintf(s.defout, "quitting, bye!\n");
	  free (s.sorted);
	  exit(0);
	} else if (strcmp(buf, "list") == 0) {
	  for (int i = 0; i < s.numel; i++) {
	    fprintf(s.defout, "[%s]\t->\t%s\n", s.sorted[i].name, s.sorted[i].description);
	    continue;
	  }
	} else exec(buf, &s);
      }
    } else { /* we found a number */
      if (s.stk.count == STACK_SIZE - 1) {
	fprintf(s.defout, "exceeded stack size %d\n", STACK_SIZE);
	continue;
      }
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

