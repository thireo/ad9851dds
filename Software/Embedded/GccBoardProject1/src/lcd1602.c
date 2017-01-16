/*
 * lcd1602.c
 *
 * Created: 27-12-2016 14:41:59
 *  Author: Andreas
 *  Inspired by Athir and Bravo
 */ 
#include "lcd1602.h"

union {
	struct  
	{
		unsigned int bit0	:1;
		unsigned int bit1	:1;
		unsigned int bit2	:1;
		unsigned int bit3	:1;
		unsigned int bit4	:1;
		unsigned int bit5	:1;
		unsigned int bit6	:1;
		unsigned int bit7	:1;
	};
	unsigned int completebyte;
} lcd_data_byte;


void lcd_cmd(uint8_t command)
{
	port_pin_set_output_level(LCD_D0,((command >> 0)  & 0x01));
	port_pin_set_output_level(LCD_D1,((command >> 1)  & 0x01));
	port_pin_set_output_level(LCD_D2,((command >> 2)  & 0x01));
	port_pin_set_output_level(LCD_D3,((command >> 3)  & 0x01));
	port_pin_set_output_level(LCD_D4,((command >> 4)  & 0x01));
	port_pin_set_output_level(LCD_D5,((command >> 5)  & 0x01));
	port_pin_set_output_level(LCD_D6,((command >> 6)  & 0x01));
	port_pin_set_output_level(LCD_D7,((command >> 7)  & 0x01));

	port_pin_set_output_level(LCD_EN,1);
	delay_ms(2);
	port_pin_set_output_level(LCD_EN,0);
	delay_ms(2);
}


void lcd_data(uint8_t data)
{
	port_pin_set_output_level(LCD_D0,((data >> 0)  & 0x01));
	port_pin_set_output_level(LCD_D1,((data >> 1)  & 0x01));
	port_pin_set_output_level(LCD_D2,((data >> 2)  & 0x01));
	port_pin_set_output_level(LCD_D3,((data >> 3)  & 0x01));
	port_pin_set_output_level(LCD_D4,((data >> 4)  & 0x01));
	port_pin_set_output_level(LCD_D5,((data >> 5)  & 0x01));
	port_pin_set_output_level(LCD_D6,((data >> 6)  & 0x01));
	port_pin_set_output_level(LCD_D7,((data >> 7)  & 0x01));

	port_pin_set_output_level(LCD_EN,1);
	port_pin_set_output_level(LCD_RS,1);
	delay_ms(2);
	port_pin_set_output_level(LCD_EN,0);
	port_pin_set_output_level(LCD_RS,0);
	delay_ms(2);
}

void lcd_send_string(char* string)
{
	while(*string)
	{
		//Send value of pointer as data to LCD
		lcd_data(*string);
		//Increment string pointer
		string++;
	}
}


void lcd_init(void)
{
	configure_lcd_pins();
	
	//Setup both lines of LCD
	lcd_cmd(0x38);
	delay_ms(6);
	//Set Cursor off - Enable LCD
	lcd_cmd(0x0E);
	delay_ms(6);
	//Clear Screen
	lcd_cmd(LCD_CMD_CLEAR_SCREEN);
	delay_ms(6);
	//Goto first position
	lcd_cmd(0x80);
}

void configure_lcd_pins(void)
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LCD_D0, &config_port_pin);
	port_pin_set_config(LCD_D1, &config_port_pin);
	port_pin_set_config(LCD_D2, &config_port_pin);
	port_pin_set_config(LCD_D3, &config_port_pin);
	port_pin_set_config(LCD_D4, &config_port_pin);
	port_pin_set_config(LCD_D5, &config_port_pin);
	port_pin_set_config(LCD_D6, &config_port_pin);
	port_pin_set_config(LCD_D7, &config_port_pin);
	
	port_pin_set_config(LCD_EN, &config_port_pin);
	port_pin_set_config(LCD_RW, &config_port_pin);
	port_pin_set_config(LCD_RS, &config_port_pin);
}

void lcd_clear_screen(void)
{
	lcd_cmd(LCD_CMD_CLEAR_SCREEN);
}

void lcd_set_line(unsigned char line)
{
	switch(line)
	{
		case 1:
			lcd_cmd(0x80);
			break;
		case 2:
			lcd_cmd(0xC0);
			break;
		default:
			break;
	}
}


void lcd_disp_freq(int freq)
{
	printnumberswiththousandsseparatorcomma(freq);
	//printfcomma2(freq);
}

void printfcomma2 (int n)
{
	char buffer[4];
			
	if (n < 1000)
	{
		sprintf (buffer,"%3d", n);
		//lcd_cmd(0x8B);
		lcd_send_string(buffer);
		return;
	}
		//lcd_cmd(LCD_CMD_MOVE_CURSOR_LEFT);
		//lcd_cmd(LCD_CMD_MOVE_CURSOR_LEFT);
		//lcd_cmd(LCD_CMD_MOVE_CURSOR_LEFT);
	printfcomma2 (n/1000);
	sprintf (buffer,".%03d", n%1000);

	//lcd_cmd(0x8B-0x03);
	lcd_send_string(buffer);
}


void printnumberswiththousandsseparatorcomma(uint32_t n) 
{
	char buffer[5];
    if (n < 1000) 
    {
        sprintf(buffer,"%d", n);
		lcd_send_string(buffer);
        return;
    }
    printnumberswiththousandsseparatorcomma(n / 1000);
    sprintf(buffer,".%03d", n % 1000);
	lcd_send_string(buffer);
}