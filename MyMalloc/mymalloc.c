#include <stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "mymalloc.h"

static char bigMemory[4096] ={'4', '0', '9', '6'};

typedef struct metaD {
	unsigned short sizeB;
	unsigned short mNum;
} meta;

void * mymalloc(int x,char* file,int line) 
{
	int s,e,i; //start, end, index
	s = 0;
	e = 0;
	i = 4;
	void* ptr = NULL;
	
	if(x <= 0)
	{
		printf("Error: Unable to allocate memory size less than 1. File: %s Line %i\n", file, line);
		return ptr;
	}
	if(x > 4092)
	{
		printf("Error: Unable to allocate memory size greater than initial array size. File: %s Line %i\n",file, line);
		return ptr;
	}
	
	//first time accessed create metadata to manage how much free space isleft in the array
	if (bigMemory[0] == '4' && bigMemory[1] == '0' && bigMemory[2] == '9' && bigMemory[3] == '6') 
	{
		int b = 4;
		for(b = 4; b < 4096; b++)
		{
			bigMemory[b] = '\0';
		}
		meta* super = (meta*)  &bigMemory[0];
  		super->mNum = 42096;
		super->sizeB = 4092; 
	} 
	meta* metaReader = (meta*)  &bigMemory[0];
	
	while((i + e) < 4096) //looks through while index + end
	{
		if(bigMemory[i] == '\0') //found empty space check the block size
		{
			if(s == 0)
			{
				s = i;
				e++;
			}
			else
			{
				e++;
			}
		}
		if(e == (x+4)) //block is big enough add meta and return ptr
		{
			//adds th metadata for this entry
			metaReader = (meta*) &bigMemory[s];
			metaReader->sizeB = x;
			metaReader->mNum = 42069;
			ptr = &bigMemory[s+4];
			
			return ptr;
		}
		if(bigMemory[i] != '\0')
		{
			s = 0;
			e = 0;
			unsigned short skip = 0;
			metaReader = (meta*) &bigMemory[i];
			if (metaReader->mNum == 42069) {
				skip = metaReader->sizeB;
			}
			i = i+skip+4;
		}
	}
	return ptr;	
}


void myfree (void* ptr, char* file, int line)
{ 
	
	char* check = (char*)  ptr;
	meta* metaR = NULL; 
	if (check-2 <= &bigMemory[0] || check-2 > &bigMemory[4095]) 
	{
		printf("Unable to free. Please enter a valid pointer. File: %s Line %i\n", file, line);		
		return;
	}
	metaR = (meta*) (check-4); 
	unsigned short valid = metaR->mNum;
	unsigned short sizetofree = (metaR->sizeB)+4;
	
	if (valid == 42069) 
	{
		int a = 0; 
		for (a = -4; a < sizetofree-4; a++) 
		{
			*(check + a) = '\0';	
		}
	} 
	else 
	{
		printf("%p is an invalid pointer. File: %s Line: %i\n",ptr,file,line);
		return;
	}
}	
