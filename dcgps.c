#include "gpsdclient.h"

static struct fixsource_t source;

/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:		dcgps.c - The main entry point of the program.
--
-- PROGRAM:			GPS
--
-- FUNCTIONS:		int main(int argc, char** argv) 
--
--
-- DATE:			November 7, 2017
--
--
-- DESIGNER:		Vafa Dehghan Saei, William Murphy
--
-- PROGRAMMER:		William Murphy
--
-- NOTES:			This file is the entry point of GPS, and where the stream to the gpsd is opened
--                  This file also mallocs and frees the gps_data_t struct.
----------------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:	main
--
-- DATE:		November 7, 2017
--
--
-- DESIGNER:	Vafa Dehghan Saei, William Murphy
--
-- PROGRAMMER:	 William Murphy
--
-- INTERFACE:	int main(int argc, char** argv) 
--					int argc: Number of command line arguments
--					char** argv: pointer to the command line arguments
--
--
-- RETURNS:		If the function succeeds, and terminated successfully returns a 0;
--
-- NOTES:		This function is the application entry point.
--
----------------------------------------------------------------------------------------------------------------------*/

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
