#include "HX711.h"
#include "STM32_reg.h"
#include "GPIO.h"
#include "SysTick.h"
#define GAIN_128 25
#define GAIN_64 27
#define GAIN_32 26
// check if HX711 is ready for data retrieval
int8_t HX711_check(void){
    return (HX711_DT_Read()==0);
}
// read 24-bit data from HX711
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
    if (data & 0x800000){        // if the sign bit is set, extend the sign to 32 bits
        data |= 0xFF000000; 
    }
    return (uint32_t)data;
}

// calculate the offset value by averaging multiple samples
uint32_t HX711_tare(uint16_t samples){
    uint64_t sum = 0;
    for (int i = 0; i < samples; i++){
        sum += HX711_read_data(GAIN_128);
    }
    return (uint32_t)(sum / samples);
}

// calibrate the scale with known weight
void HX711_calibrate(HX711_Cal_t *cal, uint16_t samples, float known_weight){
    uint64_t sum = 0;
    cal->offset = HX711_tare(samples);
    for (int i = 0; i < samples; i++){
        sum += HX711_read_data(GAIN_128);
    }
    uint32_t avg = (uint32_t)(sum / samples);
    cal->scale = (float)(avg - cal->offset) / known_weight;
}

// get weight in grams
float HX711_get_weight(HX711_Cal_t *cal, uint16_t samples){
    uint64_t sum = 0;
    for (int i = 0; i < samples; i++){
        sum += HX711_read_data(GAIN_128);
    }
    uint32_t avg = (uint32_t)(sum / samples);
    return (float)(avg - cal->offset) / cal->scale;
}
