#include "client.h"

#define SEPERATOR ":"

int metric_transmit(metrics_connection * conn, char * data, int len) {
  if(sendto(conn->socket, data, len, 0, conn->server_addr, sizeof(conn->server_addr)) < 0) {
    printf("Failed to send data.\n");
    exit(1);
  }

  return(0);
}

int report_metricd(metrics_connection * conn, const char * metric_name, double value) {
  char data[1024];
  int data_len;

  memset(data, '\0', 1024);
  data_len = sprintf(data, "%s%s%s%s%.8f", conn->user_key, SEPERATOR, metric_name, SEPERATOR, value);

  return metric_transmit(conn, data, data_len);
}

int report_metricf(metrics_connection * conn, const char * metric_name, float value) {
  char data[1024];
  int data_len;

  memset(data, '\0', 1024);
  data_len = sprintf(data, "%s%s%s%s%.8f", conn->user_key, SEPERATOR, metric_name, SEPERATOR, value);

  return metric_transmit(conn, data, data_len);
}

int report_metrici(metrics_connection * conn, const char * metric_name, int value) {
  char data[1024];
  int data_len;

  memset(data, '\0', 1024);
  data_len = sprintf(data, "%s%s%s%s%d", conn->user_key, SEPERATOR, metric_name, SEPERATOR, value);

  return metric_transmit(conn, data, data_len);
}


int metrics_connect(char * hostname, int port, char * user_key, metrics_connection ** conn) {
  struct addrinfo *result;
  int fd;

  if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    fprintf(stderr, "Could not create socked: %d\n", fd);
    exit(-1);
  }

  if(getaddrinfo((const char *)hostname, NULL, NULL, &result) < 0) {
    fprintf(stderr, "Could not look up hostname %s", hostname);
    exit(-1);
  }

  (*conn) = (metrics_connection *)malloc(sizeof(metrics_connection));

  (*conn)->socket = fd;
  (*conn)->user_key = (char *)malloc(sizeof(char) * (strlen(user_key) + 1));

  memset((*conn)->user_key, '\0', sizeof(char) * (strlen(user_key) + 1));
  strcpy((*conn)->user_key, (const char *)user_key);

  (*conn)->server_addr = (struct sockaddr *)malloc(result->ai_addrlen);
  memcpy(result->ai_addr, (*conn)->server_addr, result->ai_addrlen);

  return(0);
}

/**
 * Disconnects from and frees a given metrics_connection object.
 *
 * conn - metrics_connection * - The connection object to free.
 */
int metrics_disconnect(metrics_connection * conn) {
  close(conn->socket);
  conn->socket = -1;

  free(conn->server_addr);
  free(conn->user_key);

  /* Finally done with struct itself. */
  free(conn);

  return(0);
}
