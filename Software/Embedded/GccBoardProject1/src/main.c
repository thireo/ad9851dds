/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "lcd1602.h"
#include "ad9851.h"

int main (void)
{
	system_init();
	delay_init();
	
	ad9851_init();
		
	int counter = 54000000;
	int step = 1;
	char buffer[32];
	delay_ms(20);
	
	lcd_init();
	
	//Goto Line-1,first position
	lcd_cmd(0x80);
	lcd_send_string("HELLO");
	//Goto Line-2, first position
	lcd_cmd(0xC0);
	lcd_send_string("world   0x2A");
	
	
	step = 100000;


	while (1)
	{
		delay_ms(250);
		//lcd_clear_screen();
		
		
		//sprintf(buffer,"%12.2d",counter);
		//lcd_send_string(buffer);
		
		/*lcd_disp_freq(counter);
		lcd_cmd(0x8E);
		lcd_send_string("Hz");*/

		
		/*lcd_set_line(2);
		sprintf(buffer,"0x2A = %d",step);
		lcd_send_string(buffer);*/
		step = step * (-1);//step + 25;
		counter = counter + step;
		send_word(calc_word((double)counter));
		//send_word((uint32_t)357914);
		//send_word(16000000);
		 
	}
	
	
	/* Insert application code here, after the board has been initialized. */
}
