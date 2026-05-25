#include "stm32c0xx.h"
#include "stdint.h"
class SignalFilter{
  private:
    volatile int buffer[8];
  public:
    void filter(uint32_t* buf);
    uint32_t* get_buffer() const;
};