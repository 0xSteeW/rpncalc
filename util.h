#ifndef UTIL_H
#define UTIL_H

typedef enum {OPERATOR, COMMAND ,DOUBLE, FUNCTION} TYPE;
TYPE discriminate(char *s);
#endif
