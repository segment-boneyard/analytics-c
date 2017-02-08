
//
// analytics.c
//
// Copyright (c) 2017 Segment
//

#include "analytics.h"
#include "request.h"
#include <stdio.h>
#include <assert.h>

/*
 * Initialize with `writeKey`.
 */

void
analytics_init(analytics_t *self, const char *writeKey, const char *host) {
  assert(writeKey)
  self->writeKey = writeKey;
  self->host = host || "https://api.segment.com";
}

/*
 * Free up analytics after use.
 */

void
analytics_free(analytics_t *self) {
  free(self->writeKey);
  free(self->host);
}

/**
 * Track.
 */

void
analytics_track(analytics_t *self, /* message */, analytics_callback_t cb) {
  // request(/* message */, "track")
}

/**
 * Identify.
 */

void
analytics_identify(analytics_t *self, /* message */, analytics_callback_t cb) {
  // request(/* message */, "identify")
}

/**
 * Page.
 */

void
analytics_page(analytics_t *self, /* message */, analytics_callback_t cb) {
  // request(/* message */, "page")
}

/**
 * Alias.
 */

void
analytics_alias(analytics_t *self, /* message */, analytics_callback_t cb) {
  // request(/* message */, "alias")
}

/**
 * Group.
 */

void
analytics_group(analytics_t *self, /* message */, analytics_callback_t cb) {
  // request(/* message */, "group")
}
