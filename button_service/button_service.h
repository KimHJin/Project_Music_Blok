
#ifndef BUTTON_SERVICE_H
#define BUTTON_SERVICE_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "boards.h"
#include "bsp.h"
#include "app_timer.h"
#include "nordic_common.h"
#include "nrf_error.h"
#include "nrf_delay.h"
#include "bsp_btn_ble.h"
#include "nrf_soc.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define START_PAUSE_EVENT BSP_EVENT_KEY_2
#define STOP_EVENT        BSP_EVENT_KEY_3
#define LEFT_EVENT        BSP_EVENT_KEY_0
#define RIGHT_EVENT       BSP_EVENT_KEY_1
#define SAVE_RECORD_EVENT BSP_EVENT_KEY_4

#define HIGH 1
#define LOW  0
 
#define PLAY   0
#define PAUSE  1 
#define STOP   2
#define SAVE   3
#define CHORD  4
#define RECORD 5
#define IDLE   6

void bsp_evt_handler(bsp_event_t evt);
void clock_initialization(void);
void bsp_configuration(bool * p_erase_bonds);
void button_init(bool * p_erase_bonds);
void sleep_mode_enter(void);

bool read_play_flag(void);
bool read_pause_flag(void);
bool read_stop_flag(void);
void set_state(int state);


#endif