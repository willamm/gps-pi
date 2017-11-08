#include "gpsdclient.h"
/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:		gps-util.c - The function that reads the gps data.
--
-- PROGRAM:			GPS
--
-- FUNCTIONS:		int gps_read_data(struct gps_data_t *gpsdata) 
--					char* deg_to_str(enum deg_str_type type, double degrees)
--
--
-- DATE:			November 7, 2017
--
--
-- DESIGNER:		Vafa Dehghan Saei, William Murphy
--
-- PROGRAMMER:		Vafa Dehghan Saei, William Murphy
--
-- NOTES:			This file is the entry point of GPS, and where the stream to the gpsd is opened
--                  This file also mallocs and frees the gps_data_t struct.
----------------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:	gps_read_data
--
-- DATE:		November 7, 2017
--
--
-- DESIGNER:	Vafa Dehghan Saei, William Murphy
--
-- PROGRAMMER:	 William Murphy
--
-- INTERFACE:	int gps_read_data(struct gps_data_t *gpsdata) 
--					struct gps_data_t *gpsdata: The struct that holds all the gps data/info
--
--
-- RETURNS:		If the function fails, it returns a -1.
--
-- NOTES:		Checks to see if there is gps data waitng to be read, and if there it is the data is sent to another function to print.
--
----------------------------------------------------------------------------------------------------------------------*/
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


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:	deg_to_str
--
-- DATE:		November 7, 2017
--
--
-- DESIGNER:	Vafa Dehghan Saei, William Murphy
--
-- PROGRAMMER:  Vafa Dehghan Saei
--
-- INTERFACE:	int gps_read_data(struct gps_data_t *gpsdata) 
--				enum deg_str_type type: Here in case if we want to use more printing formats in the future, not in use now
--				double degrees: the degrees of the gps
--
--
-- RETURNS:		This function returns the latitutde and longitude as a string.
--
-- NOTES:		This function takes in the degrees and returns it as a string
--
----------------------------------------------------------------------------------------------------------------------*/
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
