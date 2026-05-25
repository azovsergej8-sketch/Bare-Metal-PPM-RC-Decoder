#include <ChannelMapper.h>
#include <SignalFilter.h>
#include <PPM_Decoder.h>

class RC_Manager{
  private:
    //Собственный объект преобразования, фильтрации сигнала и непорсдетсвенно измерения
    ChannelMapper channelmapper;
    SignalFilter signalfilter;
    PPM_Decoder ppm_decoder;
    //Готовый массив
    volatile float result[8];
    //Время последнего обновления
    uint32_t last_time_update;
    //Флаг отсутствия данных
    bool long_update;
  public:
  uint32_t time;
  RC_Manager(uint32_t min_pwm[8],uint32_t center_pwm[8], uint32_t max_pwm[8]);
  void init();
  float get_ch_data(uint8_t i) const;
  void take_update();
  bool is_long_update() const;
}