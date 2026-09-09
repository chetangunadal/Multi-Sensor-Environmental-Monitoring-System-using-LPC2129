#include<lpc21xx.h>
#include"header.h"


void adc_init()
{
PINSEL1=0x15400000;
ADCR=0x00200400;
}
#define DONE (ADDR>>31)
int adc_read(int chnum)
{  
ADCR|=(1<<chnum);
ADCR|=(1<<24);
while(DONE==0);
ADCR^=(1<<24);
ADCR^=(1<<chnum);
//return 0;
return (ADDR>>6)&0x3ff;
}
