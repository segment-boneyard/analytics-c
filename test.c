
#include <stdio.h>
#include "analytics.h"

int
main(int argc, char **argv){
  analytics_t *analytics = analytics_init("91uhdbiyvft712");
  analytics_free(analytics);
  return 0;
}
