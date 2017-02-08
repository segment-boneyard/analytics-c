
//
// analytics.h
//
// Copyright (c) 2017 Segment
//

#ifndef ANALYTICS_H
#define ANALYTICS_H

/**
 * Analytics struct.
 */

struct analytics;

/*
 * Callback.
 */

typedef void (* analytics_callback_t)(struct analytics *self);

/**
 * Analytics.
 */

typedef struct analytics {
  const char *writeKey;
  const char *host;
} analytics_t;

// prototypes

void
analytics_init(analytics_t *self, const char *writeKey, const char *host);

void
analytics_free(analytics_t *self);

void
analytics_track(analytics_t *self, /* message */, analytics_callback_t cb);

void
analytics_identify(analytics_t *self, /* message */, analytics_callback_t cb);

void
analytics_page(analytics_t *self, /* message */, analytics_callback_t cb);

void
analytics_alias(analytics_t *self, /* message */, analytics_callback_t cb);

void
analytics_group(analytics_t *self, /* message */, analytics_callback_t cb);

#endif // ANALYTICS_H
