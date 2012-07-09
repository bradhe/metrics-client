#include <ruby.h>
#include "client.h"

static VALUE rb_metrics_report_metric(VALUE self, VALUE user_id, VALUE key, VALUE val) {
  char * user_id_str, * key_str;
  int result = 0;

  user_id_str = RSTRING_PTR(user_id);
  key_str = RSTRING_PTR(key);

  /* Figure out what this belongs to and call the apprioriate one. */
  switch(TYPE(val)) {
    case T_FIXNUM:
      result = metrici((const char *)user_id_str, (const char *)key_str, FIX2INT(val));
      break;
    case T_FLOAT:
      result = metricd((const char *)user_id_str, (const char *)key_str, NUM2DBL(val));
      break;
    default:
      rb_raise(rb_eTypeError, "Value is not a valid type. Expecting Fixnum or Float.");
      break;
  }

  return (result > 0) ? T_TRUE : T_FALSE;
}

static VALUE rb_metrics_initialize(VALUE self, VALUE hostname, VALUE port) {
  if(!FIXNUM_P(port)) {
    rb_raise(rb_eTypeError, "Port is not a Fixnum.");
    return T_FALSE;
  }

  rb_iv_set(self, "hostname", hostname);
  rb_iv_set(self, "port", port);

  return T_TRUE;
}

void Init_metrics(void) {
  VALUE rb_mMetrics = rb_define_module("Metrics");
  VALUE rb_cNativeClient = rb_define_class_under(rb_mMetrics, "NativeClient", rb_cObject);
  rb_define_singleton_method(rb_cNativeClient, "report_metric", rb_metrics_report_metric, 3);
  rb_define_method(rb_cNativeClient, "initialize", rb_metrics_initialize, 2);
}
