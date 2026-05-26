#include <ChannelMapper.h>

//Конструктор
ChannelMapper::ChannelMapper(uint32_t mn_pwm[8], uint32_t cr_pwm[8], uint32_t mx_pwm[8]): min_pwm(mn_pwm), center_pwm(cr_pwm), max_pwm[mx_pwm]{}

//Преобрахование
void ChannelMapper::transform(uint32_t* buf_in, float* buf_out){

  //1. Обработка канала газа
  int32_t total_range = max_pwm[0] - min_pwm[0];
  if(total_range > 0){
    buf_out[0] = (((int32_t)buf_in[0] - min_pwm[0]) / (float)total_range);
    if(buf_out[0] > 1.0f) buf_out[0] = 1.0f;
    else if(buf_out[0] < 0.0f) buf_out[0] = 0.0f;
  }
  else buf_out[0] = 0.0f;
  int32_t deviation;
  int32_t half_range;
  
  //Обработка остальных каналов
  for(int i = 1; i < 8; i++){
     deviation = buf_in[i] - center_pwm[i];
     if(deviation > 0) half_range = max_pwm[i] - center_pwm[i];
     else half_range = center_pwm[i] - min_pwm[i];
     if(half_range > 0){
      buf_out[i] = deviation / (float)half_range;
      if (buf_out[i] > 1.0f)  buf_out[i] = 1.0f;
      if (buf_out[i] < -1.0f) buf_out[i] = -1.0f;
     }
     else{
      buf_out[i] = 0.0f
     }
  }
}
