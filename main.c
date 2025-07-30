#include <stdio.h>
#include "pico/stdlib.h"
#include "SHT4xl-PCEIoT-Board.h" 


//Setagem de pinos

#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

int main() {

    stdio_init_all();
    sleep_ms(2000); 

    if (!sht4x_init()) {
        printf("Falha ao iniciar o sensor SHT4x. Verifique as conexoes.\n");
    }

    printf("Sensor SHT4x pronto. Iniciando medicoes...\n");

    float temperatura, umidade;
    while (1) {

        if (sht4x_read_temp_hum(PRECISION_MEDIUM, &temperatura, &umidade)) {
            printf("Temperatura: %.2f C, Umidade: %.2f %%RH\n", temperatura, umidade);
        } else {
            printf("Erro na leitura do sensor.\n");
        }

        sleep_ms(2000);
    }

    return 0;
}
