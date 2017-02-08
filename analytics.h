
//
// analytics.h
//
// Copyright (c) 2017 Segment
//

#ifndef ANALYTICS_H
#define ANALYTICS_H 1

/**
 * Return codes.
 */

typedef enum {
  ANALYTICS_SUCCESS = 0,
  ANALYTICS_MEMORY_ERROR = -1
} analytics_rc;

/**
 * Analytics API method types.
 */

typedef enum {
  ANALYTICS_METHOD_IDENTIFY,
  ANALYTICS_METHOD_TRACK,
  ANALYTICS_METHOD_PAGE,
  ANALYTICS_METHOD_SCREEN,
  ANALYTICS_METHOD_GROUP,
  ANALYTICS_METHOD_ALIAS
} analytics_method_t;

/**
 * Analytics hashmap.
 */

typedef struct {
  // this is for stuff like:
  //   - properties
  //   - traits
  //   - context
  int foo;
} analytics_hashmap_t;

/**
 * Event structure.
 */

typedef struct {
  analytics_method_t method;

  const char *event;
  const char *name;

  const char *group_id;
  const char *user_id;
  const char *anonymous_id;
  const char *previous_id;

  analytics_hashmap_t *traits;
  analytics_hashmap_t *properties;
} analytics_event_t;

/**
 * Create a new event.
 */

analytics_event_t *
analytics_event_new(analytics_method_t type);

/**
 * Free memory associated with an event.
 */

void
analytics_event_free(analytics_event_t *event);

/**
 * Analytics.
 */

typedef struct {
  const char *write_key;
  const char *host;
} analytics_t;

// prototypes

analytics_t *
analytics_init(const char *write_key);

void
analytics_free(analytics_t *self);

int
analytics_track(analytics_t *self, const char *event_name, const char *user_id, analytics_hashmap_t *properties);

int
analytics_identify(analytics_t *self, const char *user_id, analytics_hashmap_t *traits);

int
analytics_page(analytics_t *self, const char *event_name, const char *user_id, analytics_hashmap_t *properties);

int
analytics_screen(analytics_t *self, const char *event_name, const char *user_id, analytics_hashmap_t *properties);

int
analytics_alias(analytics_t *self, const char *previous_id, const char *user_id);

int
analytics_group(analytics_t *self, const char *group_id, analytics_hashmap_t *traits);

#endif // ANALYTICS_H
