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
 
/*Array to store hexadecimal values for custom characters */ 
const short Custorm_Chars5X8[] = { 
	0x0E,0x1B,0x11,0x11,0x1F,0x1F,0x1F,0x00,// Code for CGRAM memory space 0: Battery 
}
	
/*Our main program*/ 
int main(void){ 
	LCD_Init(); /* Initialize LCD */ 
	Load_Custom_Char(); /* Load custom characters into CGRAM */ 
	LCD_Clear(); /* Clear LCD */ 
	LCD_String("Custom Chars");/* Display string on screen */ 
	_delay_ms(1000); 
	LCD_Cmd(0xC0); /* Place cursor on the second row */ 
	LCD_Char(0x00); /* Display the character in address 0x00 of CGRAM*/ 
	return 0;
}

