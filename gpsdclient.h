#ifndef GPSD_CLIENT_H
#define GPSD_CLIENT_H

#include <stdio.h>
#include <gps.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

struct fixsource_t
{
	char *spec;
	char *server;
	char *port;
	char *device;
};

enum deg_str_type
{
	deg_dd,
	deg_ddmm,
	deg_ddmmss
};

int gps_read_data(struct gps_data_t *gpsdata);
void print_gps_data(const struct gps_data_t *gpsdata);
char* deg_to_str(enum deg_str_type type, double degrees); 

#endif /*GPSD_CLIENT_H*/
