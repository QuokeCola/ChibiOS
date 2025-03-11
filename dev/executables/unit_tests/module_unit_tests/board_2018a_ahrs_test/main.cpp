/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.hpp"
#include "hal.h"
#include "shell.h"
#include "ahrs.h"
#ifndef BOARD_RM_2018A
#error This target is only for Robomaster Board 2018A. Please add -DBOARD_NAME="rm_board_2018a" to your cmake options
#endif

using namespace chibios_rt;

/*
 * Message server thread class. It receives messages and does nothing except
 * reply after the specified time.
 */

AHRS ahrs;

class Thd : public BaseStaticThread<512> {
public:
//    AHRS ahrs;
private:
    void main() final{
        setName("UUIDD");
        bool test = false;
//        ahrs.start(NORMALPRIO+3);
        while (!shouldTerminate()) {
            Vector3D accel = ahrs.angle;
//            Vector3D accel = {0,0,0,};
            Shell::printf("%f %f %f" SHELL_NEWLINE_STR,accel.x, accel.y, accel.z);
            chThdSleepMilliseconds(100);
            (test) ? palSetPad(GPIOG,GPIOG_LED4) : palClearPad(GPIOG,GPIOG_LED4);
            test = !test;
        }
    };
}thd;



/*
 * Application entry point.
 */
int main(void) {

    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *   and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */

    halInit();
    System::init();

    Shell::start(NORMALPRIO);

    chThdSleepMilliseconds(1000);

    ahrs.start(NORMALPRIO+1);

    chThdSleepMilliseconds(1000);

    thd.start(NORMALPRIO+2);

    chThdSleepMilliseconds(10000);
    // See chconf.h for what this #define means.
#if CH_CFG_NO_IDLE_THREAD
    // ChibiOS idle thread has been disabled,
    // main() should implement infinite loop
    while (true) {}
#else
    // When main() quits, the main thread will somehow
    // enter an infinite loop, so we set the priority to lowest
    // before quitting, to let other threads run normally
    BaseThread::setPriority(1);
#endif
    return 0;

}
