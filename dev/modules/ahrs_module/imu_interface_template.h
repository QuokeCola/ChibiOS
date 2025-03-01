//
// Created by Quoke on 2/25/2025.
//

#ifndef META_EMBEDDED_IMU_INTERFACE_TEMPLATE_H
#define META_EMBEDDED_IMU_INTERFACE_TEMPLATE_H

#include "ch.hpp"
#include "hal.h"


#if defined(BOARD_RM_2018A)

#define MPU6500_SPI_DRIVER SPID5
#define MPU6500_SPI_CS_PAD GPIOF
#define MPU6500_SPI_CS_PIN GPIOF_PIN6
#include "mpu6500_reg.h"
#include "ist8310_reg.h"

#elif defined(BOARD_RM_C)
#include "ist8310_reg.h"
#define BMI088_SPI_DRIVER SPID1
#define BMI088_SPI_CS_PAD GPIOA
#define BMI088_SPI_CS_ACCEL_PIN GPIOA_CS1_ACCEL
#define BMI088_SPI_CS_GYRO_PIN GPIOB_CS1_GYRO
#else
#error "MPU6500 interface has not been defined for selected board"
#endif


class IMUInterfaceTemplate {

};


#endif //META_EMBEDDED_IMU_INTERFACE_TEMPLATE_H
