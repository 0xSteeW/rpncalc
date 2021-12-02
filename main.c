#include "cmds.h"
#include "state.h"
#include "util.h"
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  fprintf(s.defout, "welcome to rpncalc! type 'list' to see a list of "
	  "commands, or 'quit' to leave.\n");

  /* start reading from defbuf */
  char buf[BUF_SIZE];
  while (1) {
    int execval = 0;
    /* prompt the user for input */
    fprintf(s.defout, s.prompt, s.command_count, s.last_op);
    s.last_op = 0;
    char *endptr = NULL;
    /* get input */
    char *check = fgets(buf, BUF_SIZE, s.defbuf);
    if (check == NULL)
      exit(0);
    /* strip newline */
    buf[strcspn(buf, "\n")] = 0;
    /* parse input as a number */
    double interpreted = strtod(buf, &endptr);
    if (errno == ERANGE) {
      fprintf(s.defout, "sorry, this number is too big\n");
      continue;
    }
    /* special functions, quit and list, that do not interact with the stack directly */
    if (strcmp(buf, "quit") == 0) {
      fprintf(s.defout, "quitting, bye!\n");
      exit(0);
    } else if (strcmp(buf, "list") == 0) {
      for (int i = 0; i < s.numel; i++) {
        fprintf(s.defout, "[%s]\t->\t%s\n", s.sorted[i].name,
                s.sorted[i].description);
      }
      continue;
    } else if ((execval = exec(buf, &s)) == -1 || execval > 0) { /* try to execute a known function.
								    if we fail, we either catch an
								    incorrect number of arguments
								    error, or we pass it to the next
								    else clause.*/
      if (execval > 0) {
	fprintf(s.defout, "this function requires %d arguments\n", execval);
	continue;
      }
    } else { /* we found a number */
      /* test if provided input could not be parsed by strtod, in this case we are not against
	 a number, so error out */
      if (endptr == buf) {
	fprintf(s.defout, "function %s not found\n", buf);
	continue;
      }
      if (s.stk.count == STACK_SIZE - 1) {
        fprintf(s.defout, "exceeded stack size %d\n", STACK_SIZE);
        continue;
      }
      s.stk.val[s.stk.count++] = interpreted;
    }
    /* add one to the command count, and print the updated stack */
    s.command_count++;
    for (int i = 0; i < s.stk.count; i++) {
      fprintf(s.defout, "%d → %f\n", i, s.stk.val[i]);
    }
  }
}

