#include "RC_Manager.h"

int main(){
  const uint32_t low_calib[8]    = {1000, 1004, 996,  1002, 1000, 1000, 1000, 1000};
  const uint32_t center_calib[8] = {1500, 1502, 1498, 1500, 1500, 1500, 1500, 1500};
  const uint32_t max_calib[8]    = {2000, 1996, 2004, 1998, 2000, 2000, 2000, 2000};
  RC_Manager rc_manager(low_calib, center_calib, max_calib);
  SystemInit();        // Настройка частоты процессора
  System_Time_Init();  // Запуск SysTick ядра ARM
  rc_manager.init();
  while(1){
    rc_manager.take_update(); 
    if(rc_manager.is_long_update()) {
      // Авария — связи нет
    } 
    else {
      float throttle = rc_manager.get_ch_data(0);
      float roll     = rc_manager.get_ch_data(1);
      // Передаем float в PID-регулятор
    }
  }
}