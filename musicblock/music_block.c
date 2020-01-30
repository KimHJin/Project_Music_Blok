#include "music_block.h"




void bsp_evt_handler(bsp_event_t evt)
{
   ret_code_t err_code;
   
   switch(evt)
   {
      case START_PAUSE_EVENT:

      break;

      case STOP_EVENT:
        
      break;

      case LEFT_EVENT:
      
      break;

      case RIGHT_EVENT:
      
      break;

      case SAVE_RECORD_EVENT:

      break;

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
    }
}


void bsp_configuration(void)
{
    ret_code_t err_code;

    err_code = bsp_init(BSP_INIT_LEDS | BSP_INIT_BUTTONS, bsp_evt_handler);
    APP_ERROR_CHECK(err_code);
}


void button_init(void) 
{

    clock_initialization();

    ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    bsp_configuration();
}
