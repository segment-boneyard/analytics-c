
#include <stdio.h>
#include "analytics.h"

int
main(int argc, char **argv){
  analytics_t analytics;
  analytics_init(&analytics, "91uhdbiyvft712");
  analytics_track(&analytics, /* msg */);
  analytics_identify(&analytics, /* msg */);
  analytics_page(&analytics, /* msg */);
  analytics_alias(&analytics, /* msg */);
  analytics_group(&analytics, /* msg */);
  analytics_free(&analytics);
  return 0;
}
