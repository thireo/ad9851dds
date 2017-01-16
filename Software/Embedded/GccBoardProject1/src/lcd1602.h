/*
 * lcd1602.h
 *
 * Created: 27-12-2016 14:42:19
 *  Author: Andreas
 */ 


#ifndef LCD1602_H_
#define LCD1602_H_

#include "asf.h"

#define LCD_D0 PIN_PA15 //IOPIN_CREATE_PIN(PORTA,PIN_PA15)
#define LCD_D1 PIN_PA16 //IOPIN_CREATE_PIN(PORTA,PIN_PA16)
#define LCD_D2 PIN_PA17 //IOPIN_CREATE_PIN(PORTA,PIN_PA17)
#define LCD_D3 PIN_PA18 //IOPIN_CREATE_PIN(PORTA,PIN_PA18)
#define LCD_D4 PIN_PA19 //IOPIN_CREATE_PIN(PORTA,PIN_PA19)
#define LCD_D5 PIN_PA20 //IOPIN_CREATE_PIN(PORTA,PIN_PA20)
#define LCD_D6 PIN_PA21 //IOPIN_CREATE_PIN(PORTA,PIN_PA21)
#define LCD_D7 PIN_PA22 //IOPIN_CREATE_PIN(PORTA,PIN_PA22)

#define LCD_EN PIN_PA23 //IOPIN_CREATE_PIN(PORTA,PIN_PA23)
#define LCD_RW PIN_PA24 //IOPIN_CREATE_PIN(PORTA,PIN_PA24)
#define LCD_RS PIN_PA25 //IOPIN_CREATE_PIN(PORTA,PIN_PA25)

#define LCD_CMD_CLEAR_HOME 0x01
#define LCD_CMD_CLEAR_SET_CSR 0x06
#define LCD_CMD_CLEAR_TURN_ON_DISP 0x0C
#define LCD_CMD_CLEAR_SCREEN 0x01
#define LCD_CMD_MOVE_CURSOR_LEFT 0x10
#define LCD_CMD_MOVE_CURSOR_RIGHT 0x14
#define LCD_CMD_MOVE_DISPLAY_LEFT 0x18
#define LCD_CMD_MOVE_DISPLAY_RIGHT 0x1C


void configure_lcd_pins(void);
void lcd_init(void);
void lcd_send_string(char* string);
void lcd_data(uint8_t data);
void lcd_cmd(uint8_t command);
void lcd_clear_screen(void);
void lcd_set_line(unsigned char line);

void lcd_disp_freq(int freq);
void printfcomma2 (int n);
void printnumberswiththousandsseparatorcomma(uint32_t n);
#endif /* LCD1602_H_ */