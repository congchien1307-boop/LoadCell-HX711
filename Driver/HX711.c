#include "HX711.h"
#include "STM32_reg.h"
#include "stdint.h"
#define GAIN_128 25
#define GAIN_64 27
#define GAIN_32 26
int8_t HX711_check(void){
    return (HX711_DT_read()==0);
}
int32_t HX711_read_data(uint8_t gain)
{
    int32_t data = 0;
    while (!HX711_check());
    for (int i = 0; i < 24; i++){
        HX711_SCK_HIGH();
        Delay_us(1);
        data = (data << 1) | HX711_DT_Read();
        HX711_SCK_LOW();
        Delay_us(1);
    }
    for (int i = 0; i < gain; i++){
        HX711_SCK_HIGH();
        Delay_us(1);
        HX711_SCK_LOW();
        Delay_us(1);
    }
    if (data & 0x800000){
        data |= 0xFF000000; 
    }
    return (uint32_t)data;
}

