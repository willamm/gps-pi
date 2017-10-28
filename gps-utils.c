#include "gpsdclient.h"

int gps_read_data(struct gps_data_t *gpsdata)
{
	for(;;)
	{
		if (!gps_waiting(gpsdata, 5000000))
		{
			return -1;
		} 
		else
		{
			errno = 0;
			if (gps_read(gpsdata) == -1)
			{
				return -1;
			}
			else 
			{
				print_gps_data(gpsdata);
			}
		}
		// Get user input
	}
}

char* deg_to_str(enum deg_str_type type, double degrees)
{
	const int MAX_STR_LENGTH = 40;
	char* deg_str = malloc(sizeof(MAX_STR_LENGTH));	
	if (degrees < 0 || degrees > 360)
	{
		strncat(deg_str, "nan", 3);
		return deg_str;
	}
	double int_part = 0.0;
	double fract_part = modf(degrees, &int_part);
	if (deg_dd == type)
	{
		snprintf(deg_str, MAX_STR_LENGTH, "%3d.%06ld", (int)int_part, (long)(fract_part * 1000000));
		return deg_str;
	}
	return deg_str;
}
