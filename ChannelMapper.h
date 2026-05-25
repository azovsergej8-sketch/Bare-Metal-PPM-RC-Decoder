#include "stm32c0xx.h"
#include "stdint.h"
class ChannelMapper{
  private:
    uint32_t min_pwm[8];
    uint32_t center_pwm[8];
    uint32_t max_pwm[8];
  public:
    ChannelMapper(uint32_t mn_pwm[8], uint32_t cr_pwm[8], uint32_t mx_pwm[8]);
    void transform(uint32_t* buf_in, float* buf_out);
}