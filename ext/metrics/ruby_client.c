#include <ruby.h>
#include "client.h"

static VALUE metrics_report_metric(VALUE self, VALUE user_id, VALUE key, VALUE val) {
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

void Init_client(void) {
  VALUE klass = rb_define_class("Metrics", rb_cObject);
  rb_define_singleton_method(klass, "report_metric", metrics_report_metric, 0);
}
