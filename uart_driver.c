#include<lpc21xx.h>
void uart0_init(unsigned int baud)
{
	unsigned int pclk,result=0;
	if(VPBDIV==0x00)
		pclk=15000000;
	else if(VPBDIV==0x01)
		pclk=60000000;
		else if(VPBDIV==0x02)
			pclk=30000000;
		result=pclk/(16*baud);
		
		PINSEL0 |=0x05;
		U0LCR=0x83;
		//U0DLL=0x83;
		U0DLL=result&0x0ff;
		U0DLM=(result>>8)&0xff;
		U0LCR=0x03;
	
		
}


#define THRE ((U0LSR>>5)&1)

void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
}


#define RDR (U0LSR&1)

unsigned char uart0_rx()
{
	while(RDR==0);
	return U0THR;
}

void uart0_string( char *p)
{
	while(*p)
	{
		uart0_tx(*p);
		p++;
	}
}

void uart0_int( int num)
{
	char a[20];
	int i=0;
	if(num==0)
	{
		uart0_tx('0');
		return;
	}
	if(num<0)
	{
		uart0_tx('-');
		num*=-1;
	}
	while(num)
	{
		a[i++]=num%10+48;
		num/=10;
	}
	for(i--;i>=0;i--)
	{
		uart0_tx(a[i]);
	}
}

void uart0_float( float num)
{
	int a;
	if(num==0)
	{
		uart0_tx('0');
		return;
	}
	if(num<0)
	{
		uart0_tx('-');
		num*=-1;
	}
	a=num;
	num=(num-a)*1000000;
	
	uart0_int(a);
	uart0_tx('.');
	uart0_int(num);
}
