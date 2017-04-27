#include <stdlib.h>
#include "describe/describe.h"
#include "analytics.h"

int main () {
  describe("analytics_init") {
    it("should initialize") {
      analytics_t *analytics = analytics_init("XXX");
      assert_not_null(analytics);
      analytics_free(analytics);
    }

    it("should set the write key") {
      analytics_t *analytics = analytics_init("XXX");
      assert_str_equal(analytics->write_key, "XXX");
      analytics_free(analytics);
    }

    it("should create a queue") {
      analytics_t *analytics = analytics_init("XXX");
      assert_not_null(analytics->queue);
      analytics_free(analytics);
    }

    it("should set the default host") {
      analytics_t *analytics = analytics_init("XXX");
      assert_str_equal(analytics->host, "https://api.segment.com");
      analytics_free(analytics);
    }
  }

  describe("analytics_free") {
    // TODO: better test
    it("should work") {
      analytics_t *analytics = analytics_init("XXX");
      analytics_free(analytics);
    }
  }

  describe("analytics_event_new") {
    it("should initialize") {
      analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_TRACK);
      assert_not_null(event);
      analytics_event_free(event);
    }

    it("should set type") {}

    it("should set defaults") {}
  }

  describe("analytics_event_free") {
    // TODO: better test
    it("should work") {
      analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_TRACK);
      analytics_event_free(event);
    }
  }

  describe("analytics_track") {
    it("should enqueue a track event") {
      analytics_t *analytics = analytics_init("XXX");

      int rc = analytics_track(analytics, "Did Something", "abc123", NULL);
      assert_equal(rc, ANALYTICS_SUCCESS);

      analytics_event_t *event = (analytics_event_t *) list_at(analytics->queue, 0);
      assert_not_null(event);

      analytics_free(analytics);
    }
  }

  describe("analytics_identify") {
    it("should enqueue an identify event") {
      analytics_t *analytics = analytics_init("XXX");

      int rc = analytics_identify(analytics, "abc123", NULL);
      assert_equal(rc, ANALYTICS_SUCCESS);

      analytics_event_t *event = (analytics_event_t *) list_at(analytics->queue, 0);
      assert_not_null(event);

      analytics_free(analytics);
    }
  }

  describe("analytics_page") {
    it("should enqueue a page event") {
      analytics_t *analytics = analytics_init("XXX");

      int rc = analytics_page(analytics, "Did Something", "abc123", NULL);
      assert_equal(rc, ANALYTICS_SUCCESS);

      analytics_event_t *event = (analytics_event_t *) list_at(analytics->queue, 0);
      assert_not_null(event);

      analytics_free(analytics);
    }
  }

  describe("analytics_screen") {
    it("should enqueue a screen event") {
      analytics_t *analytics = analytics_init("XXX");

      int rc = analytics_screen(analytics, "Did Something", "abc123", NULL);
      assert_equal(rc, ANALYTICS_SUCCESS);

      analytics_event_t *event = (analytics_event_t *) list_at(analytics->queue, 0);
      assert_not_null(event);

      analytics_free(analytics);
    }
  }

  describe("analytics_alias") {
    it("should enqueue an alias event") {
      analytics_t *analytics = analytics_init("XXX");

      int rc = analytics_alias(analytics, "old id", "new id");
      assert_equal(rc, ANALYTICS_SUCCESS);

      analytics_event_t *event = (analytics_event_t *) list_at(analytics->queue, 0);
      assert_not_null(event);

      analytics_free(analytics);
    }
  }

  describe("analytics_group") {
    it("should enqueue an group event") {
      analytics_t *analytics = analytics_init("XXX");

      int rc = analytics_group(analytics, "groupid", NULL);
      assert_equal(rc, ANALYTICS_SUCCESS);

      analytics_event_t *event = (analytics_event_t *) list_at(analytics->queue, 0);
      assert_not_null(event);

      analytics_free(analytics);
    }
  }

  describe("analytics_hashmap_new") {
    it("should create a hashmap") {
      analytics_hashmap_t *hash = analytics_hashmap_new();
      assert_not_null(hash);
      analytics_hashmap_free(hash);
    }
  }

  describe("analytics_hashmap_free") {
    // TODO: better test
    it("should work") {
      analytics_hashmap_t *hash = analytics_hashmap_new();
      analytics_hashmap_free(hash);
    }
  }

  describe("analytics_hashmap_set") {
    it("should set `key` to `value`") {
      analytics_hashmap_t *hash = analytics_hashmap_new();
      analytics_hashmap_set(hash, "foo", "bar");
      const char *foo = analytics_hashmap_get(hash, "foo");
      assert_str_equal(foo, "bar");
      analytics_hashmap_free(hash);
    }
  }

  describe("analytics_hashmap_get") {
    it("should return the value of `key`") {
      analytics_hashmap_t *hash = analytics_hashmap_new();
      analytics_hashmap_set(hash, "foo", "bar");
      const char *foo = analytics_hashmap_get(hash, "foo");
      assert_str_equal(foo, "bar");
      analytics_hashmap_free(hash);
    }

    it("should return NULL if `key` is not set") {
      analytics_hashmap_t *hash = analytics_hashmap_new();
      const char *foo = analytics_hashmap_get(hash, "foo");
      assert_null(foo);
      analytics_hashmap_free(hash);
    }
  }

  describe("analytics_hashmap_serialize") {
    it("should serialize the map") {
      analytics_hashmap_t *hash = analytics_hashmap_new();
      analytics_hashmap_set(hash, "foo", "bar");
      analytics_hashmap_set(hash, "baz", "qux");

      const char *expected = "{\n"
                             "  \"foo\": \"bar\",\n"
                             "  \"baz\": \"qux\"\n"
                             "}\n";

      const char *str = analytics_hashmap_serialize(hash);
      assert_str_equal(str, expected);

      free((char*)str);

      analytics_hashmap_free(hash);
    }
  }

  return assert_failures();
}
