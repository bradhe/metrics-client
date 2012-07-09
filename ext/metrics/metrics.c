#include <ruby.h>
#include "client.h"

static VALUE cNativeConnectionInfo;
static VALUE cNativeClient;

static VALUE rb_metrics_report_metric(VALUE self, VALUE key, VALUE val) {
  char * key_str;
  VALUE _conn;
  metrics_connection * conn;
  int result = 0;

  key_str = RSTRING_PTR(key);
  _conn = rb_iv_get(self, "@metrics_connection");

  /* Aaand we're back! */
  Data_Get_Struct(_conn, metrics_connection, conn);

  /* Figure out what this belongs to and call the apprioriate one. */
  switch(TYPE(val)) {
    case T_FIXNUM:
      result = report_metrici(conn, (const char *)key_str, FIX2INT(val));
      break;
    case T_FLOAT:
      result = report_metricd(conn, (const char *)key_str, NUM2DBL(val));
      break;
    default:
      rb_raise(rb_eTypeError, "Value is not a valid type. Expecting Fixnum or Float.");
      break;
  }

  return (result > 0) ? T_TRUE : T_FALSE;
}

static VALUE rb_metrics_initialize(VALUE self, VALUE hostname, VALUE port, VALUE user_key) {
  metrics_connection * conn;
  VALUE _conn;

  if(!FIXNUM_P(port)) {
    rb_raise(rb_eTypeError, "Port is not a Fixnum.");
    return T_FALSE;
  }

  metrics_connect(RSTRING_PTR(hostname), FIX2INT(port), RSTRING_PTR(user_key), &conn);

  _conn = Data_Make_Struct(cNativeConnectionInfo, metrics_connection, 0, metrics_disconnect, conn);

  /* save this for later...lets see what happens! */
  rb_iv_set(self, "@metrics_connection", _conn);

  return T_TRUE;
}

void Init_metrics(void) {
  VALUE mMetrics = rb_define_module("Metrics");
  cNativeClient = rb_define_class_under(mMetrics, "NativeClient", rb_cObject);
  cNativeConnectionInfo = rb_define_class_under(cNativeClient, "Info", cNativeConnectionInfo);

  rb_define_method(cNativeClient, "initialize",         rb_metrics_initialize,          3);
  rb_define_method(cNativeClient, "report_metric",      rb_metrics_report_metric,       2);
}
