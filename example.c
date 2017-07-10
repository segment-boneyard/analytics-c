#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "analytics.h"

int
main(void){
  analytics_t *analytics = analytics_init("91uhdbiyvft712");
  assert(analytics);

  analytics_hashmap_t *properties = analytics_hashmap_new();
  assert(properties);

  analytics_hashmap_set(properties, "foo", "bar");
  analytics_hashmap_set(properties, "baz", "qux");
  analytics_hashmap_set(properties, "dog", "true");
  analytics_hashmap_set(properties, "cat", "false");

  const char *s = analytics_hashmap_serialize(properties);
  printf("%s\n", s);
  free((char *) s);

  int rc = analytics_track(analytics, "Did Something", "abc123", properties);
  assert(rc == ANALYTICS_SUCCESS);

  analytics_hashmap_free(properties);

  analytics_free(analytics);
  return 0;
}
