/*
 * LCD.c
 *
 * Created: 04/11/2021 22:05:30
 *  Author: Default
 */ 


/*LCD command write function*/ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define RS PC0
#define RW PC1
#define EN PC2
#define LCD_Data_Port PORTD 
#define LCD_Cmd_Port PORTC 
#define LCD_Cmd_Dir DDRC 
#define LCD_Data_Dir DDRD 

/*Array to store hexadecimal values for custom characters */
const short Custorm_Chars5X8[] = {0xe,0x1b,0x11,0x11,0x1f,0x1f,0x1f};// Code for CGRAM memory space 0: Battery
const short Cord5X8[]={0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};//Code for Charger 
const short Tower5x8[]={0x1f,0x15,0xe,0x4,0x4,0x4,0x4};//Code for tower
const short DataCell5x8[]={	0x1,0x1,0x5,0x5,0x15,0x15,0x15};//COde for data cell
const short HalfCord5X8[]={	0xa,0xa,0x1f,0x11,0x11,0xe,0x4};//Code for Half filled cord 
const short Bluetooth5X8[]={0x0,0x4,0x16,0xf,0x4,0xf,0x16,0x4};//Code for Blue tooth
const short Bell5x8[]={	0x4,0xe,0xe,0xe,0x1f,0x0,0x4,0x00};//hexCode for Bell
const short Music5x8[]={0x3,0x7,0xd,0x9,0xb,0x1b,0x18,0x00};//Hex code for Music
	



void LCD_Cmd(unsigned char cmd){ 
	LCD_Data_Port = cmd; 
	LCD_Cmd_Port &= ~(1<<RS); /* RS=0 command reg. */ 
	LCD_Cmd_Port &= ~(1<<RW); /* RW=0 Write operation */ 
	_delay_us(1); 
	LCD_Cmd_Port |= (1<<EN); /* Enable pulse ON */
	_delay_us(1); 
	LCD_Cmd_Port &= ~(1<<EN); /* Enable pulse OFF */ 
	_delay_ms(2); 
	}
	
/*LCD data write function */ 
void LCD_Char (unsigned char char_data){ 
	LCD_Data_Port = char_data; 
	LCD_Cmd_Port |= (1<<RS); /* RS=1 Data reg. */ 
	LCD_Cmd_Port &= ~(1<<RW); /* RW=0 write operation */ 
	_delay_us(1); 
	LCD_Cmd_Port |= (1<<EN); /* Enable Pulse ON */ 
	_delay_us(1); 
	LCD_Cmd_Port &= ~(1<<EN); /* Enable Pulse ON */ 
	_delay_ms(2); 
	}
	
/*LCD Initialize function */ 
void LCD_Init (void){ 
	LCD_Cmd_Dir = 0xFF; /* Make LCD command port direction as output pins*/ 
	LCD_Data_Dir = 0xFF; /* Make LCD data port direction as output pins*/ 
	_delay_ms(50); /* LCD Power ON delay always >15ms */ 
	LCD_Cmd(0x02); /* Return display to its home position */ 
	LCD_Cmd(0x38); /* Initialization of 16X2 LCD in 8bit mode */ 
	LCD_Cmd(0x0F); /* Display ON Cursor Blinking */ 
	LCD_Cmd(0x06); /* Auto Increment cursor */ 
	LCD_Cmd(0x01); /* Clear display */ 
	}
	
/*Clear LCD Function*/ 
void LCD_Clear(void){ 
	LCD_Cmd(0x01); /* clear display */ 
	LCD_Cmd(0x02); /* Return display to its home position */ 
	}
	
/*Send string to LCD function */ 
void LCD_String (char *str){ 
	int i; /* Send each char of string till the NULL */ 
	for(i=0;str[i]!=0;i++){ 
		LCD_Char(str[i]); 
		} 
		}
		
/*Send string to LCD with xy position */ 
void LCD_String_xy (char row, char pos, char *str){ 
	if (row == 0 && pos<16){ 
		LCD_Cmd((pos & 0x0F)|0x80);/* Command of first row and required position<16 */ 
		} 
		else if (row == 1 && pos<16){ 
			LCD_Cmd((pos & 0x0F)|0xC0);/* Command of second row and required position<16 */ 
			} 
			LCD_String(str); /* Call LCD string function */
}

void Load_Custom_Char(){ /*Load custom char into the CGROM*/
	LCD_Cmd(0x40); // Set CGRAM Address
	for (int i = 0; i <= sizeof(Custorm_Chars5X8); i++)
	LCD_Char(Custorm_Chars5X8[i]);
	LCD_Cmd(0x48); 
	for (int i = 0; i <= sizeof(Cord5X8); i++)	
	LCD_Char(Cord5X8[i]);
	LCD_Cmd(0x50); 
	for (int i = 0; i <= sizeof(Tower5x8); i++){
	LCD_Char(Tower5x8[i]);	
	}
	LCD_Cmd(0x58);
	for (int i = 0; i <= sizeof(DataCell5x8); i++)
	LCD_Char(DataCell5x8[i]);
	LCD_Cmd(0x60);
	for (int i = 0; i <= sizeof(HalfCord5X8); i++)
	LCD_Char(HalfCord5X8[i]);
	LCD_Cmd(0x68);
	for (int i = 0; i <= sizeof(Bluetooth5X8); i++)
	LCD_Char(Bluetooth5X8[i]);
	LCD_Cmd(0x70);
	for (int i = 0; i <= sizeof(Bell5x8); i++)
	LCD_Char(Bell5x8[i]);
	LCD_Cmd(0x78);
	for (int i = 0; i <= sizeof(Music5x8); i++)
	LCD_Char(Music5x8[i]);

	LCD_Cmd(0x80); // Return to Home
	}