#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>

#include "storm.h"

void print_execute(const struct tuple *t, struct executor *self)
{
  printf("Printer got: ");

  for(int i = 0; i < MAX_VECTOR; i++) {
    printf("['%s', %d], ", t->v[i].str, t->v[i].integer);
  }

  printf("\n");
}
