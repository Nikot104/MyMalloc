#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h> //ADD THIS WHEN THE TIME COMES
#include<sys/time.h>
#include"mymalloc.h"
#include"mymalloc.c"

void main(int argc, char *argv[])
{
	//Initializes all the needed Vars. *point is the array used to store the pointers we will be malloc'ing. Alongside those are the time and counter variables.	
	char *point[5000];
	int i = 0;
	int w = 0;
	int j = 0;
	struct timeval starting, ending; //creates time stamps
	long timeElapsed = 0;
	long averageTime = 0;
	
	//TEST CASE A; STORE THEN FREE (IMMEDIATELY) 1 BYTE 150 TIMES
	
	int workCounter = 0;
	
	while(j < 100)
	{
	gettimeofday(&starting, NULL);
		
		
		for(i = 0; i < 150; i++)
		{
			point[1] = (char*) malloc(1);
			if(point[1] == NULL)
			{
				printf("ERROR: MALLOC RETURNED NULL\n");
				
			}
			free(point[1]);
		} 
		point[1] = NULL;
		
		
		
	
	
	gettimeofday(&ending, NULL); 
	
	timeElapsed = (ending.tv_sec * 1000000 + ending.tv_usec)-(starting.tv_sec * 1000000 + starting.tv_usec);
	averageTime += timeElapsed;
	j++;
	}
	averageTime = (averageTime/100);
	printf("TEST A: Average Time %ld microseconds\n", averageTime);
	averageTime = 0;
	//TEST CASE B; STORE 1 BYTE 50 TIMES, FREE, REPEAT 3 TIMES
	
	for(workCounter = 0; workCounter < 100; workCounter++)
	{
	gettimeofday(&starting, NULL); 
	for(i = 0; i < 50; i++)
	{
		point[i] = (char*) malloc(1);
		if(point[i] == NULL)
		{
			printf("ERROR: MALLOC RETURNED NULL\n");
		}
	}
 
	for(i = 0; i < 50; i++)
	{
		free(point[i]);
	} 
	
	for(i = 0; i < 50; i++)
	{
		point[i] = (char*) malloc(1);
		if(point[i] == NULL)
		{
			printf("ERROR: MALLOC RETURNED NULL\n");
		}

	} 
	for(i = 0; i < 50; i++)
	{
		free(point[i]);
	} 

	for(i = 0; i < 50; i++)
	{
		point[i] = (char*) malloc(1);
		if(point[i] == NULL)
		{
			printf("ERROR: MALLOC RETURNED NULL\n");
		}

	} 
	for(i = 0; i < 50; i++)
	{
		free(point[i]);
	} 
	
	gettimeofday(&ending, NULL); 
	timeElapsed = (ending.tv_sec * 1000000 + ending.tv_usec)-(starting.tv_sec * 1000000 + starting.tv_usec);
	averageTime += timeElapsed;
	}
	averageTime = (averageTime/100);
	printf("TEST B: Average Time %ld microseconds\n", averageTime);

	//TEST CASE C; RANDOMLY CHOOSE MALLOCING AND FREEING 1 BYTE, REPEAT 50 TIMES
	
	averageTime = 0;
	for(workCounter = 0; workCounter < 100; workCounter++)
	{
	gettimeofday(&starting, NULL); 
	i = 0;
	int counter = 0;
	while(counter < 50)
	{
		
		if(rand()%2 == 0)
		{
			point[i] = (char*) malloc(1);
			if(point[i] == NULL)
			{
				printf("ERROR: MALLOC RETURNED NULL\n");
			}
			i++;
			counter++;

		}
		else
		{ 
			if(i != 0)
			{
				i--;
				free(point[i]);
			}
			else
			{
			}
		} 
	}
	int bumblechum = 0;
	for(bumblechum = 0; bumblechum < i; bumblechum++)
	{
		free(point[bumblechum]);
	}
	gettimeofday(&ending, NULL); 
	timeElapsed = (ending.tv_sec * 1000000 + ending.tv_usec)-(starting.tv_sec * 1000000 + starting.tv_usec);
	averageTime += timeElapsed;
	}
	averageTime = (averageTime/100);
	printf("TEST C: Average Time %ld microseconds\n", averageTime);
	
	//TESTCASE D; RANDOMLY CHOOSE BETWEEN 64 BYTES AND 1 BYTE TO MALLOC OR FREE
	
	averageTime = 0;
	for(workCounter = 0; workCounter < 100; workCounter++)
	{
	gettimeofday(&starting, NULL); 
	int counter = 0; // Will count up to 50 for 50 memory allocations
	int memcounter = 0;
	int mem = 0;
	i = 0; // Will index where the last allocation was in the array
	while(counter < 50)
	{
	
		if(rand() % 2 == 0)
		{	
			mem = ((rand() % 64) + 1);
			
			point[i] = (char*) malloc(mem);
			if(point[i] == NULL)
			{
				printf("ERROR: MALLOC RETURNED NULL\n");
			}

			i++;
			counter++;
		}
		else
		{
			if(i != 0)
			{
				i--;
				free(point[i]);
			}
		}
	}

	int plumbus = 0;
	for(plumbus = 0; plumbus < i; plumbus++)
	{
		free(point[plumbus]);
	}
	gettimeofday(&ending, NULL); 
	timeElapsed = (ending.tv_sec * 1000000 + ending.tv_usec)-(starting.tv_sec * 1000000 + starting.tv_usec);
	averageTime += timeElapsed;
	}
	averageTime = (averageTime/100);
	printf("TEST D: Average Time %ld microseconds\n", averageTime);
	
	//TESTCASE E; malloc and free allocated space then try to free statically allocated ptr.
	
	
	averageTime = 0;
	for(workCounter = 0; workCounter < 100; workCounter++)
	{
		gettimeofday(&starting, NULL); 
		int * a = NULL;
		int butta = 32;
		a = &butta;
		char * c = (char*) malloc(sizeof(char)*5);
		free(c);	
		free(a);
	
	gettimeofday(&ending, NULL); 
	timeElapsed = (ending.tv_sec * 1000000 + ending.tv_usec)-(starting.tv_sec * 1000000 + starting.tv_usec);
	averageTime += timeElapsed;
	}
	averageTime = (averageTime/100);
	printf("TEST E: Average Time %ld microseconds\n", averageTime);
	
	//TESTCASE F; try mallocing over the size of the array. should return an error on second attempt at mallocing
	averageTime = 0;
	for(workCounter = 0; workCounter < 100; workCounter++)
	{
	gettimeofday(&starting, NULL); 
		
	char * stuff = (char*) malloc(1010);
	char * stuff2 = (char*) malloc(1010);
	char * stuff3 = (char*) malloc(1010);
	char * stuff4 = (char*) malloc(1010);
	free(stuff2);
	char * stuff5 = (char*) malloc(1010);
	free(stuff);
	free(stuff3);
	free(stuff4);
	free(stuff5);
	
	gettimeofday(&ending, NULL); 
	timeElapsed = (ending.tv_sec * 1000000 + ending.tv_usec)-(starting.tv_sec * 1000000 + starting.tv_usec);
	averageTime += timeElapsed;
	}
	averageTime = (averageTime/100);
	printf("TEST F: Average Time %ld microseconds\n", averageTime);	
	
	return;
}
