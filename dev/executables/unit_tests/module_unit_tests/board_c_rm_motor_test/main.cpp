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
#include "pid_controller.hpp"
#include "can_interface.h"
#include "can_motor_interface.h"

#ifndef BOARD_RM_C
#error This target is only for Robomaster Board C. Please add -DBOARD_NAME="rm_board_c" to your cmake options
#endif

using namespace chibios_rt;

/*
 * Message server thread class. It receives messages and does nothing except
 * reply after the specified time.
 */
CANInterface can1(&CAND1);
CANInterface can2(&CAND2);

class PIDThread : public BaseStaticThread<512>
{
    PIDController pid_v2i;
    int target_current = 0;
    float target_velocity = 0.0f;
    void main() final
    {
        setName("PID Thread");

        pid_v2i.change_parameters({20.0f, 0.1f, 0.0f, 6000.0, 10000.0});
        while (!shouldTerminate())
        {
            if (target_velocity < 360.0f*10)
            {
                target_velocity += 0.08f;
            }
            target_current = static_cast<int>(pid_v2i.calc(CANMotorIF::motor_feedback[0].actual_velocity, target_velocity));
            CANMotorIF::set_current(CANMotorCFG::MOTOR_1, target_current);
            CANMotorIF::post_target_current(CANMotorFeedback::can_channel_1,0x1FF);

            sleep(TIME_MS2I(1));
        }
    }
} pid_thread;

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

    chThdSleepMilliseconds(1000);
    can1.start(NORMALPRIO);
    can2.start(NORMALPRIO+1);
    chThdSleepMilliseconds(1000);
    palClearPad(GPIOH, GPIOH_LED_R);
    palClearPad(GPIOH, GPIOH_LED_G);
    palClearPad(GPIOH, GPIOH_LED_B);
    CANMotorIF::init(&can1, &can2);
    chThdSleepMilliseconds(1000);
    pid_thread.start(NORMALPRIO+2);
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
