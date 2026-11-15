#include<lpc21xx.h>
#include"header.h"
#define LED (1<<17)
#define LED1 (1<<18)
#define LED2 (1<<19)
#define LED3 (1<<16)
#define water (1<<5)

#define ldr (1<<17)
int main()
{
	unsigned int adc_value;
	unsigned int moisture_value;
	int temp;
	IODIR0|=LED|LED1|LED2|LED3;
	IODIR0&=~water;
	
	IOSET0=LED|LED1|LED2|LED3;
	uart0_init(9600);
	adc_init();
	uart0_txt_string("\r\n SENSORS:\r\n");
	while(1)
	{		
		//TEMPERATURE
		adc_value=adc_read(1);
		temp=(adc_value*3.3*100)/1023;
		uart0_txt_string("\r\n tempetarure:\r\n");
		uart0_int(temp);
		if(temp>35)
		{
			IOCLR0=LED;
			uart0_txt_string("\r\n LED ON\r\n");
		}
		else
		{
			IOSET0=LED;
			uart0_txt_string("\r\n LED OFF\r\n");
		}
	
		
		//WATER SENSOR
		
		if((IOPIN0&water)==0)
		{
			IOCLR0=LED1;
			uart0_txt_string("\r\n Detected \r\n");
		}
		else
		{
			IOSET0=LED1;
			uart0_txt_string("\r\n Not detected\r\n");
		}
		
		//LDR sensor
		adc_value=adc_read(2);
		if(adc_value<500)
		{
			IOCLR0=LED2;
			uart0_txt_string("\r\n Normal \r\n");
		}
		else
		{
			IOSET0=LED2;
		uart0_txt_string("\r\n High \r\n");
	}
		
	//MOISTURE SENSOR
	moisture_value=adc_read(3);
	if(moisture_value<800)
	{
		IOCLR0=LED3;
		//lcd_string("SOIL DRY\r\n");
		uart0_txt_string("\r\n SOIL DRY \r\n");
	}
	else
	{
		IOSET0=LED3;
		//lcd_string("SOIL WET \r\n");
		uart0_txt_string("\r\n SOIL WET \r\n");
	}
	if((temp>35) || (moisture_value<800) || (adc_value>500) || ((IOPIN0&water)==0))
			{
				uart0_txt_string("\r\n STATUS:ALERT \r\n");
				IOSET0=LED;
				uart0_txt_string("\r\n RED-LED ON \r\n");
				IOCLR0=LED1;
				IOSET0=LED2;
			}
			else
			{
				uart0_txt_string("\r\n STATUS:SAFE\r\n");
				IOCLR0=LED;
				uart0_txt_string("\r\n GREEN-LED ON \r\n");
			   IOSET0=LED1;
				IOSET0=LED2;
	}
}
	}
