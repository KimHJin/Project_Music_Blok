#include "button_service.h"


bool Play_flag  = false;
bool Pause_flag = false;
bool Stop_flag  = false;


bool read_play_flag(void)
{
  return Play_flag; 
}
bool read_pause_flag(void)
{
  return Pause_flag;
}
bool read_stop_flag(void)
{
  return Stop_flag; 
}


void set_state(int state)
{
    switch(state)
    {
      case PLAY  : Play_flag   = true;  Pause_flag = false; Stop_flag  = false; break;
      case PAUSE : Pause_flag  = true;  Play_flag  = false; Stop_flag  = false; break;
      case STOP  : Stop_flag   = true;  Play_flag  = false; Pause_flag = false; break;
      case IDLE  : Play_flag   = false; Pause_flag = false; Stop_flag  = false; break;
    }
}


/**@brief Function for putting the chip into sleep mode.
 *
 * @note This function will not return.
 */
void sleep_mode_enter(void)
{
    ret_code_t err_code;

    err_code = bsp_indication_set(BSP_INDICATE_IDLE);
    APP_ERROR_CHECK(err_code);

    // Prepare wakeup buttons.
    err_code = bsp_btn_ble_sleep_mode_prepare();
    APP_ERROR_CHECK(err_code);

    // Go to system-off mode (this function will not return; wakeup will cause a reset).
    err_code = sd_power_system_off();
    APP_ERROR_CHECK(err_code);
}



void bsp_evt_handler(bsp_event_t evt)
{
   ret_code_t err_code;
   
   switch(evt)
   {
      case START_PAUSE_EVENT:
            NRF_LOG_INFO("START_PAUSE_EVENT");

            if(!read_play_flag()) set_state(PLAY);
            else                  set_state(PAUSE);

            break; // START_PAUSE_EVENT

      case STOP_EVENT:
            NRF_LOG_INFO("STOP_EVENT");

            set_state(STOP);

            break; // STOP_EVENT

      case LEFT_EVENT:
           // NRF_LOG_INFO("LEFT_EVENT");
            break; // LEFT_EVENT

      case RIGHT_EVENT:
           // NRF_LOG_INFO("RIGHT_EVENT");
            break; // RIGHT_EVENT

      case SAVE_RECORD_EVENT:
           // NRF_LOG_INFO("SAVE_RECORD_EVENT");
            break; // SAVE_RECORD_EVENT

//      case BSP_EVENT_SLEEP:
//            sleep_mode_enter();
//            break; // BSP_EVENT_SLEEP
   }

}


void clock_initialization(void)
{
    NRF_CLOCK->LFCLKSRC            = (CLOCK_LFCLKSRC_SRC_Xtal << CLOCK_LFCLKSRC_SRC_Pos);
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_LFCLKSTART    = 1;

    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0)
    {
        // Do nothing.
        NRF_LOG_INFO("LOOP");
    }
}


void bsp_configuration(bool * p_erase_bonds)
{
    ret_code_t err_code;
    bsp_event_t startup_event;

    err_code = bsp_init(BSP_INIT_LEDS | BSP_INIT_BUTTONS, bsp_evt_handler);
    APP_ERROR_CHECK(err_code);

    err_code = bsp_btn_ble_init(NULL, &startup_event);
    APP_ERROR_CHECK(err_code);

    *p_erase_bonds = (startup_event == BSP_EVENT_CLEAR_BONDING_DATA);
}


void button_init(bool * p_erase_bonds) 
{

    clock_initialization();
  
    //ret_code_t err_code = app_timer_init();
    //APP_ERROR_CHECK(err_code);

    bsp_configuration(p_erase_bonds);
}
