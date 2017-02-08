
#include <stdlib.h>
#include <assert.h>
#include "analytics.h"

int
main(void){
  analytics_t *analytics = analytics_init("91uhdbiyvft712");
  assert(analytics);

  int rc = analytics_track(analytics, "Did Something", "abc123", NULL);
  assert(rc == ANALYTICS_SUCCESS);

  analytics_free(analytics);
  return 0;
}
