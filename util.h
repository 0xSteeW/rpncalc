#ifndef UTIL_H
#define UTIL_H

typedef enum {OPERATOR, COMMAND ,DOUBLE, FUNCTION} TYPE;
TYPE discriminate(char *s);
typedef struct {
  char n;
  const char* desc;
} command;
  
#endif
