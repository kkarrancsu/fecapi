/*
------------------------------------------------------------------------------
   Description: Generic tools used for calculating BER curves 
 
   Usage:       These routines will be called to perform testing 
                for various coding schemes 
                 
------------------------------------------------------------------------------
*/

#include <libbertools.h>



inline int putbit(int word, int loc, int bit) {
    return (((word)&(~((1)<<(loc))))^((bit)<<(loc)));
}


/*
------------------------------------------------------------------------------
  SYNOPSIS:
    void gaussnoise(float *inBuffer, int buffSize)

  ARGUMENTS: 
    float * inBuffer - buffer containing data to receive additive 
                       gaussian noise 
  PURPOSE:
    Add BPSK gaussian noise with standard deviation equal to sigma
    to a floating point input buffer 

------------------------------------------------------------------------------
*/

void gaussnoise(float *inBuffer, int buffSize, float sigma)
{
  int i;
  float udrn1=0.0,udrn2=0.0,noise=0.0;

  for (i=0;i<buffSize;i++)
    {
      while ((udrn1 = (float)drand48()) < 0.0000001);
      udrn2 = (float)drand48();
      noise = sigma*sqrt(-2*log(udrn1))*cos(2*M_PI*udrn2);
      inBuffer[i] += noise;
    }
  
}

/*
------------------------------------------------------------------------------
  SYNOPSIS:
         int compBER(unsigned char *inBuffer1, unsigned char *inBuffer2,int buffSize)

  ARGUMENTS: 
         inBuffer1,inBuffer2:  input buffers whose difference is to be computed
	 buffSize:             number of elements in each buffer 
  PURPOSE:
    Compute the number of bit differences between input buffers 

------------------------------------------------------------------------------
*/

int compBER(unsigned char *inBuffer1, unsigned char *inBuffer2,int buffSize)
{ 
  int i,totalDiff=0;
  int popCnt[256] =
    { 
      0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
      1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
      2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
      3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
      4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
    };
  
  
  for (i=0;i<buffSize;i++)
    {
      totalDiff += popCnt[inBuffer1[i]^inBuffer2[i]];	  
      
    }

  return totalDiff;
}

/*
------------------------------------------------------------------------------
  SYNOPSIS:
      void randBuffer(unsigned char *dataBuffer,int buffSize)

  ARGUMENTS: 
         dataBuffer:  pointer to buffer containing random data 
	 buffSize:             number of elements in each buffer 
  PURPOSE:
    Generate a random buffer of data 

------------------------------------------------------------------------------
*/




void randBuffer(unsigned char *dataBuffer,int buffSize, int charOut)
{
  int i;
  unsigned char randBit;

  for (i=0;i<buffSize;i++)
    {
      // generate random element 
      randBit = (unsigned char)((0x000010000&rand())>>16);
      // place in the data buffer 
      if (charOut == 0)
	dataBuffer[i>>3] = putbit(dataBuffer[i>>3],7-(i&0x7),randBit);
      else 
	dataBuffer[i] = randBit;
    }
}





/*
------------------------------------------------------------------------------
  SYNOPSIS:
      void char2bin(unsigned char *charBuffer,int buffSize)

  ARGUMENTS: 
         dataBuffer:  pointer to buffer containing unpacked chars 
	 buffSize:             number of elements in each buffer 
  PURPOSE:
    Pack the character buffer 

------------------------------------------------------------------------------
*/

void char2bin(unsigned char *inbuffer,int buffSize)
{
  int i;
  unsigned char fbit=0;
  
  for (i=0;i<buffSize;i++)
    {
      if (inbuffer[i] == 0)
	fbit = 0;
      else 
	fbit = 1;
      inbuffer[i>>3] = putbit(inbuffer[i>>3],7-(i&0x7),fbit);
    }
  
}



