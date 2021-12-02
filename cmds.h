#ifndef CMDS_H
#define CMDS_H

#include "state.h"
#include <stdlib.h>

extern command CMD_LIST[];
void init_state(state *s);
int exec(char *buf, state *s);

#endif
