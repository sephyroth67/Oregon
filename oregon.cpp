#include "RCSwitch.h"
#include "RcOok.h"
#include "Sensor.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int loggingok;	






int main(int argc, char *argv[])
{
	int RXPIN = 2;
	int TXPIN = 0;
	time_t ltime;
    struct tm * curtime;
	FILE *fp;	 // Global var file handle 
	char buffer[80];
	
	
	if(argc==2) {
	  loggingok=1;
	} else {
	  loggingok=0;
	}

	if(wiringPiSetup() == -1)
		{
			return 0;
			printf("failed wiring pi\n");
		}	

	RCSwitch *rc = new RCSwitch(RXPIN,TXPIN);
	
	
    printf("datetime,Temperature,Humidity,Pressure,Type,Channel\n");
	while (1)
 		{
			if ( rc->OokAvailable() )
				{
					char message[100];
					time( &ltime );
					curtime = localtime( &ltime );
					strftime(buffer,80,"%F %T", curtime);

 
					
					
					rc->getOokCode(message);
					/* printf(" %s\n ",message); */

					Sensor *s = Sensor::getRightSensor(message);
					if ( s != NULL )
						{
														
							printf("%s,%f,%f,%f,%d,%d\n",
							buffer,
							s->getTemperature(),
							s->getHumidity(),
							s->getPressure(),
							s->getSensType(),
							s->getChannel());
							if(loggingok) {
								fp = fopen(argv[1], "a");
    	 						
    	 						if (fp == NULL) {
	      							perror("Failed to open log file!"); // Exit if file open fails
	      							exit(EXIT_FAILURE);
								}
								
								fprintf(fp," {\"datetime\": \"%s\", \"temperature\": \"%f\", \"humidity\": \"%f\", \"rain\": \"%f\", \"direction\": \"%f\", \"speed\": \"%f\", \"pressure\": \"%f\", \"class\": \"%d\", \"type\": \"%d\", \"channel\": \"%d\" } \n",
								buffer,
								s->getTemperature(),
								s->getHumidity(),
								s->getRain(),
								s->getDirection(),
								s->getSpeed(),
								s->getPressure(),
								s->getSensClass(),
								s->getSensType(),
								s->getChannel());		
								fflush(fp);
								fclose(fp);
  							}
							
						}
					delete s;
				}
			delay(1000);
 		}
 	
}
