//
// Created by Quoke on 3/6/2025.
//

#ifndef BOARD_C_INTERFACE_H
#define BOARD_C_INTERFACE_H

#include "ch.hpp"
#include "hal.h"

#include "bmi088_reg.h"

#if defined(BOARD_RM_2018A)

#define MPU6500_SPI_DRIVER SPID5
#define MPU6500_SPI_CS_PAD GPIOF
#define MPU6500_SPI_CS_PIN GPIOF_PIN6


#elif defined(BOARD_RM_C)
#define BMI088_SPI_DRIVER SPID1
#define BMI088_SPI_CS_PAD GPIOA
#define BMI088_SPI_CS_ACCEL_PIN GPIOA_CS1_ACCEL
#define BMI088_SPI_CS_GYRO_PIN GPIOB_CS1_GYRO
#else
#error "MPU6500 interface has not been defined for selected board"
#endif

class IMUInterface {

};



#endif //BOARD_C_INTERFACE_H
