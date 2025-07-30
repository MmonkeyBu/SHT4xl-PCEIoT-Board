#ifndef SHT4X_PCEIOT_BOARD_H
#define SHT4X_PCEIOT_BOARD_H

#include <stdbool.h>

// Endereço I2C padrão do SHT4x
#define SHT4X_I2C_ADDRESS 0x44

// Enumeração para os níveis de precisão da medição
typedef enum {
    PRECISION_HIGH,
    PRECISION_MEDIUM,
    PRECISION_LOW
} SHT4x_Precision;

// Enumeração para os modos de aquecimento
typedef enum {
    HEATER_HIGH_1S,
    HEATER_HIGH_0_1S,
    HEATER_MEDIUM_1S,
    HEATER_MEDIUM_0_1S,
    HEATER_LOW_1S,
    HEATER_LOW_0_1S
} SHT4x_HeaterMode;


//Inicializa a comunicação I2C e reseta o sensor
bool sht4x_init(void);
 //Envia um comando de soft-reset para o sensor
bool sht4x_reset(void);
 //Le temperatura e umidade com um nível de precisao 
bool sht4x_read_temp_hum(SHT4x_Precision precision, float *temperature, float *humidity);
//Le temperatura e umidade utilizando um modo de aquecedor
bool sht4x_read_with_heater(SHT4x_HeaterMode mode, float *temperature, float *humidity);

#endif // SHT4X_PCEIOT_BOARD_H
