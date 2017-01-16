/*
 * ad9851.c
 *
 * Created: 27-12-2016 23:21:08
 *  Author: Andreas
 */ 
#include "ad9851.h"
#include "lcd1602.h"

unsigned int calc_word(double frequency)
{
	unsigned int temp = (unsigned int) frequency*CLOCK_WORD_RATIO;
	return (unsigned int) temp;
}

void ad9851_init(void)
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(DDS_D0, &config_port_pin);
	port_pin_set_config(DDS_D1, &config_port_pin);
	port_pin_set_config(DDS_D2, &config_port_pin);
	port_pin_set_config(DDS_D3, &config_port_pin);
	port_pin_set_config(DDS_D4, &config_port_pin);
	port_pin_set_config(DDS_D5, &config_port_pin);
	port_pin_set_config(DDS_D6, &config_port_pin);
	port_pin_set_config(DDS_D7, &config_port_pin);
	
	port_pin_set_config(DDS_F_UP, &config_port_pin);
	port_pin_set_config(DDS_W_CLK, &config_port_pin);
	port_pin_set_config(DDS_RESET, &config_port_pin);
}

void put_data_byte(uint8_t data_byte)
{
	port_pin_set_output_level(DDS_D0,((data_byte >> 0)  & 0x01));
	port_pin_set_output_level(DDS_D1,((data_byte >> 1)  & 0x01));
	port_pin_set_output_level(DDS_D2,((data_byte >> 2)  & 0x01));
	port_pin_set_output_level(DDS_D3,((data_byte >> 3)  & 0x01));
	port_pin_set_output_level(DDS_D4,((data_byte >> 4)  & 0x01));
	port_pin_set_output_level(DDS_D5,((data_byte >> 5)  & 0x01));
	port_pin_set_output_level(DDS_D6,((data_byte >> 6)  & 0x01));
	port_pin_set_output_level(DDS_D7,((data_byte >> 7)  & 0x01));

	port_pin_set_output_level(DDS_W_CLK,1);
	delay_us(1);
	port_pin_set_output_level(DDS_W_CLK,0);
}

void send_word(uint32_t word)
{
	//char buffer[32];
	//
	//lcd_set_line(2);
	//sprintf(buffer,"0x2A = %d",word);
	//lcd_send_string(buffer);
	//delay_ms(1000);
	//lcd_set_line(2);
	//lcd_send_string("                ");
	//lcd_set_line(2);
	put_data_byte(0x01);

	/*for (int w=0;w<4;w++)
	{
		put_word((word >> (8*(w))) & 0x0F);
		sprintf(buffer,"%02X",(word >> (8*(w))) & 0xFF);
		lcd_send_string(buffer);
		delay_ms(500);
	}*/
	
	put_data_byte((word >> 24) & 0xFF);
	put_data_byte((word >> 16) & 0xFF);
	put_data_byte((word >> 8) & 0xFF);
	put_data_byte((word >> 0) & 0xFF);
	
	
	port_pin_set_output_level(DDS_F_UP,1);
	delay_us(1);
	port_pin_set_output_level(DDS_F_UP,0);
}