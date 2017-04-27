
//
// analytics.c
//
// Copyright (c) 2017 Segment
//

#include <stdlib.h>
#include <assert.h>
#include "list/list.h"
#include "asprintf/asprintf.h"
#include "analytics.h"

static void __analytics_event_free(void *_);

/**
 * Initialize with `write_key`.
 */

analytics_t *
analytics_init(const char *write_key) {
  assert(write_key);

  analytics_t *self;
  if (!(self = malloc(sizeof(analytics_t)))) {
    return NULL;
  }

  self->queue = list_new();
  if (!self->queue) {
    analytics_free(self);
    return NULL;
  }
  self->queue->free = __analytics_event_free;

  self->write_key = write_key;
  self->host = "https://api.segment.com";

  return self;
}

/**
 * Free up analytics after use.
 */

void
analytics_free(analytics_t *self) {
  if (self->queue) {
    list_destroy(self->queue);
  }
  free(self);
  self = NULL;
}

/**
 * Create a new analytics event.
 */

analytics_event_t *
analytics_event_new (analytics_method_t type) {
  analytics_event_t *event;

  if (!(event = malloc(sizeof(analytics_event_t)))) {
    return NULL;
  }

  event->method = type;

  event->event = NULL;
  event->name = NULL;

  event->group_id = NULL;
  event->user_id = NULL;
  event->anonymous_id = NULL;
  event->previous_id = NULL;

  event->traits = NULL;
  event->properties = NULL;

  return event;
}

void
analytics_event_free(analytics_event_t *event) {
  free(event);
  event = NULL;
}

// it's gross, i know
static void
__analytics_event_free(void *_) {
  analytics_event_t *event = (analytics_event_t *) _;
  analytics_event_free(event);
}

static int
analytics_enqueue (analytics_t *self, analytics_event_t *event) {
  list_node_t *event_node = list_node_new(event);
  if (list_rpush(self->queue, event_node) == NULL) {
    return ANALYTICS_QUEUE_ERROR;
  }
  return ANALYTICS_SUCCESS;
}

/**
 * Track.
 */

int
analytics_track(analytics_t *self, const char *event_name, const char *user_id, analytics_hashmap_t *properties) {
  analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_TRACK);

  if (!event) {
    return ANALYTICS_MEMORY_ERROR;
  }

  event->event = event_name;
  event->user_id = user_id;
  event->properties = properties;

  return analytics_enqueue(self, event);
}

/**
 * Identify.
 */

int
analytics_identify(analytics_t *self, const char *user_id, analytics_hashmap_t *traits) {
  analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_IDENTIFY);

  if (!event) {
    return ANALYTICS_MEMORY_ERROR;
  }

  event->user_id = user_id;
  event->traits = traits;

  return analytics_enqueue(self, event);
}

/**
 * Page.
 */

int
analytics_page(analytics_t *self, const char *event_name, const char *user_id, analytics_hashmap_t *properties) {
  analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_PAGE);

  if (!event) {
    return ANALYTICS_MEMORY_ERROR;
  }

  event->user_id = user_id;
  event->name = event_name;
  event->properties = properties;

  return analytics_enqueue(self, event);
}

/**
 * Screen.
 */

int
analytics_screen(analytics_t *self, const char *event_name, const char *user_id, analytics_hashmap_t *properties) {
  analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_SCREEN);

  if (!event) {
    return ANALYTICS_MEMORY_ERROR;
  }

  event->user_id = user_id;
  event->name = event_name;
  event->properties = properties;

  return analytics_enqueue(self, event);
}

/**
 * Alias.
 */

int
analytics_alias(analytics_t *self, const char *previous_id, const char *user_id) {
  analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_ALIAS);

  if (!event) {
    return ANALYTICS_MEMORY_ERROR;
  }

  event->previous_id = previous_id;
  event->user_id = user_id;

  return analytics_enqueue(self, event);
}

/**
 * Group.
 */

int
analytics_group(analytics_t *self, const char *group_id, analytics_hashmap_t *traits) {
  analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_GROUP);

  if (!event) {
    return ANALYTICS_MEMORY_ERROR;
  }

  event->group_id = group_id;
  event->traits = traits;

  return analytics_enqueue(self, event);
}

/**
 * Set `key` to `value`.
 */

void
analytics_hashmap_set(analytics_hashmap_t *self, const char *key, const char *value) {
  int p;
  khiter_t k = kh_put(ptr, self, key, &p);
  kh_value(self, k) = (void *) value;
}

/**
 * Get the value of `key`.
 */

const char *
analytics_hashmap_get(analytics_hashmap_t *self, const char *key) {
  khiter_t k = kh_get(ptr, self, key);
  return kh_end(self) == k
    ? NULL
    : (char *) kh_value(self, k);
}

/**
 * Serialize the map to a string.
 *
 * Free the value when done.
 */

const char *
analytics_hashmap_serialize(analytics_hashmap_t *self) {
  char *result = malloc(1);
  int length = 0;
  result[0] = 0;

  if (result == NULL) {
    return NULL;
  }

  for (khiter_t k = kh_begin(self); k < kh_end(self); ++k) {
    if (!kh_exist(self, k)) {
      continue;
    }

    const char *key = kh_key(self, k);
    const char *value = (char *) kh_value(self, k);

    const char *fmt = length == 0
      ? "{\n  \"%s\": \"%s\""
      : ",\n  \"%s\": \"%s\"";
    char *tmp = NULL;
    int adding = asprintf(&tmp, fmt, key, value);
    if (adding == -1) {
      free(result);
      return NULL;
    }

    result = realloc(result, length + adding + 1);
    if (result == NULL) {
      return NULL;
    }

    char *pos = result + length;

    memset(pos, '\0', adding + 1); /* valgrind yells */
    memcpy(pos, tmp, adding);
    free(tmp);
    length += adding;
  }
  length += 3;
  result = realloc(result, length);
  strncat(result, "\n}\0", 3);

  return result;
}
