//
// Created by Quoke on 2/25/2025.
//

#include "imu_interface.h"

static const SPIConfig SPI_cfg =
#if defined(BOARD_RM_2018A)
        {
                false,
                false,
                nullptr,
                nullptr,
                MPU6500_SPI_CS_PAD,
                MPU6500_SPI_CS_PIN,
                SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_MSTR |
                SPI_CR1_CPHA | SPI_CR1_CPOL, //Set CPHA and CPOL to be 1
                0
        };
#elif defined(BOARD_RM_C)
        {
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
#endif