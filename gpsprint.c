#include "gpsdclient.h"

#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS 70
typedef struct satellite_t satellite_t;
bool usedFlags[MAXCHANNELS];

/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:		gpsprint.c - The main file to print the gps data
--
-- PROGRAM:			GPS
--
-- FUNCTIONS:		void print_gps_data(const struct gps_data_t *gpsdata)
--					
--
-- DATE:			November 7, 2017
--
--
-- DESIGNER:		Vafa Dehghan Saei, William Murphy
--
-- PROGRAMMER:		Vafa Dehghan Saei, William Murphy
--
-- NOTES:			This is where the printing of the gps data is done.
----------------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:	print_gps_data
--
-- DATE:		November 7, 2017
--
--
-- DESIGNER:	Vafa Dehghan Saei, William Murphy
--
-- PROGRAMMER:	 Vafa Dehghan Saei
--
-- INTERFACE:	void print_gps_data(const struct gps_data_t *gpsdata) 
--					const struct gps_data_t *gpsdata: The struct that holds all the gps data/info
--
--
-- RETURNS:		Void
--
-- NOTES:		Prints the GPS data if there are satelites visible. Prints the PRN, elevation, azimuth and fix time.
--
----------------------------------------------------------------------------------------------------------------------*/
void print_gps_data(const struct gps_data_t *gpsdata)
{
	for (int i = 0; i < MAXCHANNELS; i++)
	{
		usedFlags[i] = false;
		for (int j = 0; j < gpsdata->satellites_used; j++) 
		{
			if (gpsdata->skyview[j].used == gpsdata->skyview[i].PRN)
			{
				usedFlags[i] = true;
			}
		
		}
	}
	if (gpsdata->satellites_visible != 0) 
	{
		for (int i = 0; i < MAX_POSSIBLE_SATS; i++)
		{
			if (i < gpsdata->satellites_visible) 
			{
				gpsdata->skyview[i].PRN, gpsdata->skyview[i].elevation, gpsdata->skyview[i].azimuth, 
			(int)gpsdata->skyview[i].ss, gpsdata->skyview[i].used ? 'Y' : 'N');
			}
		}	
	}
	if (isnan(gpsdata->fix.time) == 0) 
	{
		time_t seconds = (time_t)(gpsdata->fix.time);
		char result[70];
		if (strftime(result, sizeof result, "%c", gmtime(&seconds)))
		{
			fprintf(stdout, "Time: %s ", result);
		}
		else 
		{
			printf("strftime failed");
		}
	}
	if (gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.latitude) == 0)
	{
		char* deg_str = deg_to_str(deg_dd, fabs(gpsdata->fix.latitude));
		fprintf(stdout, " Latitude %s %c;", deg_str, (gpsdata->fix.latitude < 0) ? 'S' : 'N');
		fflush(stdout);
		free(deg_str);
	}
	else 
	{
		printf("n/a\n");
	}
	if (gpsdata->fix.mode >- MODE_2D && isnan(gpsdata->fix.longitude) == 0)
	{
		char* deg_str = deg_to_str(deg_dd, fabs(gpsdata->fix.longitude));
		fprintf(stdout, " Longitude %s %c;\n", deg_str, (gpsdata->fix.longitude < 0) ? 'W' : 'E');
		fflush(stdout);
		free(deg_str);
	}
	else 
	{	
		printf("n/a\n");
	}
}
