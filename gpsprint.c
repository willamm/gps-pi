#include "gpsdclient.h"

#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS 70

typedef struct satellite_t satellite_t;

bool usedFlags[MAXCHANNELS];

static void print_visible(const struct gps_data_t *gpsdata, const int i)
{
	fprintf(stdout, "PRN: %3d Elevation: %02d Azimuth: %03d SNR: %02d Used: %c\n",
			gpsdata->skyview[i].PRN, gpsdata->skyview[i].elevation, gpsdata->skyview[i].azimuth, 
			(int)gpsdata->skyview[i].ss, gpsdata->skyview[i].used ? 'Y' : 'N');
} 

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
				print_visible(gpsdata, i);
			}
		}	
	}
	if (isnan(gpsdata->fix.time) == 0) 
	{
		time_t seconds = (time_t)(gpsdata->fix.time);
		char result[70];
		if (strftime(result, sizeof result, "%c", gmtime(&seconds)))
		{
			fprintf(stdout, "Time: %s \n", result);
		}
		else 
		{
			printf("strftime failed");
		}
	}
	if (gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.latitude) == 0)
	{
		char* deg_str = deg_to_str(deg_dd, fabs(gpsdata->fix.latitude));
		fprintf(stdout, "Latitude: %s %c;", deg_str, (gpsdata->fix.latitude < 0) ? 'S' : 'N');
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
		fprintf(stdout, " Longitude: %s %c;\n", deg_str, (gpsdata->fix.longitude < 0) ? 'W' : 'E');
		fflush(stdout);
		free(deg_str);
	}
	else 
	{	
		printf("n/a\n");
	}
}
