#include<stdio.h>
#include<string.h>
#include"header.h"
#include<lpc21xx.h>
#define R (1<<17)
#define G (1<<18)
#define Y (1<<19)
#define water (IOPIN0&(1<<10))  //p0.10 coonesting the water sensor
int main()
{
	float vout=0,temp=0,light_percent=0,moisture_percent=0;
	int adcout;
	char s[100];
	IODIR0=R|Y|G;
	IOSET0=R|Y|G;
	uart0_init(9600);
	lcd_init();
	adc_init();
	while(1)
	{
		
		adcout=adc_read(1);
    vout=(adcout*3.3)/1023;
    temp=(vout-0.5)*100;
		sprintf(s,"TEMP:%.2f",temp);
		lcd_cmd(0x80);
		lcd_string(s);
		sprintf(s,"Temperature : %.2f 'C\n",temp);
		uart0_string(s);
		
		
		adcout=adc_read(2);
		light_percent = (adcout / 1023.0) * 100.0;
		if(light_percent<25)
			sprintf(s,"Light : LOW\n");
		else if(light_percent>=25 && light_percent<75)
			sprintf(s,"Light : MEDIUM\n");
		else
			sprintf(s,"Light : HIghintencity\n");
		uart0_string(s);
		
		
		adcout=adc_read(3);
		moisture_percent = (adcout / 1023.0) * 100.0;
	  sprintf(s,"Soil Moisture : %.2f\n",moisture_percent);
		uart0_string(s);
		lcd_cmd(0xc0);
		if(water)
		{
			uart0_string("Water Sensor : WATER DETECTED\n\r");
			uart0_string("System Status : SAFE\n\r");
			uart0_string("LED Status : GREEN\n\r\n\r");
			IOSET0=R|Y|G;
			IOCLR0=G;
			lcd_string("Status : SAFE");
		}
		else
		{
			uart0_string("Water Sensor : NOT DETECTED\n\r");
		  uart0_string("System Status : DANGER\n\r");
			uart0_string("LED Status : RED\n\r\n\r");
			IOSET0=R|Y|G;
			IOCLR0=R;
			lcd_string("Status : DANGER");
		}
		delay_ms(1000);
		lcd_cmd(0x01);
	}
}
