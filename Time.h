#pragma once
#include <stdint.h>
#include "stm32c0xx.h"
void System_Time_Init(void);
uint32_t get_system_ms(void);