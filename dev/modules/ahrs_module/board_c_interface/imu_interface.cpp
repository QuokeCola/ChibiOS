//
// Created by Quoke on 3/6/2025.
//

#include "imu_interface.h"

static const SPIConfig SPI_cfg = {
    false,
    false,
    nullptr,
    nullptr,
    BMI088_SPI_CS_PAD,
    BMI088_SPI_CS_ACCEL_PIN,
    SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_MSTR |
    SPI_CR1_CPHA | SPI_CR1_CPOL, //Set CPHA and CPOL to be 1
    0
};
