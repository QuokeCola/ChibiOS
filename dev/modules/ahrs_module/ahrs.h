//
// Created by Quoke on 3/10/2025.
//

#ifndef META_EMBEDDED_AHRS_H
#define META_EMBEDDED_AHRS_H

#include "ch.hpp"
#include "hal.h"
#include "shell.h"

#include "imu_interface.h"
#include "ahrs_math.hpp"
#include "ahrs_lib.h"

using namespace chibios_rt;

class AHRS : public BaseStaticThread<512>{
public:
    ThreadReference start(tprio_t thread_prio) override;
    Vector3D angle = {0,0,0};

private:

    IMUInterface imu_interface;
    float quat[4] = {0,0,0,0};
    Vector3D gyro_r = {0,0,0};
    Vector3D accel_r = {0,0,0};
    Vector3D magnet_r = {0,0,0};

    static constexpr int THREAD_UPDATE_INTERVAL = 1000; // [us]
    void main() override;
};

#endif //META_EMBEDDED_AHRS_H