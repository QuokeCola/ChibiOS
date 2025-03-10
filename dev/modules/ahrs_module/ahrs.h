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

class AHRS {
public:
    static void start(tprio_t thread_prio);
private:
    class UpdateThread: BaseStaticThread<512> {
        void main() final;
    };
};


#endif //META_EMBEDDED_AHRS_H
