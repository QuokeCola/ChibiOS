//
// Created by Quoke on 3/10/2025.
//

#include "ahrs.h"

ThreadReference AHRS::start(tprio_t thread_prio) {
    imu_interface.init();

    accel_r = imu_interface.get_accel()*DEG2RAD;
    magnet_r = imu_interface.get_magnet()*DEG2RAD;

    ::AHRS_init(quat, (const fp32 *) &accel_r, (const fp32 *) &magnet_r);

    return BaseStaticThread<512>::start(thread_prio);
}

void AHRS::main() {
    setName("AHRS");
    auto system_time = TIME_I2US(chVTGetSystemTimeX());
    while (!shouldTerminate()) {
        imu_interface.update();
        chSysLock();  /// --- ENTER S-Locked state. DO NOT use LOG, printf, non S/I-Class functions or return ---
        {
            gyro_r = imu_interface.get_gyro()*DEG2RAD;
            accel_r = imu_interface.get_accel()*DEG2RAD;
            magnet_r = imu_interface.get_magnet()*DEG2RAD;
            ::AHRS_update(quat, 0.001f, (const fp32 *) &gyro_r, (const fp32 *) &accel_r, (const fp32 *) &magnet_r);
            ::get_angle(quat, &angle.x, &angle.y, &angle.z);
//            angle = imu_interface.get_magnet();
            angle = angle * RAD2DEG;
        }
        system_time = TIME_I2US(chVTGetSystemTimeX());
        sleep(TIME_US2I(THREAD_UPDATE_INTERVAL - (system_time % THREAD_UPDATE_INTERVAL)));
    }
}
