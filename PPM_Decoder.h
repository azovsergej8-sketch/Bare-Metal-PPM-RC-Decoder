#include "stm32c0xx.h"
#include "stdint.h"
class PPM_Decoder{
  private:
    volatile uint32_t raw_timings[16];
    uint32_t channel_pulses[8];
    int data_ptr;
    bool new_data_ready;
  public:
    PPM_Decoder();
    void initialization() const;
    void process();
    uint32_t get_channel_pulses(uint8_t channel) const;
    bool is_new_data_ready() const;
    void switch_data_ready();
    uint32_t* get_buffer() const;
};