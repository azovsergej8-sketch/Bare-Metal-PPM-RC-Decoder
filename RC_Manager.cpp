#include <RC_Manager.h>
#icnlude "Time.h"
//1. Конструктор
RC_Manager::RC_Manager(uint32_t min_pwm[8],uint32_t center_pwm[8], uint32_t max_pwm[8]): channelmapper(min_pwm[8], center_pwm[8], max_pwm[8]), signalfilter(), ppm_decoder() {
  last_time_update = 0;
}

//2. Функция инициализации
void RC_Manager::init(){
  ppm_decoder.initialization();
}

//3. Получение значения для конкретного параметра
float RC_Manager::get_ch_data(uint8_t i) const{
  return result[i];
}

//4. Обновление данных
void RC_Manager::take_update(){
  if(ppm_decoder.is_new_data_ready()){
    long_update = false;
    last_time_update = get_system_ms();
    ppm_decoder.process();
    signalfilter.filter(ppm_decoder.get_buffer())
    channelmapper.transform(signalfilter.get_buffer(), result);
  }
  else{
    if(get_system_ms() - last_time_update > 500){
      long_update = true;
      for(int i = 0; i < 8; i++) result[i] = 0.0f;
    }
  }
}

//5. Получение состояния флага
bool RC_Manager::is_long_update() const{
  return long_update;
}