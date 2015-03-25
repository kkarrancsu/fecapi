/*
   Description: Include file for BERTOOLS Library
*/

#ifndef _LIBBERTOOLS_H
#define _LIBBERTOOLS_H

// ##################### Includes #########################  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 



// #################### Constants #########################
#define BERMINFRAMES (10000)   
#define BERMINERRORS  (100) 
#define BERMAXBITS    (1000000000)
#define CRCSIZE (16)
// #################### Function Declarations #########################

void char2bin(unsigned char *inbuffer,int buffSize);
void gaussnoise(float *inBuffer, int buffSize, float sigma);
int compBER(unsigned char *inBuffer1, unsigned char *inBuffer2,int buffSize);
void randBuffer(unsigned char *dataBuffer,int buffSize, int charOut);
#endif  // _LIBBERTOOLS_H


