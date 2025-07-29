#ifndef SHT4XL_PCEIOT_BOARD_H
#define SHT4XL_PCEIOT_BOARD_H

#include <stdio.h>
#include <stdbool.h>

#define SHT4XL_I2C_ADDRESS 0x44 // Endereço I2c indicado no datasheet do sensor

//Nivel da precisão 
typedef enum {
    SHT4X_HIGH_PRECISION,
    SHT4X_MEDIUM_PRECISION,
    SHT4X_LOW_PRECISION
} SHT4x_Precision;

bool sht4xl_init(void);
bool sht4xl_Ler_TempHum(float *temperature, float *humidity);
bool sht4xl_reset(void);
bool sht4xl_Aquecer(void);
#endif
