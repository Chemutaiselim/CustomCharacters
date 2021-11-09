/*
 * CustomCharacters_Code.c
 *
 * Created: 08/11/2021 15:32:31
 * Author : Default
 */ 

/*Typical Header file inclusion and CPU frequency definition*/ 
#define F_CPU 8000000UL 
#include <avr/io.h> 
#include <util/delay.h> 
#include "LCD.h"
 /*Inclusion of our own defined header file*/
 

/*Our main program*/ 
int main(void){ 
	LCD_Init(); /* Initialize LCD */ 
	Load_Custom_Char(); /* Load custom characters into CGRAM */ 
	LCD_Clear(); /* Clear LCD */ 
	LCD_String("Custom Chars");/* Display string on screen */ 
	_delay_ms(500); 
	LCD_Cmd(0xC0); /* Place cursor on the second row */ 
	
	const short Char5X8[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};
	for (int x=0; x < sizeof(Char5X8); x++)
	{
		LCD_Char(x);
		if(x != 2){
			LCD_String(" ");
		}
		
		_delay_ms(100);
		
	}
	for (int i = 0; i<16; i++)
	{
			LCD_Cmd(0x18);
	}

	
	
	
	
	return 0;
}

