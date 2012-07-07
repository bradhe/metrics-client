#include "client.h"

int metric_transmit(char * data, int len) {
  struct sockaddr_in server_addr;
  int fd;

  if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    printf("Could not create socked: %d\n", fd);
    exit(-1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(8081);

  if(sendto(fd, data, len, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    printf("Failed to send data.\n");
    exit(1);
  }

  close(fd);

  return(0);
}

int metricd(const char * user_id, const char * metric_name, double value) {
  char data[1024];
  int data_len;

  memset(data, '\0', 1024);
  data_len = sprintf(data, "%s%s%s%s%.8f", user_id, SEPERATOR, metric_name, SEPERATOR, value);

  return metric_transmit(data, data_len);
}

int metricf(const char * user_id, const char * metric_name, float value) {
  char data[1024];
  int data_len;

  memset(data, '\0', 1024);
  data_len = sprintf(data, "%s%s%s%s%.8f", user_id, SEPERATOR, metric_name, SEPERATOR, value);

  return metric_transmit(data, data_len);
}

int metrici(const char * user_id, const char * metric_name, int value) {
  char data[1024];
  int data_len;

  memset(data, '\0', 1024);
  data_len = sprintf(data, "%s%s%s%s%d", user_id, SEPERATOR, metric_name, SEPERATOR, value);

  return metric_transmit(data, data_len);
}
