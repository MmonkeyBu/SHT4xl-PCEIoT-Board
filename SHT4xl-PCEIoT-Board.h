#ifndef SHT4XL_PCEIOT_BOARD_H
#define SHT4XL_PCEIOT_BOARD_H

#include <stdio.h>
#include <stdbool.h>

#define SHT4XL_I2C_ADRESS 0x44 // Endereço I2c indicado no datasheet do sensor

bool sht4xl_init(void);
bool sht4xl_Ler_TempHum(float *temperature, float *humidity);
bool sht4xl_reset(void);
bool sht4xl_Aquecer(void);
#endif
