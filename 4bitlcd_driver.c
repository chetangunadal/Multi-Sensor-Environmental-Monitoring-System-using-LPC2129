#include<lpc21xx.h>
#include"header.h"
unsigned int temp;
void lcd_cmd(unsigned char cmd)
{
temp=(cmd&0xf0)<<16;
IOCLR1=0xfe<<16;
IOSET1=temp;
IOCLR1=1<<18|1<<17;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

temp=(cmd&0x0f)<<20;
IOCLR1=0xfe<<16;
IOSET1=temp;
IOCLR1=1<<18|1<<17;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_data(unsigned char data)
{
temp=(data&0xf0)<<16;
IOCLR1=0xfe<<16;
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

temp=(data&0x0f)<<20;
IOCLR1=0xfe<<16;
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_init()
{
IODIR0=0xfe<<16;
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x0e);
lcd_cmd(0x01);
}

void lcd_string(char *p)
{
	while(*p)
	{
		lcd_data(*p);
		p++;
	}
}




