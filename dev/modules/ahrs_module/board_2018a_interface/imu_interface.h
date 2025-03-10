//
// Created by Quoke on 3/6/2025.
//

#ifndef BOARD_C_INTERFACE_H
#define BOARD_C_INTERFACE_H

#include "ch.hpp"
#include "hal.h"

#include "mpu6500_reg.h"
#include "ist8310_reg.h"

#include "imu_interface_template.h"
#include "common_macro.h"

#if defined(BOARD_RM_2018A)

#define MPU6500_SPI_DRIVER SPID5
#define MPU6500_SPI_CS_PAD GPIOF
#define MPU6500_SPI_CS_PIN GPIOF_SPI5_NSS

#elif defined(BOARD_RM_C)
#include "ist8310_reg.h"
#define BMI088_SPI_DRIVER SPID1
#define BMI088_SPI_CS_PAD GPIOA
#define BMI088_SPI_CS_ACCEL_PIN GPIOA_CS1_ACCEL
#define BMI088_SPI_CS_GYRO_PIN GPIOB_CS1_GYRO
#else
#error "MPU6500 interface has not been defined for selected board"
#endif

class IMUInterface : IMUInterfaceTemplate {
public:
    static void start(tprio_t priority);
    Vector3D  get_gyro() override { return gyro; }
    Vector3D get_accel() override { return accel; }
    Vector3D get_magnet() override { return magnet; }
    time_msecs_t get_mpu_update_time() override { return imu_update_time; }
    time_msecs_t get_ist_update_time() override { return imu_update_time; }

private:
    static void init_mpu6500();
    static void init_ist8310();

    class IMUThread : public chibios_rt::BaseStaticThread<512> {
        void main() final;
    };

    static IMUThread imu_thread;

    /*===========================================================================*/
    /*                               Sensor data                                 */
    /*===========================================================================*/
    static float temperature;
    static Vector3D magnet;
    static Vector3D accel;
    static Vector3D gyro;
    static Vector3D gyro_raw;   // raw (biased) data of gyro
    static time_msecs_t imu_update_time;   // last update time from system start [ms]

    /*===========================================================================*/
    /*                             Sensor parameters                             */
    /*===========================================================================*/

    static float gyro_sensitivity;   // the coefficient converting the raw data to degree
    static float accel_sensitivity;  // the coefficient converting the raw data to m/s^2
    static float temperature_bias;
    static Vector3D gyro_zero_bias;  // Sensor drifting

    /*===========================================================================*/
    /*                         SPI buffer configurations                         */
    /*===========================================================================*/

    static constexpr size_t RX_BUF_SIZE = 6 /* gyro */ + 2 /* temperature */ + 6 /* accel */ + 7 /* ist8310*/;
    static uint8_t rx_buf[RX_BUF_SIZE];

    /*===========================================================================*/
    /*                           Sensor configurations                           */
    /*===========================================================================*/
    /**
     * MPU6500_ACCEL_CONFIG_2, [2:0] bits
     */
    typedef enum {
        MPU6500_ADLPF_460HZ = 0,
        MPU6500_ADLPF_184HZ = 1,
        MPU6500_ADLPF_92HZ = 2,
        MPU6500_ADLPF_41HZ = 3,
        MPU6500_ADLPF_20HZ = 4,
        MPU6500_ADLPF_10HZ = 5,
        MPU6500_ADLPF_5HZ = 6
    } acc_dlpf_config_t;

    /**
     * Gyro Digital Low-Pass Filter Configuration
     * Register 26 – Configuration, [2:0] bits DLPF_CFG
     * @note to enable DLPF, [1:0] FCHOICE_B at Reg 27 should be set to 00 (default by reset)
     * @note when DLPF is enabled, the sample rate is 1kHz by default (can be changed with Reg 25 – Sample Rate Divider)
     */
    typedef enum {
        MPU6500_DLPF_250HZ = 0,
        MPU6500_DLPF_184HZ = 1,
        MPU6500_DLPF_92HZ = 2,
        MPU6500_DLPF_41HZ = 3,  // √
        MPU6500_DLPF_20HZ = 4,
        MPU6500_DLPF_10HZ = 5,
        MPU6500_DLPF_5HZ = 6,
        MPU6500_DLPF_3600HZ = 7
    } dlpf_config_t;

    /**
     * Gyro full scale config
     * Register 27 - Gyroscope Configuration, [4:3] bits GYRO_FS_SEL
     */
    typedef enum {
        MPU6500_GYRO_SCALE_250 = 0,  // range of 250 dps with sensitivity factor 131
        MPU6500_GYRO_SCALE_500 = 1,  // range of 500 dps with sensitivity factor 65.5
        MPU6500_GYRO_SCALE_1000 = 2, // range of 1000 dps with sensitivity factor 32.8 √
        MPU6500_GYRO_SCALE_2000 = 3  // range of 2000 dps with sensitivity factor 16.4
    } gyro_scale_t;

    /**
     * Scale config for acceleration
     * MPU6500_ACCEL_CONFIG, [4:3] bits, shift when set SPI
     */
    typedef enum {
        MPU6500_ACCEL_SCALE_2G = 0,
        MPU6500_ACCEL_SCALE_4G = 1,
        MPU6500_ACCEL_SCALE_8G = 2,  // √
        MPU6500_ACCEL_SCALE_16G = 3
    } accel_scale_t;

    typedef struct {
        gyro_scale_t _gyro_scale;
        accel_scale_t _accel_scale;
        dlpf_config_t _dlpf_config;
        acc_dlpf_config_t _acc_dlpf_config;
    } mpu6500_config_t;

    static constexpr int THREAD_UPDATE_INTERVAL = 1000; // [us]
    static constexpr int GYRO_CALIBRATION_SAMPLE_NUMBER = 500;

    static constexpr mpu6500_config_t CONFIG = {
            MPU6500_GYRO_SCALE_1000,  // Gyro full scale 1000 dps (degree per second)
            MPU6500_ACCEL_SCALE_8G,  // Accel full scale 8g
            MPU6500_DLPF_41HZ,       // Gyro digital low-pass filter 41Hz
            MPU6500_ADLPF_20HZ};  // Accel digital low-pass filter 20Hz

};



#endif //BOARD_C_INTERFACE_H
