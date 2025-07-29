#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "SHT4xl-PCEIoT-Board.h"

// I2C defines
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

// Comandos
#define CMD_MEASURE_HIGH_PREC  0xFD
#define CMD_RESET         0x94 //Para reset do sensor

// Delay pos medição (datasheet)
#define MEASURE_DELAY_MS 10

//Para o crc8
static uint8_t sht4x_crc8(const uint8_t *data, size_t len) {
    uint8_t crc = 0xFF;
    for (size_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            crc = (crc & 0x80) ? (crc << 1) ^ 0x31 : (crc << 1);
        }
    }
    return crc;
}


bool sht4x_init(void) {
    i2c_init(I2C_PORT, 100 * 1000); // 100kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    return sht4xl_reset();
}

//para resetar 
bool sht4x_reset(void) {
    uint8_t cmd = CMD_RESET;
    return i2c_write_blocking(I2C_PORT, SHT4XL_I2C_ADDRESS, &cmd, 1, false) == 1;
}

// Ler temperatura e umidade
bool sht4xl_Ler_TempHum(SHT4x_Precision precision, float *temperature, float *humidity) {
    uint8_t cmd;
    uint16_t delay_ms;

    // Seleciona o comando e o delay com base na precisão escolhida
    switch (precision) {
        case PRECISION_HIGH:
            cmd = CMD_MEASURE_HIGH_PREC;
            delay_ms = DELAY_HIGH_PREC_MS;
            break;
        case PRECISION_MEDIUM:
            cmd = CMD_MEASURE_MEDIUM_PREC;
            delay_ms = DELAY_MEDIUM_PREC_MS;
            break;
        case PRECISION_LOW:
            cmd = CMD_MEASURE_LOW_PREC;
            delay_ms = DELAY_LOW_PREC_MS;
            break;
        default:
            return false; // Caso um valor inválido seja passado
    }

    uint8_t rx[6];

    // Envia comando
    if (i2c_write_blocking(I2C_PORT, SHT4XL_I2C_ADDRESS, &cmd, 1, false) != 1)
        return false;

    sleep_ms(delay_ms);

    // Lê 6 bytes: 2 temp + CRC, 2 humi + CRC
    if (i2c_read_blocking(I2C_PORT, SHT4XL_I2C_ADDRESS, rx, 6, false) != 6)
        return false;

    // Verifica CRC dos dois blocos
    if (sht4x_crc8(rx, 2) != rx[2] || sht4x_crc8(rx + 3, 2) != rx[5])
        return false;

    // Converte para float (datasheet)
    uint16_t raw_temp = (rx[0] << 8) | rx[1];
    uint16_t raw_humi = (rx[3] << 8) | rx[4];

    //conta no data sheet
    *temperature = -45.0f + 175.0f * ((float)raw_temp / 65535.0f);
    *humidity    = -6.0f + 125.0f * ((float)raw_humi / 65535.0f);

    // Garante que os valores de humidade fiquem entre 0 e 100
    if (*humidity > 100.0f) *humidity = 100.0f;
    if (*humidity < 0.0f) *humidity = 0.0f;

    return true;
}
