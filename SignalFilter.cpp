#include <SignalFilter.h>
//Заполнение внутреннего буфера
void SignalFilter::filter(uint32_t* buf){
  int result;
  float alpha_coef;
  for(int i = 0; i < 8; i++){
    if(i > 0 && i < 4) alpha_coef = 0.2f;
    else if(i == 0) alpha_coef = 0.1f;
    else alpha_coef = 0.4f;
    result = buf[i]*alpha_coef + ((1 - alpha_coef)*buffer[i]);
    if(((buf[i] - buffer[i]) > 3) || ((buf[i] - result) > 3)) buffer[i] = result;
  }
}
uint32_t* SignalFilter::get_buffer() const{
  return buffer;
}