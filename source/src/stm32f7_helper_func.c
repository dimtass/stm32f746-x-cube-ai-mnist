
#include <stdint.h>
#include <stdio.h>
#include "stm32f7xx_hal.h"
#include "cmsis_gcc.h"
#include "core_cm7.h"
#include "stm32f7_helper_func.h"

uint32_t disableInts(void)
{
    uint32_t state;

    state = __get_PRIMASK();
    __disable_irq();

    return state;
}

void restoreInts(uint32_t state)
{
   __set_PRIMASK(state);
}

void dwtIpInit(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

#ifdef STM32F7
    DWT->LAR = 0xC5ACCE55;
#endif

    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk | DWT_CTRL_CPIEVTENA_Msk;
}

void dwtReset(void)
{
    DWT->CYCCNT = 0; /* Clear DWT cycle counter */
}

uint32_t dwtGetCycles(void)
{
    return DWT->CYCCNT;
}

uint32_t systemCoreClock(void)
{
    return HAL_RCC_GetSysClockFreq();
}

int dwtCyclesToTime(uint64_t clks, struct dwtTime *t)
{
    if (!t)
        return -1;
    uint32_t fcpu = systemCoreClock();
    uint64_t s  = clks / fcpu;
    uint64_t ms = (clks * 1000) / fcpu;
    uint64_t us = (clks * 1000 * 1000) / fcpu;
    ms -= (s * 1000);
    us -= (ms * 1000 + s * 1000000);
    t->fcpu = fcpu;
    t->s = s;
    t->ms = ms;
    t->us = us;
    return 0;
}


float dwtCyclesToFloatMs(uint64_t clks)
{
    float res;
    float fcpu = (float)systemCoreClock();
    res = ((float)clks * (float)1000.0) / fcpu;
    return res;
}

const char *devIdToStr(uint16_t dev_id)
{
    const char *str;
    switch (dev_id) {
    case 0x422: str = "STM32F303xB/C"; break;
    case 0x438: str = "STM32F303x6/8"; break;
    case 0x446: str = "STM32F303xD/E"; break;
    case 0x431: str = "STM32F411xC/E"; break;
    case 0x435: str = "STM32L43xxx"; break;
    case 0x462: str = "STM32L45xxx"; break;
    case 0x415: str = "STM32L4x6xx"; break;
    case 0x470: str = "STM32L4Rxxx"; break;
    case 0x449: str = "STM32F74xxx"; break;
    case 0x450: str = "STM32H743/753 and STM32H750"; break;
    default:    str = "UNKNOWN";
    }
    return str;
}

#if !defined(STM32F3)
__STATIC_INLINE const char* bitToStr(uint32_t val)
{
    if (val)
        return "True";
    else
        return "False";
}
#endif

static uint32_t mconf;

uint32_t getFlashCacheConf(void)
{
    return mconf;
}

void logDeviceConf(void)
{
    uint32_t acr = FLASH->ACR ;
    uint32_t val;

    printf("STM32 Runtime configuration...\r\n");

    printf(" Device       : DevID:0x%08x (%s) RevID:0x%08x\r\n",
            (int)HAL_GetDEVID(),
            devIdToStr(HAL_GetDEVID()),
            (int)HAL_GetREVID()
    );

    printf(" Core Arch.   : M%d - %s %s\r\n",
            __CORTEX_M,
#if (__FPU_PRESENT == 1)
            "FPU PRESENT",
            __FPU_USED ? "and used" : "and not used!"
#else
            "!FPU NOT PRESENT",
            ""
#endif
    );

#if (__FPU_PRESENT == 1) && __FPU_USED
    mconf = (1 << 16);  /* FPU present and used */
#endif

    printf(" HAL version  : 0x%08x\r\n", (int)HAL_GetHalVersion());

    val = systemCoreClock()/1000000;

#if !defined(STM32H7)
    printf(" system clock : %u MHz\r\n", (int)val);
#else
    printf(" SYSCLK clock : %u MHz\r\n", (int)val);
    printf(" HCLK clock   : %u MHz\r\n", (int)HAL_RCC_GetHCLKFreq()/1000000);
#endif

#if defined(STM32F7) || defined(STM32H7)
    val = SCB->CCR;
#if !defined(STM32H7)
    mconf |= (2 << 24);  /* F7 conf. */
    mconf |= ((acr & FLASH_ACR_LATENCY_Msk) >> FLASH_ACR_LATENCY_Pos);
    if ((acr & FLASH_ACR_PRFTEN_Msk) >> FLASH_ACR_PRFTEN_Pos)
        mconf |= (1 << 8);
    if ((acr & FLASH_ACR_ARTEN_Msk) >> FLASH_ACR_ARTEN_Pos)
        mconf |= (1 << 9);
    printf(" FLASH conf.  : ACR=0x%08x - Prefetch=%s ART=%s latency=%d\r\n",
            (int)acr,
            bitToStr((acr & FLASH_ACR_PRFTEN_Msk) >> FLASH_ACR_PRFTEN_Pos),
            bitToStr((acr & FLASH_ACR_ARTEN_Msk) >> FLASH_ACR_ARTEN_Pos),
            (int)((acr & FLASH_ACR_LATENCY_Msk) >> FLASH_ACR_LATENCY_Pos));
#else
    mconf |= (3 << 24);  /* H7 conf. */
    mconf |= (acr & FLASH_ACR_LATENCY_Msk) >> FLASH_ACR_LATENCY_Pos;
    printf(" FLASH conf.  : ACR=0x%08x - latency=%d\r\n",
            (int)acr,
            (int)((acr & FLASH_ACR_LATENCY_Msk) >> FLASH_ACR_LATENCY_Pos));
#endif
    if (val & SCB_CCR_IC_Msk)
        mconf |= (1 << 10);
    if (val & SCB_CCR_DC_Msk)
        mconf |= (1 << 11);
    printf(" CACHE conf.  : $I/$D=(%s,%s)\r\n",
            bitToStr(val & SCB_CCR_IC_Msk),
            bitToStr(val & SCB_CCR_DC_Msk));
#else
#if !defined(STM32F3)
    mconf |= (1 << 24);  /* F4/L4 conf. */
    mconf |= ((acr & FLASH_ACR_LATENCY_Msk) >> FLASH_ACR_LATENCY_Pos);
    if ((acr & FLASH_ACR_PRFTEN_Msk) >> FLASH_ACR_PRFTEN_Pos)
        mconf |= (1 << 8);
    if ((acr & FLASH_ACR_ICEN_Msk) >> FLASH_ACR_ICEN_Pos)
        mconf |= (1 << 9);
    if ((acr & FLASH_ACR_DCEN_Msk) >> FLASH_ACR_DCEN_Pos)
        mconf |= (1 << 10);
    printf(" FLASH conf.  : ACR=0x%08x - Prefetch=%s $I/$D=(%s,%s) latency=%d\r\n",
            (int)acr,
            bitToStr((acr & FLASH_ACR_PRFTEN_Msk) >> FLASH_ACR_PRFTEN_Pos),
            bitToStr((acr & FLASH_ACR_ICEN_Msk) >> FLASH_ACR_ICEN_Pos),
            bitToStr((acr & FLASH_ACR_DCEN_Msk) >> FLASH_ACR_DCEN_Pos),
            (int)((acr & FLASH_ACR_LATENCY_Msk) >> FLASH_ACR_LATENCY_Pos));
#endif
#endif
}