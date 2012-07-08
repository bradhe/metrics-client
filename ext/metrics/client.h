#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SEPERATOR ":"

int metric_transmit(char *, int);
int metricd(const char *, const char *, double);
int metricf(const char *, const char *, float);
int metrici(const char *, const char *, int);
