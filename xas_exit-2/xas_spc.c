/************************************************************************
				xasSystemPowerController.c - Copyright breo

**************************************************************************/

#include "xas_spc.h"

#include <stdio.h>


/**
* @return int
*/
int execHalt( )
{
	int i = 0;

	char cmd2exec[] = "sudo halt";
	printf("\nThe system is going to %s now...\n",cmd2exec);
	i = system( cmd2exec );

	return i; // it never will be returned
}

/**
* @return int
*/
int execReboot( )
{
	int i = 0;

	char cmd2exec[] = "sudo reboot";
	printf("\nThe system is going to %s now...\n",cmd2exec);
	i = system( cmd2exec );

	return i; // it never will be returned
}

/**
* @return int
*/
int execCloseGDM( )
{
	int i = 0;

	char cmd2exec[] = "sudo killall gdm";
	i = system( cmd2exec );


	return i; // it never will be returned
}

//int main(void){ return 0; }
