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
    // PID controllers and intermediate variables
    PIDController pid_a2v, pid_v2i;
    int   target_current = 0;
    float target_velocity, target_angle = 0.0f;

    // IO Variables
    bool  previous_button_status[5] = {false};
    bool  current_button_status[5]  = {false};

    // State and target
    bool  valve_is_on       = false;  // true - valve on.
    float on_angle_position = 7.5f;  // deg
    float off_angle_position = 0.0f;
    time_msecs_t valve_on_duration = 0;      // ms
    time_msecs_t  valve_on_time     = 0;

    void main() final
    {
        setName("PID Thread");
        pid_v2i.change_parameters({70.0f, 1.0f, 0.0f, 6000.0, 10000.0});
        pid_a2v.change_parameters({30, 0.0, 1.0, 100, 500});
        off_angle_position = CANMotorIF::motor_feedback[CANMotorCFG::MOTOR_1].accumulate_angle();
        target_angle = off_angle_position;
        while (!shouldTerminate())
        {
            // Update button
            current_button_status[0] = !palReadPad(GPIOE, GPIOE_PIN9 );
            current_button_status[1] = !palReadPad(GPIOE, GPIOE_PIN11);
            current_button_status[2] = !palReadPad(GPIOE, GPIOE_PIN13);
            current_button_status[3] = !palReadPad(GPIOE, GPIOE_PIN14);
            current_button_status[4] = !palReadPad(GPIOC, GPIOC_PIN6);

            if (!valve_is_on) {
                if        (!previous_button_status[0] && current_button_status[0]) {
                    valve_is_on = true;
                    valve_on_time = SYSTIME;
                    valve_on_duration = 2000; // ms
                    target_angle = on_angle_position+off_angle_position;
                    palSetPad(GPIOH, GPIOH_LED_R);
                } else if (!previous_button_status[1] && current_button_status[1]) {
                    valve_is_on = true;
                    valve_on_time = SYSTIME;
                    valve_on_duration = 4000; // ms
                    target_angle = on_angle_position+off_angle_position;
                    palSetPad(GPIOH, GPIOH_LED_G);
                } else if (!previous_button_status[2] && current_button_status[2]) {
                    valve_is_on = true;
                    valve_on_time = SYSTIME;
                    valve_on_duration = 6000; // ms
                    target_angle = on_angle_position+off_angle_position;
                    palSetPad(GPIOH, GPIOH_LED_B);
                }
                if (current_button_status[3]){
                    off_angle_position += 0.01f;
                    target_angle=off_angle_position;
                }
                if (current_button_status[4]){
                    off_angle_position -= 0.01f;
                    target_angle=off_angle_position;
                }
            } else {
                if (SYSTIME - valve_on_time > valve_on_duration) {
                    valve_is_on = false;
                    target_angle = off_angle_position;
                    palClearPad(GPIOH, GPIOH_LED_R);
                    palClearPad(GPIOH, GPIOH_LED_G);
                    palClearPad(GPIOH, GPIOH_LED_B);
                }
            }
            // PID
            target_velocity = pid_a2v.calc(CANMotorIF::motor_feedback[0].accumulate_angle(), target_angle);
            target_current = static_cast<int>(pid_v2i.calc(CANMotorIF::motor_feedback[0].actual_velocity, target_velocity));
            CANMotorIF::set_current(CANMotorCFG::MOTOR_1, target_current);
            CANMotorIF::post_target_current(CANMotorFeedback::can_channel_1,0x1FF);

            // Update IO
            previous_button_status[0]=current_button_status[0];
            previous_button_status[1]=current_button_status[1];
            previous_button_status[2]=current_button_status[2];
            previous_button_status[3]=current_button_status[3];
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

    // Input for buttons
    palSetPadMode(GPIOE, GPIOE_PIN9,  PAL_MODE_INPUT_PULLUP); // TIM1_CHI1, C1
    palSetPadMode(GPIOE, GPIOE_PIN11, PAL_MODE_INPUT_PULLUP); // TIM1_CHI2, C2
    palSetPadMode(GPIOE, GPIOE_PIN13, PAL_MODE_INPUT_PULLUP); // TIM1_CHI3, C3
    palSetPadMode(GPIOE, GPIOE_PIN14, PAL_MODE_INPUT_PULLUP); // TIM1_CHI4, C4
    palSetPadMode(GPIOC, GPIOE_PIN6,  PAL_MODE_INPUT_PULLUP); // TIM8_CHI1, C5

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
