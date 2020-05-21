#include <string.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "trik_studio_utils.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

U32 __interpretation_started_timestamp__ = 0;
static const float pi = 3.141592653589793;

static int x;

static U8 lcd[NXT_LCD_DEPTH * NXT_LCD_WIDTH];
static U8 lcd_copy[NXT_LCD_DEPTH * NXT_LCD_WIDTH];

EXTERNAL_BMP_DATA(Image_0);
EXTERNAL_BMP_DATA(Image_1);

void ecrobot_device_initialize(void)
{
	srand(systick_get_ms());
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
	ecrobot_init_nxtcolorsensor(NXT_PORT_S1, NXT_COLORSENSOR);
}

void ecrobot_device_terminate(void)
{
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
	ecrobot_term_nxtcolorsensor(NXT_PORT_S1);
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{ 
	ts_dispatch_timers();
	ecrobot_process_bg_nxtcolorsensor();
}

/* Main task */
TASK(TASK_MAIN)
{
	__interpretation_started_timestamp__ = systick_get_ms();
	
	label_ee51ec91734f7ea6816aaa1f74e589:
	nxt_motor_set_speed(NXT_PORT_B, 100, 0);
	nxt_motor_set_speed(NXT_PORT_C, 100, 0);
	
	label_bfff3deda0fe4eaea95d47de9767f3c1:
	x = ecrobot_get_nxtcolorsensor_id(NXT_PORT_S1);
	label_f54385929d4f30b298d7ada697b0d2:
	if (x == 2) {
		goto label_cf4166b31b7d6a701773fd;
	} else if (x == 1) {
		goto label_b3826fdd116f4974bb20e029d67ba2ac;
	} else {
		goto label_a5eb58fe09c443a4b34046036b198665;
	}
	
	label_b3826fdd116f4974bb20e029d67ba2ac:
	while (ecrobot_get_nxtcolorsensor_id(NXT_PORT_S1) != NXT_COLOR_GREEN) {
		wait(4);
	}
	label_e8c6563d7744445909682b23d8df5f5:
	wait(1000);
	
	label_e1465299e14c3a8b650dcd70cc6db0:
	for (int _counter = 0; _counter < sizeof(lcd); ++_counter) {
		lcd_copy[_counter] = lcd[_counter];
	}
	ecrobot_bmp2lcd(BMP_DATA_START(Image_0), lcd, 100, 64);
	for (int _counter = 0; _counter < sizeof(lcd); ++_counter) {
		lcd[_counter] |= lcd_copy[_counter];
	}
	display_bitmap_copy(lcd, 100, 8, 0, 0);
	display_update();
	label_b79a3574009472fa7e95b1eb13faf32:
	
	label_f4a4b7c57d114abe9292b1d9c9fe4d5f:
	while (!(nxt_motor_get_count(B, C) > 150)) {
		wait(3);
	}
	label_c6b900ffd4722bf38e455d9c3564d:
	ecrobot_sound_tone(1000, 100, 50);
	
	label_f4e004c9336c4a159b4ef20b1d4b5c50:
	wait(1000);
	
	goto label_a5eb58fe09c443a4b34046036b198665;
	label_cf4166b31b7d6a701773fd:
	while (ecrobot_get_nxtcolorsensor_id(NXT_PORT_S1) != NXT_COLOR_YELLOW) {
		wait(4);
	}
	label_b243f4a2c40eb81e9ff4b36bc772e:
	wait(1000);
	
	label_d3705fcf65ac4e8ca5fa3e6015cc448e:
	for (int _counter = 0; _counter < sizeof(lcd); ++_counter) {
		lcd_copy[_counter] = lcd[_counter];
	}
	ecrobot_bmp2lcd(BMP_DATA_START(Image_1), lcd, 100, 64);
	for (int _counter = 0; _counter < sizeof(lcd); ++_counter) {
		lcd[_counter] |= lcd_copy[_counter];
	}
	display_bitmap_copy(lcd, 100, 8, 0, 0);
	display_update();
	goto label_b79a3574009472fa7e95b1eb13faf32;
	label_a5eb58fe09c443a4b34046036b198665:
	x = ecrobot_get_nxtcolorsensor_id(NXT_PORT_S1);
	goto label_dbadeaa0947b9b7f17fee35fee7d9;
	label_dbadeaa0947b9b7f17fee35fee7d9:
	if (x > 0) {
		goto label_dbe540d1de634215ac96302076a19ced;
	} else {
		goto label_b16867c67f0c46c58e8f413f738517c8;
	}
	label_dbe540d1de634215ac96302076a19ced:
	while (ecrobot_get_nxtcolorsensor_id(NXT_PORT_S1) != NXT_COLOR_BLACK) {
		wait(4);
	}
	label_e60c04e7f9f771a44b765c5f1:
	nxt_motor_set_speed(NXT_PORT_A, 0, 1);
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);
	
	label_d51718a87c048d5813be0fc0ed982fb:
	wait(500);
	
	label_fa6a001aa1f011b77c5:
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	
	label_eb658d07490440829ec758aa32c6d302:
	nxt_motor_set_speed(NXT_PORT_B, 50, 1);
	
	label_e38b27f4d608516b0f9677c53aa:
	nxt_motor_set_speed(NXT_PORT_C, 100, 0);
	
	label_f829320ea8ba49ada2c380990c993451:
	wait(4000);
	
	goto label_a2502f59bdb54a749e8d8d8a7af43265;
	label_b16867c67f0c46c58e8f413f738517c8:
	ecrobot_sound_tone(1000, 100, 50);
	
	label_fe0dc044c941eea3c17ea6c5c3930b:
	while (!(nxt_motor_get_count(NXT_PORT_B) > 100)) {
		wait(3);
	}
	label_ccbc85c177f43ef9d0c205fd51eac37:
	nxt_motor_set_count(NXT_PORT_B, 0);
	
	label_a2502f59bdb54a749e8d8d8a7af43265:
	
	goto label_ee51ec91734f7ea6816aaa1f74e589;
}
