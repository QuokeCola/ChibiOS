//
// Created by Chen Qian on 10/29/21.
//

#include "can_motor_config_template.h"

CANMotorBase CANMotorCFG::CANMotorProfile[MOTOR_COUNT] = {
        {CANMotorBase::can_channel_1, 0x205, CANMotorBase::M2006, 0},
        {CANMotorBase::can_channel_1, 0x206, CANMotorBase::M2006, 0}
};