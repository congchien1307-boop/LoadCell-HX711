#ifndef HX711_H
#define HX711_H

typedef struct {
    int32_t offset;
    float   scale;
} HX711_Cal_t;

int8_t HX711_check(void);
int32_t HX711_read_data(uint8_t gain);
#endif