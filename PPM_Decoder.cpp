#include <PPM_Decoder.h>
//Конструктор
PPM_Decoder::PPM_Decoder() : channel_pulses(nullptr), data_ptr(0), new_data_ready(0) {}

//Инициализация
void PPM_Decoder::initialization() const{
  //1. Тактирование
  RCC->IOPENR = (1 << IOPAEN); //Тактирование порта ввода/вывода
  RCC->APBENR2 = (1 << TIM1EN); //Тактирование Таймера 1
  RCC->AHBENR = (1 << DMAEN); //Тактирование DMA

  //2. Настройка пина PA8
  GPIOA->MODER = (1 << 17); //Сигнал идет непосредственно на канал таймера
  GPIOA->AFRH = (1 << 1); //Выбор канала и таймера

  //3. Настройка таймера
  TIM1->PSC = 47; //Предделитель
  TIM1->ARR = 65535; //Максимальное значение счета
  TIM1->CR1 = (1 << CEN) | (1 << UDIS); //Включение счетчика и запрет на обновление
  TIM1->CCMR1 = (1 << CC1S0); //Режим захвата канала 1
  TIM1->CCER = (1 << CC1E) | (1 << CC1P) | (1 << CC1NP); //Разрешение захвата по обоим фронтам
  TIM1->DIER = (1 << CC1DE); //Запрос DMA при событии захвата/сравнения канала 1

  //4. Настройка DMA
  DMA->CCR = (1 << EN) | (1 << CIRC) | (1 << MINC) | (1 << PSIZE0) | (1 << MSIZE1);
  DMA->CPAR = 0x40012C34; //Адрес TIM1_CCR1
  DMA->CMAR = (uint32_t)&this->raw_timings; //Адорес памяти
  DMA->CNDTR = 16; //Количество передач
}

bool PPM_Decoder::is_new_data_ready() const{
  return this->new_data_ready;
}


//Работа
void PPM_Decoder::process(){
  int i;
  if(raw_timings[1] - raw_timings[0] < 2500) i = 1;
  else i = 0;
  //Поиск синхро-паузы
  for( ; i < 14; i+=2){
    if((raw_timings[i+1] - raw_timings[i]) > 2500) break;
  }
  if(i >= 14){
    data_ptr = 0;
    i = -1;
  }
  //Заполнение получившимися импульсами
  for(j = i + 1; j < 16; j+=2){
    channel_pulses[data_ptr] = raw_timings[j+1] - raw_timings[j];
    if(data_ptr < 7 ) data_ptr++;
    else data_ptr = 0;
  }
  //Поднятие флага
  new_data_ready = true;
}

//Сброс флага - данные прочитаны
void PPM_Decoder::switch_data_ready(){
  new_data_ready = false;
}
//Получение буфера
uint32_t* PPM_Decoder::get_buffer() const{
  return channel_pulses;
}