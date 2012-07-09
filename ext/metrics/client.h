#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef struct {
  int socket;
  char * user_key;
  struct sockaddr * server_addr;
} metrics_connection;

int report_metricd(metrics_connection *, const char *, double);
int report_metricf(metrics_connection *, const char *, float);
int report_metrici(metrics_connection *, const char *, int);

int metrics_connect(char *, int, char *, metrics_connection **);
int metrics_disconnect(metrics_connection *);
