#include "gpsdclient.h"

static struct fixsource_t source;

int main(int argc, char** argv) 
{
    struct gps_data_t *gpsdata = malloc(sizeof (struct gps_data_t));
    source.server = "127.0.0.1";
    source.port = DEFAULT_GPSD_PORT;
    if (gps_open(source.server, source.port, gpsdata) != 0)
    {
	    fprintf(stderr, "%s: no gpsd running or network error: %d, %s\n", argv[0], errno, gps_errstr(errno));
	    exit(EXIT_FAILURE);
    }
    unsigned int flags = WATCH_ENABLE;
    if (source.device != 0)
    {
	    flags |= WATCH_DEVICE;
    }
    gps_stream(gpsdata, flags | WATCH_JSON, source.device);
    gps_read_data(gpsdata);
    gps_stream(gpsdata, WATCH_DISABLE, source.device);
    gps_close(gpsdata);
    free(gpsdata);
    return 0;
}
