#ifndef __STM32F7_HELPER_H__
#define __STM32F7_HELPER_H__

#ifdef __cplusplus
extern "C" {
#endif 

struct dwtTime {
    uint32_t fcpu;
    int s;
    int ms;
    int us;
};

uint32_t disableInts(void);
void restoreInts(uint32_t state);

void dwtIpInit(void);
void dwtReset(void);
uint32_t dwtGetCycles(void);
uint32_t systemCoreClock(void);
float dwtCyclesToFloatMs(uint64_t clks);

const char *devIdToStr(uint16_t dev_id);
void logDeviceConf(void);

uint32_t systemCoreClock(void);

#ifdef __cplusplus
}
#endif

#endif // __STM32F7_HELPER_H__