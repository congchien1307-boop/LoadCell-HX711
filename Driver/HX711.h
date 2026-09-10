#ifndef HX711_H
#define HX711_H
#include <stdint.h>
#include "STM32_reg.h"
typedef struct {
    int32_t offset;
    float   scale;
} HX711_Cal_t;

int8_t HX711_check(void);
int32_t HX711_read_data(uint8_t gain);
uint32_t HX711_tare(uint16_t samples);
void HX711_calibrate(HX711_Cal_t *cal, uint16_t samples, float known_weight);
float HX711_get_weight(HX711_Cal_t *cal, uint16_t samples);
void HX711_savetoflash(HX711_Cal_t *cal);
void HX711_Loadfromflash(HX711_Cal_t *cal);
#endif