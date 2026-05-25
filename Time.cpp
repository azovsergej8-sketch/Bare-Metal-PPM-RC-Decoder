#include "system_time.h"
volatile uint32_t system_ticks = 0;

extern "C" void SysTick_Handler() {
    system_ticks++;
}

uint32_t get_system_ms() {
    return system_ticks;
}

void System_Time_Init(void) {
    uint32_t ticks = SystemCoreClock / 1000;
    SysTick->LOAD  = (uint32_t)(ticks - 1UL);
    NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
    SysTick->VAL   = 0UL;
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}