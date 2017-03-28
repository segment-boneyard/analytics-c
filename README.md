# analytics-c (WIP)

A C client for Segment — The hassle-free way to integrate analytics into any application.

## Example

```c
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
```

## Developing

```
$ goto analytics-c
$ make test
$ ./test
```

### Running Valgrind

Because Valgrind is buggy on OSX, we'll run it in a [Docker container](https://github.com/thlorenz/docker-valgrind):

```
$ docker build -t="analytics-c" .
$ docker run -i analytics-c clean valgrind
```

## License

MIT
