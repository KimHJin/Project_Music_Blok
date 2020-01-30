#include "boards.h"
#include "bsp.h"
#include "app_timer.h"
#include "nordic_common.h"
#include "nrf_error.h"
#include "nrf_delay.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


#define START_PAUSE_EVENT BSP_EVENT_KEY_0
#define STOP_EVENT        BSP_EVENT_KEY_1
#define LEFT_EVENT        BSP_EVENT_KEY_2
#define RIGHT_EVENT       BSP_EVENT_KEY_3
#define SAVE_RECORD_EVENT BSP_EVENT_KEY_4


void bsp_evt_handler(bsp_event_t evt);
void clock_initialization(void);
void bsp_configuration(void);
void button_init(void);



