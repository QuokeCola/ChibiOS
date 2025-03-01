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
#include "buzzer_scheduler.h"
#include "shell.h"

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
    PIDController pid_v2i[2];
    PIDController pid_a2v[2];
    int target_current[2] = {0};
    float target_velocity[2] = {0.0f};
public:
    float target_angle[2] = {0.0f};
private:
    void main() final
    {
        setName("PID Thread");

        pid_v2i[0].change_parameters({40.0f, 0.2f, 0.0f, 10000.0, 10000.0});
        pid_v2i[1].change_parameters({40.0f, 0.2f, 0.0f, 10000.0, 10000.0});
        pid_a2v[0].change_parameters({50.0f, 0.0f, 0.0f, 6000.0, 1800.0});
        pid_a2v[1].change_parameters({50.0f, 0.0f, 0.0f, 6000.0, 1800.0});

        while (!shouldTerminate())
        {
            target_velocity[0] = pid_a2v[0].calc(CANMotorIF::motor_feedback[0].accumulate_angle(), target_angle[0]);
            target_velocity[1] = pid_a2v[1].calc(CANMotorIF::motor_feedback[1].accumulate_angle(), target_angle[1]);
            target_current[0] = static_cast<int>(pid_v2i[0].calc(CANMotorIF::motor_feedback[0].actual_velocity, target_velocity[0]));
            target_current[1] = static_cast<int>(pid_v2i[1].calc(CANMotorIF::motor_feedback[1].actual_velocity, target_velocity[1]));
            CANMotorIF::set_current(CANMotorCFG::MOTOR_1, target_current[0]);
            CANMotorIF::set_current(CANMotorCFG::MOTOR_2, target_current[1]);
            CANMotorIF::post_target_current(CANMotorFeedback::can_channel_1,0x1FF);

            sleep(TIME_MS2I(1));
        }
    }
} pid_thread;

bool shell_callback(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void) chp;
    if (argc != 2 && argv[0][0] == '?') return false;
    pid_thread.target_angle[0] = Shell::atof(argv[0]);
    pid_thread.target_angle[1] = Shell::atof(argv[1]);
    return true;
}

Shell::Command commands[1] = {
        {"set_angles", "motor_target_angle_0 motor_target_angle_1", shell_callback, nullptr}
};

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
    BuzzerSKD::init(NORMALPRIO+2);
    Shell::addCommands(commands);
    chThdSleepMilliseconds(1000);
    palClearPad(GPIOH, GPIOH_LED_R);
    palClearPad(GPIOH, GPIOH_LED_G);
    palClearPad(GPIOH, GPIOH_LED_B);
//    BuzzerSKD::play_sound(BuzzerSKD::sound_kong_fu_FC);
    CANMotorIF::init(&can1, &can2);
    chThdSleepMilliseconds(1000);
    pid_thread.start(NORMALPRIO+3);
    Shell::start(NORMALPRIO+4);
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
