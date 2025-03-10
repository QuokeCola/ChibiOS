//
// Created by Quoke on 2/25/2025.
//

#ifndef META_EMBEDDED_IMU_INTERFACE_TEMPLATE_H
#define META_EMBEDDED_IMU_INTERFACE_TEMPLATE_H

#include "ch.hpp"
#include "hal.h"
#include "ahrs_math.hpp"

class IMUInterfaceTemplate{
public:

    virtual ~IMUInterfaceTemplate() = default;

    /**
     * Get data from gyroscope
     * @return Gyro data from gyroscope [deg/s]
     */
    virtual Vector3D get_gyro() = 0;

    /**
     * Get data from accelerometer
     * @return Acceleration data from accelerometer [m/s^2]
     */
    virtual Vector3D get_accel() = 0;

    /**
     * Get magnet data from IST
     * @return Magnet data [uT]
     */
    virtual Vector3D get_magnet() = 0;

    /**
     * Get last update time from system start
     * @return Last update time from system start [ms]
     */
    virtual time_msecs_t get_mpu_update_time() = 0;

    /**
     * Get last update time from system start
     * @return Last update time from system start [ms]
     */
    virtual time_msecs_t get_ist_update_time()  = 0;

};


#endif //META_EMBEDDED_IMU_INTERFACE_TEMPLATE_H
