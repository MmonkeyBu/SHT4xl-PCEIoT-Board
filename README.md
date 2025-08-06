# Biblioteca SHT4x para Raspberry Pi Pico W (C/C++)

Esta é uma biblioteca modularizada em C desenvolvida para facilitar o uso da família de sensores de temperatura e umidade **SHT4x (SHT40, SHT41, SHT45)** com o **Raspberry Pi Pico W**. A biblioteca abstrai a comunicação I2C e fornece uma interface simples e eficiente para o usuário configurar os pinos desejados e começar a utilizar o sensor com poucas linhas de código.

---

## 📦 Estrutura do Projeto

```
📁 sht4x/
├── sht4x.h
├── sht4x.c
├── sht4x_def.h
├── sht4x_commands.h
└── README.md
```

---

## 🚀 Como Usar

### 1. **Clone o repositório e inclua os arquivos no seu projeto**
Coloque os arquivos `sht4x.c`, `sht4x.h`, `sht4x_def.h` e `sht4x_commands.h` no seu projeto.

### 2. **Inclua a biblioteca no seu `CMakeLists.txt`**

```cmake
add_executable(seu_programa
    main.c
    sht4x.c
)

target_include_directories(seu_programa PRIVATE .)
```

### 3. **Configure os pinos I2C na sua `main.c`**

```c
#include "sht4x.h"

int main() {
    stdio_init_all();

    sht4x_t sensor = sht4x_create(i2c0, 4, 5); // SDA = GP4, SCL = GP5
    sht4x_init(&sensor);

    while (1) {
        sht4x_measure_blocking_read(&sensor);
        printf("Temperatura: %.2f °C | Umidade: %.2f %%
", sensor.temperature, sensor.humidity);
        sleep_ms(1000);
    }
}
```

---

## 🔧 Principais Funções

| Função                            | Descrição |
|----------------------------------|-----------|
| `sht4x_t sht4x_create(...)`      | Cria e inicializa a estrutura do sensor com os pinos I2C desejados. |
| `bool sht4x_init(...)`           | Envia o comando de soft reset e verifica a conexão com o sensor. |
| `bool sht4x_measure_blocking_read(...)` | Realiza uma medição de temperatura e umidade. |
| `float sht4x_calc_temperature(...)` | Converte os dados brutos em temperatura. |
| `float sht4x_calc_humidity(...)` | Converte os dados brutos em umidade relativa. |

---

## 📌 Definições Importantes

O arquivo `sht4x_def.h` contém:
- Definições de status do sensor (`SHT4X_OK`, `SHT4X_ERR`)
- Estrutura `sht4x_t`
- Enum `sht4x_cmd_t` com os principais comandos de medição

O arquivo `sht4x_commands.h` contém:
- Constantes com os valores hexadecimais dos comandos suportados pelo sensor

---

## 🧪 Testado com:

- Raspberry Pi Pico W
- Sensor SHT45 via I2C
- SDK Pico C/C++ (versão 1.5.1)
- VSCode + CMake

---

## 🛠️ A Fazer

- Suporte a medições com heater ativado
- Suporte a múltiplos sensores no mesmo barramento
- Implementar leitura de status do sensor

---

## 🤝 Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir _issues_ ou enviar _pull requests_.

---

## 📄 Licença

Este projeto está sob a licença MIT.